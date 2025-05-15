/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:33:07 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/15 12:58:40 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void print_plane(t_elem elem)
{
	printf("Plane %d:\n", elem.id);
	printf("  Origin: (%f, %f, %f)\n", elem.origin.x, elem.origin.y, elem.origin.z);
	printf("  Normal: (%f, %f, %f)\n", elem.normal.x, elem.normal.y, elem.normal.z);
	printf("  Albedo: (%f, %f, %f)\n", elem.albedo.x, elem.albedo.y, elem.albedo.z);
}

void parse_plane(t_rt *rt, char *line)
{
	char **tab;
	int i;
	
	i = find_elem_id(rt->scene.elem);
	rt->scene.elem[i].id = i + 1;
	tab = rt_ft_split(rt, line, ' ');
	if (tab[1] && tab[2] && tab[3])
	{
		rt->scene.elem[i].origin = parse_vec(rt, tab[1]);
		rt->scene.elem[i].normal = parse_vec(rt, tab[2]);
		if (rt->scene.elem[i].normal.x == 0 && rt->scene.elem[i].normal.y == 0 && rt->scene.elem[i].normal.z == 0)
			exit_error(rt, "Error: Invalid normal for plane");
		rt->scene.elem[i].albedo = vec_mult(1.0 / 255, parse_color(rt, tab[3]));
		rt->scene.elem[i].intersection = &plane_intersection;
		rt->scene.elem[i].print = &print_plane;
		return;
	}
	exit_error(rt, "Error: Invalid number of arguments for plane");
}
	
