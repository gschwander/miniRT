#include "miniRT.h"
#define EPSILON 1e-6

// bool cylinder_intersection(t_elem elem, t_ray ray, t_point *local_point, double *t_out)
// {
//     t_vec CO = vec_minus(ray.origin, elem.origin);
//     t_vec V = elem.direction;
//     t_vec D = ray.direction;

//     // ---- Surface latérale ----
//     t_vec Dp = vec_minus(ray.direction, vec_mult(vec_scal(ray.direction, elem.direction), elem.direction));
//     t_vec COp = vec_minus(CO, vec_mult(vec_scal(CO, V), V));
//     double a = vec_scal(Dp, Dp);
//     double b = 2 * vec_scal(Dp, COp);
//     double c = vec_scal(COp, COp) - elem.radius * elem.radius;
//     double delta = b * b - 4 * a * c;

//     double t_cyl = -1;
//     if (delta >= 0)
//     {
//         double sqrt_delta = sqrt(delta);
//         double t0 = (-b - sqrt_delta) / (2 * a);
//         double t1 = (-b + sqrt_delta) / (2 * a);

//         if (t0 > EPSILON)
//             t_cyl = t0;
//         else if (t1 > EPSILON)
//             t_cyl = t1;

//         if (t_cyl > 0)
//         {
//             t_vec P = vec_plus(ray.origin, vec_mult(t_cyl, D));
//             double h = vec_scal(vec_minus(P, elem.origin), V);
//             if (h >= 0 && h <= elem.height)
//             {
//                 t_vec P_proj = vec_plus(elem.origin, vec_mult(h, V));
//                 t_vec N = normalize(vec_minus(P, P_proj));
//                 *t_out = t_cyl;
//                 local_point->P = P;
//                 local_point->N = N;
//                 return true;
//             }
//         }
//     }

//     // ---- Capot inférieur (base) ----
//     t_vec base_center = elem.origin;
//     double denom = vec_scal(D, V);
//     double t_base = -1;
//     if (fabs(denom) > EPSILON)
//     {
//         double t = vec_scal(vec_minus(base_center, ray.origin), V) / denom;
//         if (t > EPSILON)
//         {
//             t_vec P = vec_plus(ray.origin, vec_mult(t, D));
//             if (norm2(vec_minus(P, base_center)) <= elem.radius * elem.radius)
//             {
//                 t_base = t;
//                 *t_out = t_base;
//                 local_point->P = P;
//                 local_point->N = vec_mult(-1, V); // normale vers le bas
//             }
//         }
//     }

//     // ---- Capot supérieur (top) ----
//     t_vec top_center = vec_plus(elem.origin, vec_mult(elem.height, V));
//     double t_top = -1;
//     if (fabs(denom) > EPSILON)
//     {
//         double t = vec_scal(vec_minus(top_center, ray.origin), V) / denom;
//         if (t > EPSILON)
//         {
//             t_vec P = vec_plus(ray.origin, vec_mult(t, D));
//             if (norm2(vec_minus(P, top_center)) <= elem.radius * elem.radius)
//             {
//                 // Choix du plus proche entre base et top
//                 if (t_base < 0 || t < t_base)
//                 {
//                     t_top = t;
//                     *t_out = t_top;
//                     local_point->P = P;
//                     local_point->N = V; // normale vers le haut
//                 }
//             }
//         }
//     }

//     return (t_cyl > 0 || t_base > 0 || t_top > 0);
// }

// static bool lat_intersection(t_elem elem, t_ray ray, t_point *point, double *t)
// {
//     t_vec CO;
//     CO = vec_minus(ray.origin, elem.origin);

//     // ---- Surface latérale ----
//     t_vec Dp = vec_minus(ray.direction, vec_mult(vec_scal(ray.direction, elem.direction), elem.direction));
//     t_vec COp = vec_minus(CO, vec_mult(vec_scal(CO, elem.direction), elem.direction));
//     double a = vec_scal(Dp, Dp);
//     double b = 2 * vec_scal(Dp, COp);
//     double c = vec_scal(COp, COp) - (elem.radius * elem.radius);
//     double delta = b * b - 4 * a * c;

//     double t_cyl = -1;
//     if (delta >= 0)
//     {
//         double sqrt_delta = sqrt(delta);
//         double t0 = (-b - sqrt_delta) / (2 * a);
//         double t1 = (-b + sqrt_delta) / (2 * a);

//         if (t0 > EPSILON)
//             t_cyl = t0;
//         else if (t1 > EPSILON)
//             t_cyl = t1;

//         if (t_cyl > 0)
//         {
//             t_vec P = vec_plus(ray.origin, vec_mult(t_cyl, ray.direction));
//             double h = vec_scal(vec_minus(P, elem.origin), elem.direction);
//             if (h >= 0 && h <= elem.height)
//             {
//                 t_vec P_proj = vec_plus(elem.origin, vec_mult(h, elem.direction));
//                 t_vec N = normalize(vec_minus(P, P_proj));
//                 *t = t_cyl;
//                 point->P = P;
//                 point->N = N;
//                 return true;
//             }
//         }
//     }
//     return false;
// }

static bool lat_intersection(t_elem elem, t_ray ray, t_point *point, double *t)
{
    // Nouveau référentiel : on part du centre et on calcule la base
    t_vec V = elem.direction;
    t_vec base = vec_minus(elem.origin, vec_mult(0.5 * elem.height, V));

    t_vec CO = vec_minus(ray.origin, base);

    // ---- Surface latérale ----
    t_vec Dp = vec_minus(ray.direction, vec_mult(vec_scal(ray.direction, V), V));
    t_vec COp = vec_minus(CO, vec_mult(vec_scal(CO, V), V));

    double a = vec_scal(Dp, Dp);
    double b = 2 * vec_scal(Dp, COp);
    double c = vec_scal(COp, COp) - (elem.radius * elem.radius);

    double delta = b * b - 4 * a * c;
    double t_cyl = -1;

    if (delta >= 0)
    {
        double sqrt_delta = sqrt(delta);
        double t0 = (-b - sqrt_delta) / (2 * a);
        double t1 = (-b + sqrt_delta) / (2 * a);

        if (t0 > EPSILON)
            t_cyl = t0;
        else if (t1 > EPSILON)
            t_cyl = t1;

        if (t_cyl > 0)
        {
            t_vec P = vec_plus(ray.origin, vec_mult(t_cyl, ray.direction));
            double h = vec_scal(vec_minus(P, base), V); // hauteur par rapport à la base

            if (h >= 0 && h <= elem.height)
            {
                t_vec P_proj = vec_plus(base, vec_mult(h, V)); // projection sur l’axe
                t_vec N = normalize(vec_minus(P, P_proj));     // normale latérale
                *t = t_cyl;
                point->P = P;
                point->N = N;
                return true;
            }
        }
    }
    return false;
}


bool cylinder_intersection(t_elem elem, t_ray ray, t_point *point, double *t)
{
    t_point local_point;
    bool has_inter[2];
    double min_t;

    min_t = 1E99;
    has_inter[0] = false;
    has_inter[1] = lat_intersection(elem, ray, &local_point, t);
    // has_inter[1] = cap_sup_intersection(elem, ray, &local_point, &t);
    // has_inter[1] = cap_inf_intersection(elem, ray, &local_point, &t);
    if (has_inter[1])
    {
        has_inter[0] = true;
        if (*t < min_t)
        {
            min_t = *t;
            *point = local_point;
        }
    }
    if (min_t < 0.1)
        return (false);
    return (has_inter[0]);
}
