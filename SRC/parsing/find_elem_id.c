/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_elem_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:03:48 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 12:06:13 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	find_elem_id(t_elem *elem)
{
	int	i;

	i = 0;
	if (elem[0].id == 0)
		return (i);
	while (1)
	{
		if (elem[i].id == 0)
			return (i);
		i++;
	}
	return (i);
}
