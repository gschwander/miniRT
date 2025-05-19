/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:50:15 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/19 15:35:16 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define EPSILON 1e-6

bool plane_intersection(t_elem elem, t_ray ray, t_point *local_point, double *t)
{
    double denom;
    t_vec CO;

    denom = vec_scal(ray.direction, elem.normal);
    if (fabs(denom) < EPSILON) // rayon parallèle au plan
    return (false);
    // attention, ici j'ai inversé le signe de CO
    CO = vec_minus(elem.origin, ray.origin);
    // printf("CO: %f %f %f\n", CO.x, CO.y, CO.z);
    *t = vec_scal(CO, elem.normal) / denom;
    
    // printf("t: %f\n", *t);
    if (*t < 0) // intersection derrière la caméra
    return (false);
    
    local_point->P = vec_plus(ray.origin, vec_mult(*t, ray.direction));
    local_point->N = elem.normal; // plan infini, normale constante
    return (true);
}

bool sphere_intersection(t_elem elem, t_ray ray, t_point *local_point, double *t)
{
    double delta;
    double a;
    double b;
    double c;
    double t_tab[2];

    a = 1;
    b = 2 * vec_scal(ray.direction, vec_minus(ray.origin, elem.origin));
    c = norm2(vec_minus(ray.origin, elem.origin)) - (elem.radius * elem.radius);
    delta = b * b - 4 * a * c;
    if (delta < 0)
        return (false);
    t_tab[0] = (- b - sqrt(delta)) / (2 * a);
    t_tab[1] = (- b + sqrt(delta)) / (2 * a);
    if (t_tab[1] < 0)
        return (false);
    if (t_tab[0] < 0)
        *t = t_tab[1];
    else
        *t = t_tab[0];
    local_point->P = vec_plus(ray.origin, vec_mult(*t, ray.direction));
    local_point->N = normalize(vec_minus(local_point->P, elem.origin));
    return (true);
}

bool intersections(t_rt *rt, t_ray ray, t_point *point, int *elem_id)
{
    int i;
    t_point local_point;
    bool has_inter[2];
    double t;

    rt->min_t = 1E99;
    has_inter[0] = false;
    i = -1;
    while (++i < rt->scene.elem_nb)
    {
        has_inter[1] = rt->scene.elem[i].intersection(rt->scene.elem[i],
            ray, &local_point, &t);
        if (has_inter[1])
        {
            has_inter[0] = true;
            if (t < rt->min_t)
            {
                rt->min_t = t;
                *point = local_point;
                *elem_id = i;
            }
        }
    }
    if (rt->min_t < 0.1)
        return (false);
    return (has_inter[0]);
}

t_vec cal_dir_ray(t_rt *rt)
{
    t_vec vec;
    
    vec.x = (rt->j - rt->W / 2) - rt->scene.camera.origin.x;
    vec.y = (rt->i - rt->H / 2) - rt->scene.camera.origin.y;
    vec.z = - rt->W / (2 * tan(rt->scene.camera.fov / 2));
    return (vec);
}

bool shadow(t_rt *rt, t_point *point)
{
    t_ray ray_light;
    bool has_inter_light;
    t_point point_light;
    int sphere_id;
    double d_light2;
    
    ray_light.origin = vec_plus(point->P, vec_mult(0.01, point->N));
    ray_light.direction = normalize(vec_minus(rt->scene.light.origin, point->P));
    has_inter_light = intersections(rt, ray_light, &point_light, &sphere_id);
    d_light2 = norm2(vec_minus(rt->scene.light.origin, point->P));
    if (has_inter_light && rt->min_t * rt->min_t < d_light2)
		return (true);
	return (false);
}

void get_color(t_rt *rt, t_point point, int elem_id)
{
    t_elem s;
    t_vec color;
    t_vec ambient;
    t_vec Ldir;
    double   dist2;
    double   diff_coeff;
    double intensity_lum;
    t_vec diffuse;
    int idx;
	
    s = rt->scene.elem[elem_id];
    ambient = vec_mult(255 * rt->scene.ambient_light.intensity, vec_m_vec(s.albedo, rt->scene.ambient_light.color));
    Ldir = normalize(vec_minus(rt->scene.light.origin, point.P));
    dist2 = norm2(vec_minus(rt->scene.light.origin, point.P));
    diff_coeff = fmax(0., vec_scal(Ldir, point.N)) / dist2;
    intensity_lum = 1e4;
    diffuse = vec_mult(intensity_lum * diff_coeff, vec_m_vec(s.albedo, rt->scene.light.color));
	if (shadow(rt, &point))
		color = ambient;
	else
		color = vec_plus(ambient, vec_mult(255, diffuse));
    color.x = pow(color.x, 1/2.2);
    color.y = pow(color.y, 1/2.2);
    color.z = pow(color.z, 1/2.2);
    idx = ((rt->H - rt->i - 1) * rt->W + rt->j) * 3;
    rt->image[idx + 0] = (unsigned char)(fmin(255., fmax(0., color.x)));
    rt->image[idx + 1] = (unsigned char)(fmin(255., fmax(0., color.y)));
    rt->image[idx + 2] = (unsigned char)(fmin(255., fmax(0., color.z)));
}

void color_nul(t_rt *rt)
{
    rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 0] = 0;
    rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 1] = 0;
    rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 2] = 0;
}


unsigned char * render(t_rt *rt)
{
    t_ray ray;
    t_point point;
    int elem_id;

    elem_id = 0;
    rt->image = wrap_malloc(rt, sizeof(unsigned char) * rt->W * rt->H * 3);
    rt->i = -1;
    while (++rt->i < rt->H)
    {
        rt->j = -1;
        while (++rt->j < rt->W)
        {
            ray.origin = rt->scene.camera.origin;
            ray.direction = normalize(cal_dir_ray(rt));
            if (intersections(rt, ray, &point, &elem_id))
            {  
               get_color(rt, point, elem_id);
            }
            else
                color_nul(rt);
        }
    }
    return (rt->image);
}
