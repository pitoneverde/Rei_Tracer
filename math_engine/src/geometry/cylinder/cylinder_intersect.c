/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:48:43 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/20 20:04:53 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "geometry/cylinder.h"

bool	cylinder_intersect(t_cylinder_math *c, t_ray ray, t_hit *hit)
{
	t_hit	down;
	t_hit	up;

	up.t = INFINITY;
	down.t = INFINITY;
	if (plane_intersect(&c->disk_down, ray, &down))
	{
		float d_sq = vec3_distance_sq(ray_at(ray, down.t), c->disk_down.point);
		if (d_sq > c->radius_sq)
			return (false);
		*hit = down;
		hit->obj = OBJ_CYLINDER;
		return (true);
	}
	if (plane_intersect(&c->disk_up, ray, &up) && up.t < down.t)
	{
		float d_sq = vec3_distance_sq(ray_at(ray, up.t), c->disk_up.point);
		if (d_sq > c->radius_sq)
			return (false);
		*hit = up;
		hit->obj = OBJ_CYLINDER;
		return (true);
	}

	// cylinder side formula test
	return (false);
}
