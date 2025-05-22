/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:35:47 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 14:37:34 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_cylinder(t_elem elem)
{
	printf("Cylinder %d:\n", elem.id);
	printf("  Origin: (%f, %f, %f)\n", elem.origin.x, elem.origin.y,
		elem.origin.z);
	printf("  Direction: (%f, %f, %f)\n", elem.direction.x, elem.direction.y,
		elem.direction.z);
	printf("  Radius: %f\n", elem.radius);
	printf("  Height: %f\n", elem.height);
	printf("  Albedo: (%f, %f, %f)\n", elem.albedo.x, elem.albedo.y,
		elem.albedo.z);
}

void	alloc_cylinder(t_rt *rt, t_elem *cylinder, char **tab)
{
	cylinder->origin = parse_vec(rt, tab[1]);
	cylinder->direction = normalize(parse_vec(rt, tab[2]));
	if (cylinder->direction.x == 0 && cylinder->direction.y == 0
		&& cylinder->direction.z == 0)
		exit_error(rt, "Error: Invalid direction for cylinder");
	cylinder->radius = ft_atoi_double(tab[3]);
	if (cylinder->radius < 0)
		exit_error(rt, "Error: Invalid radius for cylinder");
	cylinder->height = ft_atoi_double(tab[4]);
	if (cylinder->height < 0)
		exit_error(rt, "Error: Invalid height for cylinder");
	cylinder->albedo = vec_div(parse_color(rt, tab[5]), 255);
	cylinder->intersection = &cylinder_intersection;
	cylinder->print = &print_cylinder;
}

void	parse_cylinder(t_rt *rt, char *line)
{
	char	**tab;
	int		i;

	i = find_elem_id(rt->scene.elem);
	rt->scene.elem[i].id = i + 1;
	tab = rt_ft_split(rt, line, ' ');
	if (tab[1] && tab[2] && tab[3] && tab[4])
	{
		alloc_cylinder(rt, &rt->scene.elem[i], tab);
		return ;
	}
	exit_error(rt, "Error: Invalid number of arguments for cylinder");
}
