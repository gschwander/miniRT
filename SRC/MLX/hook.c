#include "miniRT.h"

// static void	hook_rotation(int keysym, t_projection *project)
// {
// 	if (keysym == XK_w)
// 		project->rotax += 10;
// 	if (keysym == XK_s)
// 		project->rotax -= 10;
// 	if (keysym == XK_a)
// 		project->rotay += 10;
// 	if (keysym == XK_d)
// 		project->rotay -= 10;
// 	if (keysym == XK_z)
// 		project->rotaz += 10;
// 	if (keysym == XK_c)
// 		project->rotaz -= 10;
// }

static int	key_hook(int keysym, t_rt *rt)
{
	if (keysym == XK_Escape)
		mlx_loop_end(rt->param.mlx);
	// if (keysym == XK_Shift_L)
	// 	data->grid.project.hauteur *= 1.2;
	// if (keysym == XK_Control_L)
	// 	data->grid.project.hauteur /= 1.2;
	// if (keysym == XK_Left)
	// 	data->grid.project.translax += 10;
	// if (keysym == XK_Right)
	// 	data->grid.project.translax -= 10;
	// if (keysym == XK_Down)
	// 	data->grid.project.translay -= 10;
	// if (keysym == XK_Up)
	// 	data->grid.project.translay += 10;
	// if (keysym == XK_w || keysym == XK_s || keysym == XK_a || keysym == XK_d
	// 	|| keysym == XK_z || keysym == XK_c)
	// 	hook_rotation(keysym, &data->grid.project);
	// ft_project(data);
	return (0);
}

// static int	mouse_hook(int keysym, int x, int y, t_rt *rt)
// {
// 	(void)x;
// 	(void)y;
// 	if (keysym == 5)
// 		data->grid.project.zoom *= 1.2;
// 	if (keysym == 4)
// 		data->grid.project.zoom /= 1.2;
// 	ft_project(data);
// 	return (0);
// }

int	handle_input(t_rt *rt)
{
	mlx_key_hook(rt->param.win, key_hook, rt);
	// mlx_mouse_hook(rt->param.win, mouse_hook, rt);
	return (0);
 }
