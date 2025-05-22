/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:14:23 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 12:32:53 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define EPSILON 1e-6

t_vec	cal_dir_ray(t_rt *rt)
{
	t_vec	vec;

	vec.x = (rt->j - rt->W / 2) - rt->scene.camera.origin.x;
	vec.y = (rt->i - rt->H / 2) - rt->scene.camera.origin.y;
	vec.z = -rt->W / (2 * tan(rt->scene.camera.fov / 2));
	return (vec);
}

bool	plane_intersection(t_elem elem, t_ray ray, t_point *local_point,
		double *t)
{
	double	denom;
	t_vec	co;

	denom = vec_scal(ray.direction, elem.normal);
	if (fabs(denom) < EPSILON)
		return (false);
	co = vec_minus(elem.origin, ray.origin);
	*t = vec_scal(co, elem.normal) / denom;
	if (*t < 0)
		return (false);
	local_point->P = vec_plus(ray.origin, vec_mult(*t, ray.direction));
	local_point->N = elem.normal;
	return (true);
}

bool	sphere_intersection(t_elem elem, t_ray ray, t_point *local_point,
		double *t)
{
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t_tab[2];

	a = 1;
	b = 2 * vec_scal(ray.direction, vec_minus(ray.origin, elem.origin));
	c = norm2(vec_minus(ray.origin, elem.origin)) - (elem.radius * elem.radius);
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (false);
	t_tab[0] = (-b - sqrt(delta)) / (2 * a);
	t_tab[1] = (-b + sqrt(delta)) / (2 * a);
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

bool	intersections(t_rt *rt, t_ray ray, t_point *point, int *elem_id)
{
	t_point	local_point;
	bool	has_inter[2];
	double	t;

	rt->min_t = 1E99;
	has_inter[0] = false;
	rt->k = -1;
	while (++rt->k < rt->scene.elem_nb)
	{
		has_inter[1] = rt->scene.elem[rt->k].intersection(rt->scene.elem[rt->k],
				ray, &local_point, &t);
		if (has_inter[1])
		{
			has_inter[0] = true;
			if (t < rt->min_t)
			{
				rt->min_t = t;
				*point = local_point;
				*elem_id = rt->k;
			}
		}
	}
	if (rt->min_t < 0.1)
		return (false);
	return (has_inter[0]);
}
