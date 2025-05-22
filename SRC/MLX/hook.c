/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:44:23 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 11:44:24 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	key_hook(int keysym, t_rt *rt)
{
	if (keysym == XK_Escape)
		mlx_loop_end(rt->param.mlx);
	return (0);
}

int	handle_input(t_rt *rt)
{
	mlx_key_hook(rt->param.win, key_hook, rt);
	return (0);
}
