#include "miniRT.h"
#define EPSILON 1e-6

static bool cap_inf_intersection(t_elem elem, t_ray ray, t_point *point, double *t)
{
    t_vec V = elem.direction;
    t_vec base = vec_minus(elem.origin, vec_mult(0.5 * elem.height, V));
    t_vec D = ray.direction;
    double denom = vec_scal(D, V);
    double t_base = -1;
    if (fabs(denom) > EPSILON)
    {
        double t1 = vec_scal(vec_minus(base, ray.origin), V) / denom;
        if (t1 > EPSILON)
        {
            t_vec P = vec_plus(ray.origin, vec_mult(t1, D));
            if (norm2(vec_minus(P, base)) <= elem.radius * elem.radius)
            {
                t_base = t1;
                *t = t_base;
                point->P = P;
                point->N = vec_mult(-1, V); // normale vers le bas
                return true;
            }
        }
    }
    return false;
}

static bool cap_sup_intersection(t_elem elem, t_ray ray, t_point *point, double *t)
{
    t_vec top_center = vec_plus(elem.origin, vec_mult(0.5 * elem.height, elem.direction));
    t_vec V = elem.direction;
    t_vec D = ray.direction;
    double denom = vec_scal(D, V);
    double t_top = -1;
    if (fabs(denom) > EPSILON)
    {
        double t1 = vec_scal(vec_minus(top_center, ray.origin), V) / denom;
        if (t1 > EPSILON)
        {
            t_vec P = vec_plus(ray.origin, vec_mult(t1, D));
            if (norm2(vec_minus(P, top_center)) <= elem.radius * elem.radius)
            {
                if (t_top < 0 || t1 < t_top)
                {
                    t_top = t1;
                    *t = t_top;
                    point->P = P;
                    point->N = V;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool has_inter(double *t, double *min_t, t_point *point, t_point local_point)
{
    if (*t < *min_t)
    {
        *min_t = *t;
        point->P = local_point.P;
        point->N = local_point.N;
    }
    return (true);
}


bool cylinder_intersection(t_elem elem, t_ray ray, t_point *point, double *t)
{
    t_point local_point;
    bool e;
    double min_t;

    min_t = 1E99;
    e = false;
    if (lat_intersection(elem, ray, &local_point, t))
        e = has_inter(t, &min_t, point, local_point);
    if (cap_sup_intersection(elem, ray, &local_point, t))
        e = has_inter(t, &min_t, point, local_point);
    if (cap_inf_intersection(elem, ray, &local_point, t))
        e = has_inter(t, &min_t, point, local_point);
    return (e);
}
