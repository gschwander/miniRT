/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:14:23 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 15:06:00 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define EPSILON 1e-6

t_vec	cal_dir_ray(t_rt *rt)
{
	t_vec	vec;

	vec.x = (rt->j - rt->w / 2) - rt->scene.camera.origin.x;
	vec.y = (rt->i - rt->h / 2) - rt->scene.camera.origin.y;
	vec.z = -rt->w / (2 * tan(rt->scene.camera.fov / 2));
	return (vec);
}

void	plane_intersection(t_elem elem, t_ray ray, t_point *local_point,
		double *t)
{
	double	denom;
	t_vec	co;

	*t = -1;
	denom = vec_scal(ray.direction, elem.normal);
	if (fabs(denom) < EPSILON)
		return ;
	co = vec_minus(elem.origin, ray.origin);
	*t = vec_scal(co, elem.normal) / denom;
	if (*t < 0)
		return ;
	local_point->p = vec_plus(ray.origin, vec_mult(*t, ray.direction));
	local_point->n = elem.normal;
}

void	sphere_intersection(t_elem elem, t_ray ray, t_point *local_point,
		double *t)
{
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t_tab[2];

	a = 1;
	*t = -1;
	b = 2 * vec_scal(ray.direction, vec_minus(ray.origin, elem.origin));
	c = norm2(vec_minus(ray.origin, elem.origin)) - (elem.radius * elem.radius);
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return ;
	t_tab[0] = (-b - sqrt(delta)) / (2 * a);
	t_tab[1] = (-b + sqrt(delta)) / (2 * a);
	if (t_tab[1] < 0)
		return ;
	if (t_tab[0] < 0)
		*t = t_tab[1];
	else
		*t = t_tab[0];
	local_point->p = vec_plus(ray.origin, vec_mult(*t, ray.direction));
	local_point->n = normalize(vec_minus(local_point->p, elem.origin));
}

bool	intersections(t_rt *rt, t_ray ray, t_point *point, int *elem_id)
{
	t_point	local_point;
	bool	has_inter;
	double	t;

	rt->min_t = 1E99;
	has_inter = false;
	rt->k = -1;
	while (++rt->k < rt->scene.elem_nb)
	{
		rt->scene.elem[rt->k].intersection(rt->scene.elem[rt->k],
				ray, &local_point, &t);
		if (t > 0)
		{
			has_inter = true;
			if (t < rt->min_t)
			{
				rt->min_t = t;
				*point = local_point;
				*elem_id = rt->k;
			}
		}
	}
	return (has_inter);
}
