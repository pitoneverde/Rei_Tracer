/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 22:24:24 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 22:45:01 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
// Just in case you'll need it
// Btw there's already vec3_print() 
// and mat4_print() to debug prints vectors and matrices

#include "minirt_renderer.h"
#include <stdio.h>

void	print_math(const t_math *math)
{
	if (!math)
	{
		printf("t_math is NULL\n");
		return;
	}

	printf("\n=== t_math dump ===\n");

	// Camera
	printf("[CAMERA]\n");
	printf("  cam_to_world:\n");
	for (int i = 0; i < 4; i++)
	{
		printf("    ");
		for (int j = 0; j < 4; j++)
			printf("%8.3f ", math->camera.cam_to_world.mat[i][j]);
		printf("\n");
	}
	printf("  near_clip = %f\n", math->camera.near_clip);
	printf("  far_clip  = %f\n", math->camera.far_clip);
	printf("  image_h   = %d\n", math->camera.image_h);
	printf("  image_w   = %d\n", math->camera.image_w);
	printf("  hfov      = %f\n", math->camera.hfov);
	printf("  zoom      = %f\n", math->camera.zoom);
	printf("  canvas    = [%f, %f, %f, %f]\n",
		math->camera.canvas[0], math->camera.canvas[1],
		math->camera.canvas[2], math->camera.canvas[3]);
	printf("  image_aspect = %f\n", math->camera.image_aspect);

	// Luce
	printf("[LIGHT]\n");
	printf("  color     = (%f, %f, %f)\n", math->light.color.x,
	 math->light.color.y, math->light.color.z);
	printf("  intensity = (%f)\n", math->light.intensity);
	printf("  point     = (%f, %f, %f)\n", math->light.point.x, 
	math->light.point.y, math->light.point.z);

	// Sfere
	printf("[SPHERES] count = %d\n", math->sp_count);
	for (int i = 0; i < math->sp_count; i++)
	{
		const t_sphere_math *s = &math->spheres[i];
		printf("  sphere %d:\n", i);
		printf("    center   = (%f, %f, %f)\n", s->center.x, 
		s->center.y, s->center.z);
		printf("    radius   = %f\n", s->radius);
		printf("    color    = (%f, %f, %f)\n", s->color.x,
		 s->color.y, s->color.z);
		printf("    radius_sq= %f\n", s->radius_sq);
	}

	// Piani
	printf("[PLANES] count = %d\n", math->pl_count);
	for (int i = 0; i < math->pl_count; i++)
	{
		const t_plane_math *p = &math->planes[i];
		printf("  plane %d:\n", i);
		printf("    normal = (%f, %f, %f)\n", p->normal.x,
		 p->normal.y, p->normal.z);
		printf("    point  = (%f, %f, %f)\n", p->point.x, 
		p->point.y, p->point.z);
		printf("    color  = (%f, %f, %f)\n", p->color.x, 
		p->color.y, p->color.z);
		printf("    dot    = %f\n", p->dot);
	}

	// Cilindri (cys)
	printf("[CYLINDERS] count = %d\n", math->cy_count);
	for (int i = 0; i < math->cy_count; i++)
	{
		const t_cylinder_math *c = &math->cys[i];
		printf("  cylinder %d:\n", i);
		printf("    axis        = (%f, %f, %f)\n", 
		c->axis.x, c->axis.y, c->axis.z);
		printf("    center      = (%f, %f, %f)\n", 
		c->center.x, c->center.y, c->center.z);
		printf("    color       = (%f, %f, %f)\n", 
		c->color.x, c->color.y, c->color.z);
		printf("    radius      = %f\n", c->radius);
		printf("    radius_sq   = %f\n", c->radius_sq);
		printf("    height      = %f\n", c->height);
		printf("    half_height = %f\n", c->half_height);
		printf("    disk_up:\n");
		printf("      normal = (%f, %f, %f)\n", 
		c->disk_up.normal.x, c->disk_up.normal.y, c->disk_up.normal.z);
		printf("      point  = (%f, %f, %f)\n", 
		c->disk_up.point.x, c->disk_up.point.y, c->disk_up.point.z);
		printf("      color  = (%f, %f, %f)\n", 
		c->disk_up.color.x, c->disk_up.color.y, c->disk_up.color.z);
		printf("      dot    = %f\n", c->disk_up.dot);
		printf("    disk_down:\n");
		printf("      normal = (%f, %f, %f)\n", 
		c->disk_down.normal.x, c->disk_down.normal.y, c->disk_down.normal.z);
		printf("      point  = (%f, %f, %f)\n", 
		c->disk_down.point.x, c->disk_down.point.y, c->disk_down.point.z);
		printf("      color  = (%f, %f, %f)\n", 
		c->disk_down.color.x, c->disk_down.color.y, c->disk_down.color.z);
		printf("      dot    = %f\n", c->disk_down.dot);
	}

	printf("=== end dump ===\n");
}

*/