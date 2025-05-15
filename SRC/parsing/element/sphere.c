/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:32:15 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/15 13:02:00 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void print_sphere(t_elem elem)
{
	printf("Sphere %d:\n", elem.id);
	printf("  Origin: (%f, %f, %f)\n", elem.origin.x, elem.origin.y, elem.origin.z);
	printf("  Radius: %f\n", elem.radius);
	printf("  Albedo: (%f, %f, %f)\n", elem.albedo.x, elem.albedo.y, elem.albedo.z);
}

void parse_sphere(t_rt *rt, char *line)
{
	char **tab;
	int i;
	
	i = find_elem_id(rt->scene.elem);
	rt->scene.elem[i].id = i + 1;
	tab = rt_ft_split(rt, line, ' ');
	if (tab[1] && tab[2] && tab[3])
	{
		rt->scene.elem[i].origin = parse_vec(rt, tab[1]);
		rt->scene.elem[i].radius = ft_atoi_double(tab[2]);
		if (rt->scene.elem[i].radius < 0)
			exit_error(rt, "Error: Invalid radius for sphere");
		rt->scene.elem[i].albedo = vec_mult(1.0 / 255, parse_color(rt, tab[3]));
		rt->scene.elem[i].intersection = &sphere_intersection;
		rt->scene.elem[i].print = &print_sphere;
		return;
	}
	exit_error(rt, "Error: Invalid number of arguments for sphere");
}