/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:07:29 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 11:40:37 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define EPSILON 1e-6

static bool	cap_inf_intersection(t_elem elem, t_ray ray, t_point *point,
		double *t)
{
	t_vec	base;
	double	denom;
	t_vec	p;
	double	t1;
	double	t_base;

	base = vec_minus(elem.origin, vec_mult(0.5 * elem.height, elem.direction));
	denom = vec_scal(ray.direction, elem.direction);
	t_base = -1;
	if (fabs(denom) < EPSILON)
		return (false);
	t1 = vec_scal(vec_minus(base, ray.origin), elem.direction) / denom;
	if (t1 < EPSILON)
		return (false);
	p = vec_plus(ray.origin, vec_mult(t1, ray.direction));
	if (norm2(vec_minus(p, base)) > elem.radius * elem.radius)
		return (false);
	t_base = t1;
	*t = t_base;
	point->P = p;
	point->N = vec_mult(-1, elem.direction);
	return (true);
}

static bool	cap_sup_intersection(t_elem elem, t_ray ray, t_point *point,
		double *t)
{
	t_vec	top_center;
	t_vec	p;
	double	t_top;
	double	t1;
	double	denom;

	top_center = vec_plus(elem.origin, vec_mult(0.5 * elem.height,
				elem.direction));
	denom = vec_scal(ray.direction, elem.direction);
	t_top = -1;
	if (fabs(denom) < EPSILON)
		return (false);
	t1 = vec_scal(vec_minus(top_center, ray.origin), elem.direction) / denom;
	if (t1 < EPSILON)
		return (false);
	p = vec_plus(ray.origin, vec_mult(t1, ray.direction));
	if (norm2(vec_minus(p, top_center)) > elem.radius * elem.radius)
		return (false);
	if (t_top > 0 && t1 > t_top)
		return (false);
	t_top = t1;
	*t = t_top;
	point->P = p;
	point->N = elem.direction;
	return (true);
}

static bool	has_inter(double *t, double *min_t, t_point *point,
		t_point local_point)
{
	if (*t < *min_t)
	{
		*min_t = *t;
		point->P = local_point.P;
		point->N = local_point.N;
	}
	return (true);
}

bool	cylinder_intersection(t_elem elem, t_ray ray, t_point *point, double *t)
{
	t_point	local_point;
	bool	e;
	double	min_t;

	min_t = 1E99;
	e = false;
	if (lat_intersection(elem, ray, &local_point, t))
		e = has_inter(t, &min_t, point, local_point);
	if (cap_sup_intersection(elem, ray, &local_point, t))
		e = has_inter(t, &min_t, point, local_point);
	if (cap_inf_intersection(elem, ray, &local_point, t))
		e = has_inter(t, &min_t, point, local_point);
	return (e);
}
