/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:38:28 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/15 12:52:29 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// int	check_size_tab(char **tab)
void	check_size_tab(t_rt *rt, char **tab)
{
	int	i;

	i = 0;
	if (!tab)
        exit_error(rt, "Error: Invalid number of arguments");
		// return (0);
	while (tab[i])
		i++;
	if (i != 3)
        exit_error(rt, "Error: Invalid number of arguments");
		// return (/* free_tab_char(tab),  */ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	// return (i);
}

void	check_color(t_rt * rt,char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
            exit_error(rt, "Error: Invalid color");
			// return (ft_putstr_fd("Error: Invalid color\n", 2), 1);
		i++;
	}
	// return (0);
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
			// return (ft_putstr_fd("Error: Invalid vector\n", 2), 1);
		else if (line[i] == '.')
			point++;
		i++;
	}
	if (point > 1)
        exit_error(rt,"Error: Invalid vector");
		// return (ft_putstr_fd("Error: Invalid vector\n", 2), 1);
	// return (0);
}

// t_vec	*parse_color(t_rt *rt, char *line)
t_vec	parse_color(t_rt *rt, char *line)
{
	// t_vec	*color;
	t_vec	color;
	char	**tab;

	// tab = ft_split(line, ',');
    tab = rt_ft_split(rt,line, ',');
	check_size_tab(rt,tab);
	// if (check_size_tab(tab) != 3)
	// 	return (NULL);
	// color = wrap_malloc(rt, sizeof(t_vec));
	// if (!color)
	// 	return (free_tab_char(tab), ft_putstr_fd("Error: Memory allocation failed\n", 2), NULL);
    check_color(rt, tab[0]);
	// if (check_color(tab[0]))
	// 	return (free_tab_char(tab), NULL);
	// color->x = ft_atoi(tab[0]);
    color.x = ft_atoi(tab[0]);
    check_color(rt, tab[1]);
	// if (check_color(tab[1]))
	// 	return (free_tab_char(tab), NULL);
	// color->y = ft_atoi(tab[1]);
	color.y = ft_atoi(tab[1]);
    check_color(rt , tab[2]);
	// if (check_color(tab[2]))
	// 	return (free_tab_char(tab), NULL);
	// color->z = ft_atoi(tab[2]);
	color.z = ft_atoi(tab[2]);
	// free_tab_char(tab);
	// if (color->x < 0 || color->y < 0 || color->z < 0 || color->x > 255
	// 	|| color->y > 255 || color->z > 255)
	// 	return (ft_putstr_fd("Error: Invalid color\n", 2), NULL);
    if (color.x < 0 || color.y < 0 || color.z < 0 || color.x > 255 || color.y > 255 || color.z > 255)
		exit_error(rt, "Error: Invalid color");
	return (color);
}

t_vec	parse_vec(t_rt *rt, char *line)
{
	// t_vec	*vec;
    t_vec vec;
	char	**tab;

    vec = (t_vec){};
	// tab = ft_split(line, ',');
    tab = rt_ft_split(rt, line, ',');
	check_size_tab(rt, tab);
	// if (check_size_tab(tab) != 3)
		// return (NULL);
	// vec = wrap_malloc(rt, sizeof(t_vec));
	// if (check_vec(tab[0]))
	// 	return (free_tab_char(tab), NULL);
    check_vec(rt, tab[0]);
	// vec->x = ft_atoi_double(tab[0]);
	vec.x = ft_atoi_double(tab[0]);
	// if (check_vec(tab[1]))
	// 	return (free_tab_char(tab), NULL);
    check_vec(rt, tab[1]);
	// vec->y = ft_atoi_double(tab[1]);
	vec.y = ft_atoi_double(tab[1]);
	// if (check_vec(tab[2]))
	// 	return (free_tab_char(tab), NULL);
	// vec->z = ft_atoi_double(tab[2]);
    check_vec(rt, tab[2]); 
    vec.z = ft_atoi_double(tab[2]);
	// free_tab_char(tab);
	return (vec);
}

// void	free_tab_char(char **tab)
// {
// 	int	i;
//
// 	i = 0;
// 	while (tab[i])
// 		free(tab[i++]);
// 	free(tab);
// }

void	print_scene(t_rt *rt)
{
	int	i;

	i = 0;
	while (i < rt->scene.elem_nb)
	{
		if (rt->scene.elem[i].id == 0)
			break ;
		if (rt->scene.elem[i].print)
			rt->scene.elem[i].print(rt->scene.elem[i]);
		i++;
	}
}

// int find_elem_id(void *elem)
// {
//     int i;

//     i = 0;
//     if (elem[0]->id == 0)
//         return (i);
//     while (elem[i])
//     {
//         if (elem[i]->id == 0)
//             return (i);
//         i++;
//     }
//     return (i);
// }
