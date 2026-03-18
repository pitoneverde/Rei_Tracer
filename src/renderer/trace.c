/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:21:27 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 12:44:19 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

// function that calls for each object type its own intersect function
// returns true if the intersection is found
// idx then holds the index of the array member of t_math
// the specific array is identified by near->obj enum entry
// there's a triple loop leading to future multithreading optimizations,
// where each thread could loop on each geometry type safely
bool	trace(const t_ray ray, const t_math *math, t_hit *near, int *idx)
{
	int		i;
	t_hit	hit;

	hit.obj = OBJ_NULL;
	hit.t = INFINITY;
	i = 0;
	while (i < math->sp_count)
	{
		near->t = INFINITY;
		if (sphere_intersect(&math->spheres[i++], ray, &hit) && hit.t < near->t)
		{
			printf("t: %7.3f", hit.t);
			near->t = hit.t;
			near->color = hit.color;
			near->normal = hit.normal;
			near->obj = hit.obj;
			near->point = hit.point;
			near->ray = hit.ray;
			*idx = i;
			printf("t: %7.3f", near->t);
			fflush(stdout);
		}
	}
	return (near->obj != OBJ_NULL);
}