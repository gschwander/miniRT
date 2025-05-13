#include "miniRT.h"

bool intersection (t_rt *rt, t_ray ray)
{
    // cal eq si intersection ou non
    double delta;
    double a;
    double b;
    double c;
    // double t1;
    double t2;

    a = 1;
    b = 2 * vec_scal(ray.direction, vec_minus(ray.origin, rt->scene.spheres[0].origin));
    c = norm2(vec_minus(ray.origin, rt->scene.spheres[0].origin)) - rt->scene.spheres[0].radius * rt->scene.spheres[0].radius;
    delta = - b * b - 4 * a * c;
    if (delta < 0)
        return (false);
    // t1 = (- b - sqrt(delta)) / (2 * a);
    t2 = (- b + sqrt(delta)) / (2 * a);
    if (t2 < 0)
        return (false);
    return (true);
}

t_vec cal_dir_ray(t_rt *rt, int i, int j)
{
    t_vec vec;
    
    vec.x = j - rt->W / 2 - rt->scene.camera.origin.x;
    vec.y = i - rt->H / 2 -rt->scene.camera.origin.y;
    vec.z = - rt->W / (2 * tan((rt->scene.camera.fov)/2));
    return (vec);
}

unsigned char * render (t_rt *rt)
{
    unsigned char * image;
    t_ray ray;
    int i;
    int j;

    image = wrap_malloc(rt, sizeof(unsigned char) * rt->W * rt->H * 3);
    i = -1;
    while (++i < rt->H)
    {
        j = -1;
        while (++j < rt->W)
        {
            ray = (t_ray){};
            ray.direction = normalize(cal_dir_ray(rt, i, j));
            if (intersection(rt, ray))
            {
                image[((rt->H-i-1)*rt->W + j) * 3 + 0] = 255;
                image[((rt->H-i-1)*rt->W + j) * 3 + 1] = 255;
                image[((rt->H-i-1)*rt->W + j) * 3 + 2] = 255;
            }
        }
    }
    return (image);
}
