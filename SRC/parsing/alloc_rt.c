/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:48:41 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 12:04:59 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	creat_scene(t_rt *rt, t_file **file)
{
	rt->scene = (t_scene){0};
	check_files(rt, file);
	alloc_scene(rt, file);
}

void	creat_struct_parser_minirt(t_parser *parser)
{
	parser[0] = (t_parser){"sp ", parse_sphere};
	parser[1] = (t_parser){"pl ", parse_plane};
	parser[2] = (t_parser){"cy ", parse_cylinder};
	parser[3] = (t_parser){"A ", parse_amb_light};
	parser[4] = (t_parser){"C ", parse_camera};
	parser[5] = (t_parser){"L ", parse_light};
	parser[6] = (t_parser){NULL, NULL};
}

void	alloc_element(t_rt *rt, t_file **file)
{
	t_parser	parsers[7];
	t_file		*node;
	int			i;

	creat_struct_parser_minirt(parsers);
	node = *file;
	while (node)
	{
		i = 0;
		while (parsers[i].id)
		{
			if (!ft_strncmp(node->line, parsers[i].id,
					ft_strlen(parsers[i].id)))
			{
				parsers[i].parse(rt, node->line);
				break ;
			}
			i++;
		}
		node = node->next;
	}
}

void	alloc_rt(t_rt *rt, t_file **file)
{
	creat_scene(rt, file);
	alloc_element(rt, file);
}
