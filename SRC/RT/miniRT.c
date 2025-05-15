/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:50:15 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/14 12:23:45 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define EPSILON 1e-6

bool intersection_sphere(t_sphere sphere, t_ray ray, t_point *local_point, double *t)
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

#include <math.h>
#define EPSILON 1e-6

bool intersection_cylinder(t_cylinder cy, t_ray ray, t_point *pt, double *t_out)
{
    t_vec O = ray.origin;
    t_vec D = ray.direction;
    t_vec C = cy.origin;
    t_vec V = cy.direction;                  // unitaire
    double r    = cy.radius;
    double h2   = cy.height   * 0.5;
    double denom = vec_scal(D, V);

    double t_min = INFINITY;
    t_vec  N_min = (t_vec){0., 0., 0.};

    // === 1) Surface latérale ===
    {
        t_vec CO   = vec_minus(O, C);
        t_vec Dp   = vec_minus(D, vec_mult(vec_scal(D, V), V));
        t_vec COp  = vec_minus(CO, vec_mult(vec_scal(CO, V), V));
        double a   = vec_scal(Dp, Dp);
        double b   = 2.0 * vec_scal(Dp, COp);
        double c   = vec_scal(COp, COp) - r * r;
        double delta = b * b - 4.0 * a * c;

        if (delta >= 0.0 && fabs(a) > EPSILON)
        {
            double sq = sqrt(delta);
            double t0 = (-b - sq) / (2.0 * a);
            double t1 = (-b + sq) / (2.0 * a);

            /* premier candidat t0 */
            if (t0 > EPSILON)
            {
                t_vec P0 = vec_plus(O, vec_mult(t0, D));
                double proj0 = vec_scal(vec_minus(P0, C), V);
                if (proj0 >= -h2 && proj0 <= h2)
                {
                    if (t0 < t_min)
                    {
                        t_min = t0;
                        t_vec tmp = vec_minus(
                            vec_minus(P0, C),
                            vec_mult(proj0, V)
                        );
                        N_min = normalize(tmp);
                    }
                }
            }

            /* deuxième candidat t1 */
            if (t1 > EPSILON)
            {
                t_vec P1 = vec_plus(O, vec_mult(t1, D));
                double proj1 = vec_scal(vec_minus(P1, C), V);
                if (proj1 >= -h2 && proj1 <= h2)
                {
                    if (t1 < t_min)
                    {
                        t_min = t1;
                        t_vec tmp = vec_minus(
                            vec_minus(P1, C),
                            vec_mult(proj1, V)
                        );
                        N_min = normalize(tmp);
                    }
                }
            }
        }
    }

    // === 2) Base (plan C - h2·V) ===
    if (fabs(denom) > EPSILON)
    {
        t_vec Cb = vec_minus(C, vec_mult(h2, V));
        double tb = vec_scal(vec_minus(Cb, O), V) / denom;
        if (tb > EPSILON && tb < t_min)
        {
            t_vec P2 = vec_plus(O, vec_mult(tb, D));
            t_vec d2 = vec_minus(P2, Cb);
            if (vec_scal(d2, d2) <= r * r)
            {
                t_min = tb;
                N_min = vec_mult(-1.0, V);
            }
        }
    }

    // === 3) Sommet (plan C + h2·V) ===
    if (fabs(denom) > EPSILON)
    {
        t_vec Ct = vec_plus(C, vec_mult(h2, V));
        double tt = vec_scal(vec_minus(Ct, O), V) / denom;
        if (tt > EPSILON && tt < t_min)
        {
            t_vec P3 = vec_plus(O, vec_mult(tt, D));
            t_vec d3 = vec_minus(P3, Ct);
			if (vec_scal(d3, d3) <= r * r)
			{
				t_min = tt;
				N_min = V;
			}
		}
    }

    if (t_min == INFINITY)
        return false;

    /* renvoyer le hit le plus proche */
    pt->P    = vec_plus(O, vec_mult(t_min, D));
    pt->N    = N_min;
    *t_out   = t_min;
    return true;
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
        has_inter[1] = intersection_sphere(rt->scene.spheres[i], ray, &local_point, &t);
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
	i = -1;
	while (++i < rt->scene.cylinders_nb)
	{
		has_inter[1] = intersection_cylinder(rt->scene.cylinders[i], ray, &local_point, &t);
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
	// i = -1;
	// while (++i < rt->scene.planes_nb)
	// {
	// 	has_inter[1] = intersection_plane(rt->scene.planes[i], ray, &local_point, &t);
	// 	if (has_inter[1])
	// 	{
	// 		has_inter[0] = true;
	// 		if (t < rt->min_t)
	// 		{
	// 			rt->min_t = t;
	// 			*point = local_point;
	// 			*sphere_id = i;
	// 		}
	// 	}
	// }
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

// void get_color(t_rt *rt, t_vec P, t_vec N, int sphere_id)
// {
//     double intensity_lum = 1000000000;
//     t_vec intensity_pixel;
//     intensity_pixel = (t_vec){0., 0., 0.};
//     intensity_pixel = vec_mult(intensity_lum * fmax(0., vec_scal(normalize(vec_minus(rt->scene.light.origin, P)), N) / norm2(vec_minus(rt->scene.light.origin, P))), rt->scene.spheres[sphere_id].albedo);
//     rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 0] = fmin(255., fmax(0., pow(intensity_pixel.x, 1 / 2.2)));
//     rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 1] = fmin(255., fmax(0., pow(intensity_pixel.y, 1 / 2.2)));
//     rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 2] = fmin(255., fmax(0., pow(intensity_pixel.z, 1 / 2.2)));
// }

// void get_color(t_rt *rt, t_vec P, t_vec N, int sphere_id)
// {
//     double intensity_lum = 1000000000;
//     t_vec intensity_pixel;
//     t_vec ambient;

//     ambient = vec_mult(rt->scene.ambient_light.intensity, vec_m_vec(rt->scene.spheres[sphere_id].albedo, rt->scene.ambient_light.color));
    
//     intensity_pixel = (t_vec){0., 0., 0.};
//     intensity_pixel = vec_mult(intensity_lum * fmax(0., vec_scal(normalize(vec_minus(rt->scene.light.origin, P)), N) / norm2(vec_minus(rt->scene.light.origin, P))), rt->scene.spheres[sphere_id].albedo);
//     rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 0] = fmin(255., fmax(0., pow(intensity_pixel.x, 1 / 2.2)));
//     rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 1] = fmin(255., fmax(0., pow(intensity_pixel.y, 1 / 2.2)));
//     rt->image[((rt->H - rt->i - 1) * rt->W + rt->j) * 3 + 2] = fmin(255., fmax(0., pow(intensity_pixel.z, 1 / 2.2)));
// }

void get_color(t_rt *rt, t_vec P, t_vec N, int sphere_id)
{
    t_sphere s;
	s = rt->scene.spheres[sphere_id];
    // 1) composante ambiante (toujours présente, non affectée par l’ombre)
    t_vec ambient = vec_mult(255 * rt->scene.ambient_light.intensity,
                             vec_m_vec(s.albedo, rt->scene.ambient_light.color));

    // 2) distance et direction de la lumière
    t_vec Ldir = normalize(vec_minus(rt->scene.light.origin, P));
    double   dist2 = norm2(vec_minus(rt->scene.light.origin, P));
    double   diff_coeff = fmax(0., vec_scal(Ldir, N)) / dist2;
    
    // 3) composante diffuse
    double intensity_lum = 1e4;
    t_vec diffuse = vec_mult(intensity_lum * diff_coeff,
                             vec_m_vec(s.albedo, rt->scene.light.color));

    // 4) si l’objet est dans l’ombre, on ne garde que l’ambiant
	t_vec color;
	if (shadow(rt, &(t_point){ .P = P, .N = N }))
		color = ambient;
	else
		color = vec_plus(ambient, vec_mult(255, diffuse));
	
    // 5) gamma-correction et clamp
    color.x = pow(color.x, 1/2.2);
    color.y = pow(color.y, 1/2.2);
    color.z = pow(color.z, 1/2.2);
	// printf("color: %f %f %f\n", color.x, color.y, color.z);
    int idx = ((rt->H - rt->i - 1) * rt->W + rt->j) * 3;
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
               get_color(rt, point.P, point.N, sphere_id);
            }
            else
                color_nul(rt);
        }
    }
    return (rt->image);
}


// sp -20,0,-30 20 255,0,0
// sp 20,0,-55 20 255,0,0