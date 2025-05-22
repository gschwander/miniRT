/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ft_strdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:43:26 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 11:43:27 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*rt_ft_strdup(t_rt *rt, const char *s)
{
	char			*s_dupe;
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	s_dupe = wrap_malloc(rt, (i + 1) * sizeof(char));
	if (!s_dupe)
		return (0);
	i = 0;
	while (s[i])
	{
		s_dupe[i] = s[i];
		i++;
	}
	s_dupe[i] = s[i];
	return (s_dupe);
}
