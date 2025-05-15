/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:38:28 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/15 13:12:06 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_size_tab(t_rt *rt, char **tab)
{
	int	i;

	i = 0;
	if (!tab)
        exit_error(rt, "Error: Invalid number of arguments");
	while (tab[i])
		i++;
	if (i != 3)
        exit_error(rt, "Error: Invalid number of arguments");
}

void	check_color(t_rt * rt,char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
            exit_error(rt, "Error: Invalid color");
		i++;
	}
}

void	check_vec(t_rt * rt, char *line)
{
	int	i;
	int	point;

	i = 0;
	point = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && i == 0 && line[i] != '-')
            exit_error(rt,"Error: Invalid vector");
		else if (line[i] == '.')
			point++;
		i++;
	}
	if (point > 1)
        exit_error(rt,"Error: Invalid vector");
}

t_vec	parse_color(t_rt *rt, char *line)
{
	t_vec	color;
	char	**tab;

    tab = rt_ft_split(rt,line, ',');
	check_size_tab(rt,tab);
    check_color(rt, tab[0]);
    color.x = ft_atoi(tab[0]);
    check_color(rt, tab[1]);
	color.y = ft_atoi(tab[1]);
    check_color(rt , tab[2]);
	color.z = ft_atoi(tab[2]);
    if (color.x < 0 || color.y < 0 || color.z < 0 || color.x > 255 || color.y > 255 || color.z > 255)
		exit_error(rt, "Error: Invalid color");
	return (color);
}

t_vec	parse_vec(t_rt *rt, char *line)
{
    t_vec vec;
	char	**tab;

    vec = (t_vec){};
    tab = rt_ft_split(rt, line, ',');
	check_size_tab(rt, tab);
    check_vec(rt, tab[0]);
	vec.x = ft_atoi_double(tab[0]);
    check_vec(rt, tab[1]);
	vec.y = ft_atoi_double(tab[1]);
    check_vec(rt, tab[2]); 
    vec.z = ft_atoi_double(tab[2]);
	return (vec);
}

void	print_scene(t_rt *rt)
{
	int	i;

	i = 0;
	printf("Scene:\n");
	printf("  Ambient light: %f, (%f, %f, %f)\n", rt->scene.ambient_light.intensity,
		rt->scene.ambient_light.color.x, rt->scene.ambient_light.color.y,
		rt->scene.ambient_light.color.z);
	printf("  Camera: (%f, %f, %f), (%f, %f, %f), %f\n", rt->scene.camera.origin.x,
		rt->scene.camera.origin.y, rt->scene.camera.origin.z,
		rt->scene.camera.direction.x, rt->scene.camera.direction.y,
		rt->scene.camera.direction.z, rt->scene.camera.fov);
	printf("  Light: (%f, %f, %f), %f, (%f, %f, %f)\n", rt->scene.light.origin.x,
		rt->scene.light.origin.y, rt->scene.light.origin.z,
		rt->scene.light.intensity, rt->scene.light.color.x,
		rt->scene.light.color.y, rt->scene.light.color.z);
	while (i < rt->scene.elem_nb)
	{
		if (rt->scene.elem[i].id == 0)
			break ;
		if (rt->scene.elem[i].print)
			rt->scene.elem[i].print(rt->scene.elem[i]);
		i++;
	}
}
