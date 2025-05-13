/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:50:15 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/13 17:21:23 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool intersection(t_sphere sphere, t_ray ray, t_point *local_point, double *t)
{
    double delta;
    double a;
    double b;
    double c;
    double t_tab[2];

    a = 1;
    b = 2 * vec_scal(ray.direction, vec_minus(ray.origin, sphere.origin));
    c = norm2(vec_minus(ray.origin, sphere.origin)) - (sphere.radius * sphere.radius);
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
    local_point->N = normalize(vec_minus(local_point->P, sphere.origin));
    return (true);
}

bool intersections(t_rt *rt, t_ray ray, t_point *point, int *sphere_id)
{
    int i;
    t_point local_point;
    bool has_inter[2];
    double t;

    rt->min_t = 1E99;
    has_inter[0] = false;
    i = -1;
    while (++i < rt->scene.spheres_nb)
    {
        has_inter[1] = intersection(rt->scene.spheres[i], ray, &local_point, &t);
        if (has_inter[1])
        {
            has_inter[0] = true;
            if (t < rt->min_t)
            {
                rt->min_t = t;
                *point = local_point;
                *sphere_id = i;
            }
        }
    }
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

void get_color(t_rt *rt, t_vec P, t_vec N, int sphere_id)
{
    double intensity_lum = 1000000000;
    t_vec intensity_pixel;
    intensity_pixel = (t_vec){0., 0., 0.};
    intensity_pixel = vec_mult(intensity_lum * fmax(0., vec_scal(normalize(vec_minus(rt->scene.light.origin, P)), N) / norm2(vec_minus(rt->scene.light.origin, P))), rt->scene.spheres[sphere_id].albedo);
    rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 0] = fmin(255., fmax(0., pow(intensity_pixel.x, 1 / 2.2)));
    rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 1] = fmin(255., fmax(0., pow(intensity_pixel.y, 1 / 2.2)));
    rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 2] = fmin(255., fmax(0., pow(intensity_pixel.z, 1 / 2.2)));
}

void color_nul(t_rt *rt)
{
    rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 0] = 0;
    rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 1] = 0;
    rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 2] = 0;
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

unsigned char * render(t_rt *rt)
{
    t_ray ray;
    t_point point;
    int sphere_id;

    sphere_id = 0;
    rt->image = wrap_malloc(rt, sizeof(unsigned char) * rt->W * rt->H * 3);
    rt->i = -1;
    while (++rt->i < rt->H)
    {
        rt->j = -1;
        while (++rt->j < rt->W)
        {
            ray.origin = rt->scene.camera.origin;
            // ray.origin = (t_vec){0.,0.,0.};
            ray.direction = normalize(cal_dir_ray(rt));
            if (intersections(rt, ray, &point, &sphere_id))
            {
                if (shadow(rt, &point))
                    color_nul(rt);
                else    
                    get_color(rt, point.P, point.N, sphere_id);
            }
            else
                color_nul(rt);
        }
    }
    return (rt->image);
}
