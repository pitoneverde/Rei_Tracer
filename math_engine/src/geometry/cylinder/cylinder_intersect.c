/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:48:43 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/21 21:55:40 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "geometry/cylinder.h"
#include "geometry/intersection.h"

bool	cylinder_intersect(t_cylinder_math *c, t_ray ray, t_hit *hit)
{
	t_hit		down;
	t_hit		up;
	t_quadratic	cy_eq;

	up.t = INFINITY;
	down.t = INFINITY;
	if (plane_intersect(&c->disk_down, ray, &down))
	{
		float d_sq = vec3_distance_sq(ray_at(ray, down.t), c->disk_down.point);
		if (d_sq > c->radius_sq)
			return (false);
		*hit = down;
		hit->obj = OBJ_CYLINDER;
	}
	if (plane_intersect(&c->disk_up, ray, &up) && up.t < down.t)
	{
		float d_sq = vec3_distance_sq(ray_at(ray, up.t), c->disk_up.point);
		if (d_sq > c->radius_sq)
			return (false);
		*hit = up;
		hit->obj = OBJ_CYLINDER;
	}
	// cylinder side formula test
	t_vec3	delta_rej = vec3_reject(vec3_sub(ray.origin, c->disk_down.point), c->axis);
	t_vec3	dir_rej = vec3_reject(ray.direction, c->axis);
	cy_eq.a = vec3_length_sq(dir_rej);
	cy_eq.b = 2.0f * (vec3_dot(delta_rej, dir_rej));
	cy_eq.c = vec3_length_sq(delta_rej) - c->radius_sq;
	cy_eq.x1 = NAN;
	if (!solve_quadratic(&cy_eq))
		return (false);
	if (cy_eq.x0 < ray.t_min || cy_eq.x0 > ray.t_max)
	{
		if (cy_eq.x1 < ray.t_min || cy_eq.x1 > ray.t_max)
			return (false);
		cy_eq.x0 = cy_eq.x1;
	}
	if (cy_eq.x0 < hit->t)
	{
		hit->t = cy_eq.x0;
		hit->point = ray_at(ray, hit->t);
		float h = vec3_dot(vec3_sub(hit->point, c->disk_down.point), c->axis);
		if (h > c->half_height || h < -c->half_height)
			return (false);
		hit->color = c->color;
		hit->ray = ray;
		hit->normal = vec3_add(delta_rej, vec3_scale(dir_rej, hit->t));
		hit->obj = OBJ_CYLINDER;
	}
	return (true);
}
