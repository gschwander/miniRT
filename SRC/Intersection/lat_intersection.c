/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lat_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:40:54 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 13:27:52 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define EPSILON 1e-6

static void	compute_lateral_normal(t_vec P, t_vec base, t_vec V, t_point *point)
{
	double	h;
	t_vec	p_proj;
	t_vec	n;

	h = vec_scal(vec_minus(P, base), V);
	p_proj = vec_plus(base, vec_mult(h, V));
	n = normalize(vec_minus(P, p_proj));
	point->p = P;
	point->n = n;
}

static double	solve_cylinder_quadratic(t_ray ray, t_vec base, t_vec V,
		double radius)
{
	t_vec	co;
	t_vec	dp;
	t_vec	cop;
	double	eq[4];
	double	t[2];

	co = vec_minus(ray.origin, base);
	dp = vec_minus(ray.direction, vec_mult(vec_scal(ray.direction, V), V));
	cop = vec_minus(co, vec_mult(vec_scal(co, V), V));
	eq[0] = vec_scal(dp, dp);
	eq[1] = 2 * vec_scal(dp, cop);
	eq[2] = vec_scal(cop, cop) - (radius * radius);
	eq[3] = eq[1] * eq[1] - 4 * eq[0] * eq[2];
	if (eq[3] < 0)
		return (-1);
	t[0] = (-eq[1] - sqrt(eq[3])) / (2 * eq[0]);
	t[1] = (-eq[1] + sqrt(eq[3])) / (2 * eq[0]);
	if (t[0] > EPSILON)
		return (t[0]);
	else if (t[1] > EPSILON)
		return (t[1]);
	return (-1);
}

bool	lat_intersection(t_elem elem, t_ray ray, t_point *point, double *t)
{
	t_vec	v;
	t_vec	base;
	t_vec	p;
	double	t_cyl;
	double	h;

	v = elem.direction;
	base = vec_minus(elem.origin, vec_mult(0.5 * elem.height, v));
	t_cyl = solve_cylinder_quadratic(ray, base, v, elem.radius);
	if (t_cyl > 0)
	{
		p = vec_plus(ray.origin, vec_mult(t_cyl, ray.direction));
		h = vec_scal(vec_minus(p, base), v);
		if (h < 0 || h > elem.height)
			return (false);
		compute_lateral_normal(p, base, v, point);
		*t = t_cyl;
		return (true);
	}
	return (false);
}
