/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:30:27 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 11:46:22 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_light(t_rt *rt, char *line)
{
	char	**tab;

	tab = rt_ft_split(rt, line, ' ');
	if (tab[1] && tab[2] && tab[3])
	{
		rt->scene.light.origin = parse_vec(rt, tab[1]);
		rt->scene.light.intensity = ft_atoi_double(tab[2]);
		if (rt->scene.light.intensity < 0 || rt->scene.light.intensity > 1)
			exit_error(rt, "Error: Invalid ratio for light");
		rt->scene.light.color = parse_color(rt, tab[3]);
		return ;
	}
	exit_error(rt, "Error: Invalid number of arguments for light");
}
