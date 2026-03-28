/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:48:43 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/28 01:10:59 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "geometry/cylinder.h"
#include "geometry/intersection.h"

static bool	disk_intersect(t_plane_math *d, t_ray ray, t_hit *hit, float r_sq);
static bool	side_int(t_cylinder_math *c, t_ray ray, t_hit *hit, t_quad *cy_eq);
static bool	check_bounds(t_cylinder_math *c, t_hit hit);

// Performs ray-cylinder intersections: first it checks the two bases' disks
// Then it starts from the implicit formula ∥(P−C)−((P−C)⋅a)a∥=R
// (points on the lateral surface), combined with the ray equation to get a
// quadratic equation in t. delta=O−C, the _rej vars are the orthogonal
// components of the ray direction and delta. It then checks if the point 
// falls into the height bounds [0, height] from the lower base disk. 
// It replaces the resulting t_hit struct if the next step yields 
// a smaller t, and returns the one with the smallest t at the end 
// (maybe could be optimized with some early returns later)
bool	cylinder_intersect(t_cylinder_math *c, t_ray ray, t_hit *hit)
{
	t_hit	tmp_hit;
	t_quad	cy_eq;

	tmp_hit.t = INFINITY;
	if (disk_intersect(&c->disk_down, ray, &tmp_hit, c->radius_sq))
	{
		if (tmp_hit.t < hit->t)
			*hit = tmp_hit;
	}
	if (disk_intersect(&c->disk_up, ray, &tmp_hit, c->radius_sq))
	{
		if (tmp_hit.t < hit->t)
			*hit = tmp_hit;
	}
	if (side_int(c, ray, &tmp_hit, &cy_eq))
	{
		if (tmp_hit.t < hit->t && check_bounds(c, tmp_hit))
			*hit = tmp_hit;
	}
	return (true);
}

// checks if height is within range
static bool	check_bounds(t_cylinder_math *c, t_hit hit)
{
	float	h;

	h = vec3_dot(vec3_sub(hit.point, c->disk_down.point), c->axis);
	if (h <= 0.0f || h >= c->height)
		return (false);
	return (true);
}

// just a ray-plane intersection bounded by the cylinder radius squared
static bool	disk_intersect(t_plane_math *d, t_ray ray, t_hit *hit, float r_sq)
{
	float	d_sq;

	if (plane_intersect(d, ray, hit))
	{
		d_sq = vec3_distance_sq(ray_at(ray, hit->t), d->point);
		if (d_sq > r_sq)
			return (false);
		hit->obj = OBJ_CYLINDER;
		return (true);
	}
	return (false);
}

// cylinder side intersection test
static bool	side_int(t_cylinder_math *c, t_ray ray, t_hit *hit, t_quad *cy_eq)
{
	t_vec3	delta_rej;
	t_vec3	dir_rej;

	delta_rej = vec3_reject(vec3_sub(ray.origin, c->disk_down.point), c->axis);
	dir_rej = vec3_reject(ray.direction, c->axis);
	cy_eq->a = vec3_length_sq(dir_rej);
	cy_eq->b = 2.0f * (vec3_dot(delta_rej, dir_rej));
	cy_eq->c = vec3_length_sq(delta_rej) - c->radius_sq;
	cy_eq->x1 = NAN;
	if (!solve_quadratic(cy_eq))
		return (false);
	if (cy_eq->x0 < ray.t_min || cy_eq->x0 > ray.t_max)
	{
		if (cy_eq->x1 < ray.t_min || cy_eq->x1 > ray.t_max)
			return (false);
		cy_eq->x0 = cy_eq->x1;
	}
	hit->t = cy_eq->x0;
	hit->point = ray_at(ray, hit->t);
	hit->normal = vec3_add(delta_rej, vec3_scale(dir_rej, hit->t));
	hit->normal = vec3_scale(hit->normal, 1.0f / c->radius);
	hit->color = c->color;
	hit->ray = ray;
	hit->obj = OBJ_CYLINDER;
	return (true);
}
