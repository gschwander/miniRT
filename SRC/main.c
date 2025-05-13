/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:48:28 by gschwand          #+#    #+#             */
/*   Updated: 2025/04/30 08:54:13 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// int main (int ac,char ** av)
// {
//     t_rt rt;
//     if (check_args(ac, av))
// 		return (1);
//     rt = (t_rt){};
//     rt.graphic_heap = init_alloc(&rt.graphic_heap); 
//     rt.parsing_heap = init_alloc(&rt.parsing_heap);  
//     uint64_t seeds[2];
//     entropy_getbytes((void*)seeds,sizeof(seeds));
//     pcg32_srandom_r(&rt.rng,seeds[0],seeds[1]);
//     rt.current_heap = rt.parsing_heap;
//     parsing_minirt(&rt,av[1]);
//     // rt.fov = 80 * M_PI / 180;
//     rt.W = 1024;
//     rt.H = 1024;
//     rt.current_heap = rt.graphic_heap;
//     save_img(&rt, render(&rt), rt.W, rt.H);
//     close(rt.fd_file);
//     free_heap(&rt);
//     return 0;
// }


int main(int ac, char **av)
{
	t_rt rt;
	
	if (check_args(ac, av))
		return(1);
	rt = (t_rt){};
	rt.graphic_heap = init_alloc(&rt.graphic_heap);
	rt.parsing_heap = init_alloc(&rt.parsing_heap);
	rt.current_heap = rt.parsing_heap;
	parsing_minirt(&rt, av[1]);
	rt.W = 1024;
	rt.H = 1024;
	rt.current_heap = rt.graphic_heap;
	save_img(&rt, render(&rt), rt.W, rt.H);
	close(rt.fd_file);
	free_heap(&rt);
	return (0);
}