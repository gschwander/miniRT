/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atreus <atreus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:18:50 by kgriset           #+#    #+#             */
/*   Updated: 2025/06/18 12:31:35 by atreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	exit_error(t_rt *rt, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	if (rt->fd_file)
		close(rt->fd_file);
	free_heap(rt);
	exit(EXIT_FAILURE);
}
