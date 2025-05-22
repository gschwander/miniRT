/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:44:28 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 11:44:35 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx_pixel_put(t_rt *rt, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= rt->W || y >= rt->H || x < 0 || y < 0)
		return ;
	dst = rt->img.addr + (y * rt->img.line_length + x * (rt->img.bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	cast_img(t_rt *rt)
{
	unsigned int	color;
	int				i;
	int				j;
	int				index;

	i = rt->H;
	while (--i >= 0)
	{
		j = -1;
		while (++j < rt->W)
		{
			index = (i * rt->W + j) * 3;
			color = (rt->image[index]) * 256 * 256;
			color += (rt->image[index + 1]) * 256;
			color += (unsigned char)(rt->image[index + 2]);
			my_mlx_pixel_put(rt, j, i, color);
		}
	}
}

void	initial_projection(t_rt *rt)
{
	cast_img(rt);
	mlx_put_image_to_window(rt->param.mlx, rt->param.win, rt->img.img, 0, 0);
}

bool	struct_to_mlx(t_rt *rt)
{
	rt->param.mlx = mlx_init();
	if (!rt->param.mlx)
		return (false);
	rt->param.win = mlx_new_window(rt->param.mlx, rt->W, rt->H, "miniRT");
	if (!rt->param.win)
		return (free(rt->param.mlx), false);
	rt->img.img = mlx_new_image(rt->param.mlx, rt->W, rt->H);
	if (!rt->img.img)
		return (free(rt->param.win), free(rt->param.mlx), false);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
			&rt->img.line_length, &rt->img.endian);
	if (!rt->img.addr)
		return (free(rt->img.img), free(rt->param.win), free(rt->param.mlx),
			false);
	initial_projection(rt);
	handle_input(rt);
	mlx_hook(rt->param.win, 17, 0, mlx_loop_end, rt->param.mlx);
	mlx_loop(rt->param.mlx);
	mlx_destroy_image(rt->param.mlx, rt->img.img);
	mlx_destroy_window(rt->param.mlx, rt->param.win);
	mlx_destroy_display(rt->param.mlx);
	free(rt->param.mlx);
	return (true);
}
