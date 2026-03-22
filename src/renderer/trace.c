/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:21:27 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/23 00:44:15 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

void	loop_sp(const t_ray ray, const t_math *math, t_hit *near, int *idx);
void	loop_pl(const t_ray ray, const t_math *math, t_hit *near, int *idx);
void	loop_cy(const t_ray ray, const t_math *math, t_hit *near, int *idx);

// function that calls for each object type its own intersect function
// returns true if the intersection is found
// idx then holds the index of the array member of t_math
// the specific array is identified by near->obj enum entry
// there's a triple loop leading to future multithreading optimizations,
// where each thread could loop on each geometry type safely

bool	trace(const t_ray ray, const t_math *math, t_hit *near, int *idx)
{
	near->obj = OBJ_NULL;
	near->t = INFINITY;
	loop_sp(ray, math, near, idx);
	loop_pl(ray, math, near, idx);
	loop_cy(ray, math, near, idx);
	return (near->obj != OBJ_NULL);
}

// loops over spheres
void	loop_sp(const t_ray ray, const t_math *math, t_hit *near, int *idx)
{
	int		i;
	t_hit	hit;

	i = 0;
	while (i < math->sp_count)
	{
		hit.t = INFINITY;
		if (sphere_intersect(&math->spheres[i++], ray, &hit) && hit.t < near->t)
		{
			*near = hit;
			*idx = i;
		}
	}
}

// loops over planes
void	loop_pl(const t_ray ray, const t_math *math, t_hit *near, int *idx)
{
	int		i;
	t_hit	hit;

	i = 0;
	while (i < math->pl_count)
	{
		hit.t = INFINITY;
		if (plane_intersect(&math->planes[i++], ray, &hit) && hit.t < near->t)
		{
			*near = hit;
			*idx = i;
		}
	}
}

// loops over cylinders
void	loop_cy(const t_ray ray, const t_math *math, t_hit *near, int *idx)
{
	int		i;
	t_hit	hit;

	i = 0;
	while (i < math->cy_count)
	{
		hit.t = INFINITY;
		if (cylinder_intersect(&math->cys[i++], ray, &hit) && hit.t < near->t)
		{
			*near = hit;
			*idx = i;
		}
	}
}
