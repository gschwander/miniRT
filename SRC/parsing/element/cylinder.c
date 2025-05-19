/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:35:47 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/19 09:48:21 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void print_cylinder(t_elem elem)
{
	printf("Cylinder %d:\n", elem.id);
	printf("  Origin: (%f, %f, %f)\n", elem.origin.x, elem.origin.y, elem.origin.z);
	printf("  Direction: (%f, %f, %f)\n", elem.direction.x, elem.direction.y, elem.direction.z);
	printf("  Radius: %f\n", elem.radius);
	printf("  Height: %f\n", elem.height);
	printf("  Albedo: (%f, %f, %f)\n", elem.albedo.x, elem.albedo.y, elem.albedo.z);
}

void parse_cylinder(t_rt *rt, char *line)
{
	char **tab;
	int i;
	
	i = find_elem_id(rt->scene.elem);
	rt->scene.elem[i].id = i + 1;
	tab = rt_ft_split(rt, line, ' ');
	if (tab[1] && tab[2] && tab[3] && tab[4])
	{
		rt->scene.elem[i].origin = parse_vec(rt, tab[1]);
		rt->scene.elem[i].direction = normalize(parse_vec(rt, tab[2]));
		if (rt->scene.elem[i].direction.x == 0 && rt->scene.elem[i].direction.y == 0 && rt->scene.elem[i].direction.z == 0)
			exit_error(rt, "Error: Invalid direction for cylinder");
		rt->scene.elem[i].radius = ft_atoi_double(tab[3]);
		if (rt->scene.elem[i].radius < 0)
			exit_error(rt, "Error: Invalid radius for cylinder");
		rt->scene.elem[i].height = ft_atoi_double(tab[4]);
		if (rt->scene.elem[i].height < 0)
			exit_error(rt, "Error: Invalid height for cylinder");
		rt->scene.elem[i].albedo = vec_mult(1.0 / 255, parse_color(rt, tab[5]));
		rt->scene.elem[i].intersection = &cylinder_intersection;
		rt->scene.elem[i].print = &print_cylinder;
		return;
	}
	exit_error(rt, "Error: Invalid number of arguments for cylinder");
}