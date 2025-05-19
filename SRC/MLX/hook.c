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
