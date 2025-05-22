/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:50:15 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 15:28:38 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define INTENSITY_L 1E4

bool	shadow(t_rt *rt, t_point *point)
{
	t_ray	ray_light;
	bool	has_inter_light;
	t_point	point_light;
	int		elem_id;
	double	d_light2;

	ray_light.origin = vec_plus(point->p, vec_mult(0.01, point->n));
	ray_light.direction = normalize(vec_minus(rt->scene.light.origin,
				point->p));
	has_inter_light = intersections(rt, ray_light, &point_light, &elem_id);
	d_light2 = norm2(vec_minus(rt->scene.light.origin, point->p));
	if (has_inter_light && rt->min_t * rt->min_t < d_light2)
		return (true);
	return (false);
}

void	color_to_img(t_rt *rt, t_vec color)
{
	int	idx;

	color.x = pow(color.x, 1 / 2.2);
	color.y = pow(color.y, 1 / 2.2);
	color.z = pow(color.z, 1 / 2.2);
	idx = ((rt->h - rt->i - 1) * rt->w + rt->j) * 3;
	rt->image[idx + 0] = (unsigned char)(fmin(255., fmax(0., color.x)));
	rt->image[idx + 1] = (unsigned char)(fmin(255., fmax(0., color.y)));
	rt->image[idx + 2] = (unsigned char)(fmin(255., fmax(0., color.z)));
}

void	get_color(t_rt *rt, t_point point, int elem_id)
{
	t_elem	s;
	t_vec	ambient;
	t_vec	ldir;
	double	diff_coeff;
	t_vec	diffuse;

	s = rt->scene.elem[elem_id];
	ambient = vec_mult(255 * rt->scene.ambient_light.intensity,
			vec_m_vec(s.albedo, rt->scene.ambient_light.color));
	ldir = normalize(vec_minus(rt->scene.light.origin, point.p));
	diff_coeff = fmax(0., vec_scal(ldir, point.n))
		/ norm2(vec_minus(rt->scene.light.origin, point.p));
	diffuse = vec_mult(INTENSITY_L * diff_coeff, vec_m_vec(s.albedo,
				rt->scene.light.color));
	if (shadow(rt, &point))
		color_to_img(rt, ambient);
	else
		color_to_img(rt, vec_plus(ambient, vec_mult(255, diffuse)));
}

void	color_nul(t_rt *rt)
{
	rt->image[((rt->h - rt->i - 1) * rt->w + rt->j) * 3 + 0] = 0;
	rt->image[((rt->h - rt->i - 1) * rt->w + rt->j) * 3 + 1] = 0;
	rt->image[((rt->h - rt->i - 1) * rt->w + rt->j) * 3 + 2] = 0;
}

unsigned char	*render(t_rt *rt)
{
	t_ray	ray;
	t_point	point;
	int		elem_id;

	elem_id = 0;
	rt->image = wrap_malloc(rt, sizeof(unsigned char) * rt->w * rt->h * 3);
	rt->i = -1;
	while (++rt->i < rt->h)
	{
		rt->j = -1;
		while (++rt->j < rt->w)
		{
			ray.origin = rt->scene.camera.origin;
			ray.direction = normalize(cal_dir_ray(rt));
			if (intersections(rt, ray, &point, &elem_id))
			{
				get_color(rt, point, elem_id);
			}
			else
				color_nul(rt);
		}
	}
	return (rt->image);
}
