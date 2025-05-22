/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:54:15 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 11:57:17 by gschwand         ###   ########.fr       */
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

void	check_color(t_rt *rt, char *line)
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

void	check_vec(t_rt *rt, char *line)
{
	int	i;
	int	point;

	i = 0;
	point = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && i == 0 && line[i] != '-')
			exit_error(rt, "Error: Invalid vector");
		else if (line[i] == '.')
			point++;
		i++;
	}
	if (point > 1)
		exit_error(rt, "Error: Invalid vector");
}
