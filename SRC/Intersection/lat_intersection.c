#include "miniRT.h"
#define EPSILON 1e-6

static void compute_lateral_normal(t_vec P, t_vec base, t_vec V, t_point *point)
{
    double h;
    t_vec P_proj;
    t_vec N;

    h = vec_scal(vec_minus(P, base), V);
    P_proj = vec_plus(base, vec_mult(h, V));
    N = normalize(vec_minus(P, P_proj));
    point->P = P;
    point->N = N;
}

static double solve_cylinder_quadratic(t_ray ray, t_vec base, t_vec V, double radius)
{
    t_vec CO;
    t_vec Dp;
    t_vec COp;
    double eq[4];
    double t[2];

    CO = vec_minus(ray.origin, base);
    Dp = vec_minus(ray.direction, vec_mult(vec_scal(ray.direction, V), V));
    COp = vec_minus(CO, vec_mult(vec_scal(CO, V), V));
    eq[0] = vec_scal(Dp, Dp);
    eq[1] = 2 * vec_scal(Dp, COp);
    eq[2] = vec_scal(COp, COp) - (radius * radius);
    eq[3] = eq[1] * eq[1] - 4 * eq[0] * eq[2];
    if (eq[3] < 0)
        return (-1);
    t[0] = (-eq[1] - sqrt(eq[3])) / (2 * eq[0]);
    t[1] = (-eq[1] + sqrt(eq[3])) / (2 * eq[0]);
    if (t[0] > EPSILON)
        return (t[0]);
    else if (t[1] > EPSILON)
        return (t[1]);
    return (-1);
}

bool lat_intersection(t_elem elem, t_ray ray, t_point *point, double *t)
{
    t_vec V;
    t_vec base;
    t_vec P;
    double t_cyl;
    double h;

    V = elem.direction;
    base = vec_minus(elem.origin, vec_mult(0.5 * elem.height, V));
    t_cyl = solve_cylinder_quadratic(ray, base, V, elem.radius);

    if (t_cyl > 0)
    {
        P = vec_plus(ray.origin, vec_mult(t_cyl, ray.direction));
        h = vec_scal(vec_minus(P, base), V);
        if (h < 0 || h > elem.height)
            return (false);
        compute_lateral_normal(P, base, V, point);
        *t = t_cyl;
        return (true);
    }
    return (false);
}
