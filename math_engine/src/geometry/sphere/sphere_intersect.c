/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:01:42 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 12:51:12 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/sphere.h"
#include <math.h>
#include <stdio.h>

bool sphere_intersect(t_sphere_math *s, t_ray ray, t_hit *hit)
{
	t_quadratic	sphere_eq;
	t_vec3		distance;

	distance = vec3_sub(ray.origin, s->center);
	sphere_eq.a = vec3_length_sq(ray.direction);	//1 if ray.direction is normalized
	sphere_eq.b = 2 * vec3_dot(ray.direction, distance);
	sphere_eq.c = vec3_length_sq(distance) - s->radius_sq;
	sphere_eq.x1 = NAN;
	if (!solve_quadratic(&sphere_eq))
		return (false);
	if (sphere_eq.x0 < 0.0f)
	{
		sphere_eq.x0 = sphere_eq.x1;
		if (sphere_eq.x0 < 0.0f)
			return (false);
	}
	hit->t = sphere_eq.x0;
	hit->color = s->color;
	hit->point = vec3_add(ray.origin, vec3_scale(ray.direction, hit->t));
	hit->normal = vec3_normalize(vec3_sub(hit->point, s->center));
	hit->ray = ray;
	hit->obj = OBJ_SPHERE;
	return (true);
}