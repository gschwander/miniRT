/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:25:41 by kgriset           #+#    #+#             */
/*   Updated: 2025/05/19 11:45:26 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdint.h>
# include <stdbool.h>
# include "../42libC/libft/include/libft.h"
# include "../42libC/libC/include/libC.h"

typedef struct s_vec {
    double x;
    double y;
    double z;
} t_vec;

typedef struct s_ray {
    t_vec origin;
    t_vec direction;
} t_ray;

typedef struct s_point {
    t_vec P;
    t_vec N;
} t_point;

typedef struct s_ambient_light {
    double intensity;
    t_vec color;
} t_ambient_light;

typedef struct s_light {
    t_vec origin;
    double intensity;
    t_vec color;
} t_light;

typedef struct s_camera {
    t_vec origin;
    t_vec direction;
    double fov;
} t_camera;

typedef struct s_elem {
    int id;
    t_vec origin;
    double radius;
    t_vec albedo;
    t_vec normal;
    t_vec direction;
    double height;
    bool (*intersection)(struct s_elem, t_ray, t_point *, double *);
    void (*print)(struct s_elem);
} t_elem;

typedef struct s_scene {
    t_light light;    
    t_ambient_light ambient_light;
    t_camera camera;

    int elem_nb;
    t_elem *elem;
} t_scene; 

typedef struct s_data {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;


typedef struct s_param
{
	void			*mlx;
	void			*win;
}					t_param;

typedef struct s_rt {
    int W;
    int H;
    int i;
    int j;
    int fd_file;
    double fov;
    double min_t;
    unsigned char * image;
    t_link_list * graphic_heap;
    t_link_list * parsing_heap;
    t_link_list * current_heap;
    t_scene scene;
    t_param param;
    t_data img;
} t_rt;


// vector.c 
t_vec vec_plus(const t_vec a, const t_vec b);
t_vec vec_minus(const t_vec a, const t_vec b);
t_vec vec_mult(double k, const t_vec v);
t_vec vec_div(const t_vec v, double k);
double vec_scal(const t_vec a, const t_vec b);

// vector1.c
double norm2(const t_vec v);
t_vec normalize(const t_vec v);
t_vec vec_m_vec(const t_vec a, const t_vec b);
t_vec cross(const t_vec a, const t_vec b);

// wrap_malloc.c
void	*wrap_malloc(t_rt *rt, size_t size);
void free_heap(t_rt *rt);
t_link_list *init_alloc(t_link_list **list);

// miniRT.c
unsigned char * render (t_rt * rt);
bool sphere_intersection(t_elem elem, t_ray ray, t_point *local_point, double *t);
bool plane_intersection(t_elem elem, t_ray ray, t_point *local_point, double *t);
bool cylinder_intersection(t_elem elem, t_ray ray, t_point *local_point, double *t);

// intersection/cylinder.c
bool cylinder_intersection(t_elem elem, t_ray ray, t_point *point, double *t);

// intersection/lat_intersection.c
bool lat_intersection(t_elem elem, t_ray ray, t_point *point, double *t);

// bmp.c
void save_img(t_rt * rt, const unsigned char * pixels, int W, int H); // rgb pixel
// exit_error.c
void exit_error(t_rt * rt, char * msg);
// rt_strdup.c
char	*rt_ft_strdup(t_rt *rt, const char *s);
// rt_ft_strtrim.c
char	*rt_ft_strtrim(t_rt *rt, char const *s1, char const *set);
// rt_ft_substr.c
char	*rt_ft_substr(t_rt *rt, char const *s, unsigned int start, size_t len);
// rt_ft_split.c
char	**rt_ft_split(t_rt *rt, char const *s, char c);

// find_elem_id.c
int find_elem_id(t_elem *elem);

// img.c
bool struct_to_mlx(t_rt *rt);

// hook.c
int handle_input(t_rt *rt);

#endif