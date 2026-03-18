/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:43:01 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 22:43:55 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/plane.h"

// bool	plane_intersect(t_plane_math *p, t_ray ray, t_hit *hit)
// {
// 	float	div;
// 	float	t;

// 	div = vec3_dot(ray.direction, p->normal);
// 	if (div > 1e-6)
// 	{
// 		t = -(vec3_dot(ray.origin, p->normal) + p->dot) / div;
// 		if (t > ray.t_min && t < ray.t_max)
// 		{
// 			hit->t = t;
// 			hit->color = p->color;
// 			hit->point = ray_at(ray, t);
// 			hit->normal = p->normal;
// 			hit->ray = ray;
// 			hit->obj = OBJ_PLANE;
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

bool	plane_intersect(t_plane_math *p, t_ray ray, t_hit *hit)
{
	float	div;
	float	t;

	div = vec3_dot(ray.direction, p->normal);
	if (div > 1e-6)
	{
		t_vec3 distance = vec3_sub(p->point, ray.origin);
		t = vec3_dot(distance, p->normal) / div;
		// t = -(vec3_dot(ray.origin, p->normal) + p->dot) / div;
		if (t > ray.t_min && t < ray.t_max)
		{
			hit->t = t;
			hit->color = p->color;
			hit->point = ray_at(ray, t);
			hit->normal = p->normal;
			hit->ray = ray;
			hit->obj = OBJ_PLANE;
			return (true);
		}
	}
	return (false);
}
