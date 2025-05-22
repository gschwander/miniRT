/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_rt_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:00:49 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 12:05:42 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_if_element(t_rt *rt, char *str)
{
	if (ft_strncmp(str, "sp ", 3) && ft_strncmp(str, "pl ", 3)
		&& ft_strncmp(str, "cy ", 3))
		exit_error(rt, "Error: Invalid line in the file");
}

void	check_files(t_rt *rt, t_file **file)
{
	t_file	*node;
	int		amb_light;
	int		light;
	int		camera;

	amb_light = 0;
	light = 0;
	camera = 0;
	node = *file;
	while (node)
	{
		if (!ft_strncmp(node->line, "A ", 2))
			amb_light++;
		else if (!ft_strncmp(node->line, "C ", 2))
			camera++;
		else if (!ft_strncmp(node->line, "L ", 2))
			light++;
		else
			check_if_element(rt, node->line);
		node = node->next;
	}
	if (amb_light != 1 || light != 1 || camera != 1)
		exit_error(rt, "Error: Invalid number of elements in the file");
}

void	init_null_element(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->scene.elem_nb)
	{
		rt->scene.elem[i].id = 0;
		i++;
	}
}

void	alloc_nbr_element(t_rt *rt)
{
	rt->scene.elem = wrap_malloc(rt, sizeof(t_elem) * rt->scene.elem_nb);
	init_null_element(rt);
}

void	alloc_scene(t_rt *rt, t_file **file)
{
	t_file	*node;

	node = *file;
	while (node)
	{
		if (!ft_strncmp(node->line, "sp ", 3))
			rt->scene.elem_nb++;
		else if (!ft_strncmp(node->line, "pl ", 3))
			rt->scene.elem_nb++;
		else if (!ft_strncmp(node->line, "cy ", 3))
			rt->scene.elem_nb++;
		node = node->next;
	}
	alloc_nbr_element(rt);
}
