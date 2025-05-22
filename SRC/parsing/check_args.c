/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:48:37 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 12:03:36 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	int	lens1;
	int	lens2;
	int	i;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	i = 0;
	if (n == 0)
		return (0);
	while (lens1 - i >= 0 && lens2 - i >= 0 && i < (int)n)
	{
		if (s1[lens1 - i] != s2[lens2 - i])
			return (((unsigned char *)s1)[lens1 - i]
				- ((unsigned char *)s2)[lens2 - i]);
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	if (ac != 2)
		return (ft_putstr_fd("Error: Wrong number of arguments\n", 2), 1);
	if (ft_strrncmp(av[1], ".rt", 3))
		return (ft_putstr_fd("Error: Wrong file extension\n", 2), 1);
	return (0);
}
