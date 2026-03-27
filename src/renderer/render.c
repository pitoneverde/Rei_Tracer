/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:58:38 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/23 00:51:39 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	printf("  color     = (%f, %f, %f)\n", math->light.color.x, math->light.color.y, math->light.color.z);
	printf("  intensity = (%f)\n", math->light.intensity);
	printf("  point     = (%f, %f, %f)\n", math->light.point.x, math->light.point.y, math->light.point.z);

	// Sfere
	printf("[SPHERES] count = %d\n", math->sp_count);
	for (int i = 0; i < math->sp_count; i++)
	{
		const t_sphere_math *s = &math->spheres[i];
		printf("  sphere %d:\n", i);
		printf("    center   = (%f, %f, %f)\n", s->center.x, s->center.y, s->center.z);
		printf("    radius   = %f\n", s->radius);
		printf("    color    = (%f, %f, %f)\n", s->color.x, s->color.y, s->color.z);
		printf("    radius_sq= %f\n", s->radius_sq);
	}

	// Piani
	printf("[PLANES] count = %d\n", math->pl_count);
	for (int i = 0; i < math->pl_count; i++)
	{
		const t_plane_math *p = &math->planes[i];
		printf("  plane %d:\n", i);
		printf("    normal = (%f, %f, %f)\n", p->normal.x, p->normal.y, p->normal.z);
		printf("    point  = (%f, %f, %f)\n", p->point.x, p->point.y, p->point.z);
		printf("    color  = (%f, %f, %f)\n", p->color.x, p->color.y, p->color.z);
		printf("    dot    = %f\n", p->dot);
	}

	// Cilindri (cys)
	printf("[CYLINDERS] count = %d\n", math->cy_count);
	for (int i = 0; i < math->cy_count; i++)
	{
		const t_cylinder_math *c = &math->cys[i];
		printf("  cylinder %d:\n", i);
		printf("    axis        = (%f, %f, %f)\n", c->axis.x, c->axis.y, c->axis.z);
		printf("    center      = (%f, %f, %f)\n", c->center.x, c->center.y, c->center.z);
		printf("    color       = (%f, %f, %f)\n", c->color.x, c->color.y, c->color.z);
		printf("    radius      = %f\n", c->radius);
		printf("    radius_sq   = %f\n", c->radius_sq);
		printf("    height      = %f\n", c->height);
		printf("    half_height = %f\n", c->half_height);
		printf("    disk_up:\n");
		printf("      normal = (%f, %f, %f)\n", c->disk_up.normal.x, c->disk_up.normal.y, c->disk_up.normal.z);
		printf("      point  = (%f, %f, %f)\n", c->disk_up.point.x, c->disk_up.point.y, c->disk_up.point.z);
		printf("      color  = (%f, %f, %f)\n", c->disk_up.color.x, c->disk_up.color.y, c->disk_up.color.z);
		printf("      dot    = %f\n", c->disk_up.dot);
		printf("    disk_down:\n");
		printf("      normal = (%f, %f, %f)\n", c->disk_down.normal.x, c->disk_down.normal.y, c->disk_down.normal.z);
		printf("      point  = (%f, %f, %f)\n", c->disk_down.point.x, c->disk_down.point.y, c->disk_down.point.z);
		printf("      color  = (%f, %f, %f)\n", c->disk_down.color.x, c->disk_down.color.y, c->disk_down.color.z);
		printf("      dot    = %f\n", c->disk_down.dot);
	}

	printf("=== end dump ===\n");
}

static void	put_pixel(t_mlx_minirt *mlx, int x, int y, t_rgb color);

#include <math.h>

// Le tue strutture: t_vec3, t_rgb, t_ray, t_object (con puntatore a funzione intersect)
// e la definizione di t_math come nel dump.

void render_minirt(t_mlx_minirt *mlx, t_math *math) {
    int     x, y, i;
    double  pixel_size_x, pixel_size_y;
    double  world_x, world_y;
    t_vec3  camera_pos, dir, point_on_plane;
    t_ray   ray;
    t_rgb   col;
    double  t_hit, t_min;
    t_object *hit_obj;

    // Dimensioni immagine (probabilmente definite in macro o nella struttura)
    const int width  = IMG_WIDTH;   // 1368
    const int height = IMG_HEIGHT;  // 786

    // Calcolo pixel size in coordinate mondo
    pixel_size_x = (math->canvas[1] - math->canvas[0]) / width;
    pixel_size_y = (math->canvas[3] - math->canvas[2]) / height;

    // Posizione della camera (traslazione di cam_to_world, se identità => (0,0,0))
    camera_pos.x = math->cam_to_world[0][3];
    camera_pos.y = math->cam_to_world[1][3];
    camera_pos.z = math->cam_to_world[2][3];

    for (y = 0; y < height; y++) {
        // Coordinata Y mondo (top -> bottom)
        world_y = math->canvas[3] - pixel_size_y * y;

        for (x = 0; x < width; x++) {
            // Coordinata X mondo (left -> right)
            world_x = math->canvas[0] + pixel_size_x * x;

            // Punto sul piano di proiezione (assumendo z = near_clip)
            point_on_plane = (t_vec3){world_x, world_y, math->near_clip};

            // Direzione del raggio (normalizzata)
            dir = normalize(sub(point_on_plane, camera_pos));
            ray = (t_ray){camera_pos, dir};

            // Colore di sfondo (nero)
            col = (t_rgb){0, 0, 0};
            t_min = INFINITY;
            hit_obj = NULL;

            // Verifica intersezioni con tutti gli oggetti
            // 1) Sfere
            for (i = 0; i < math->sphere_count; i++) {
                if (sphere_intersect(&math->spheres[i], ray, &t_hit) && t_hit > 1e-6) {
                    if (t_hit < t_min) {
                        t_min = t_hit;
                        hit_obj = (t_object*)&math->spheres[i];
                    }
                }
            }
            // 2) Piani
            for (i = 0; i < math->plane_count; i++) {
                if (plane_intersect(&math->planes[i], ray, &t_hit) && t_hit > 1e-6) {
                    if (t_hit < t_min) {
                        t_min = t_hit;
                        hit_obj = (t_object*)&math->planes[i];
                    }
                }
            }
            // 3) Cilindri
            for (i = 0; i < math->cylinder_count; i++) {
                if (cylinder_intersect(&math->cylinders[i], ray, &t_hit) && t_hit > 1e-6) {
                    if (t_hit < t_min) {
                        t_min = t_hit;
                        hit_obj = (t_object*)&math->cylinders[i];
                    }
                }
            }

            // Se c'è un hit, assegna il colore dell'oggetto (in seguito aggiungerai illuminazione)
            if (hit_obj) {
                col = hit_obj->color;
            }

            put_pixel(mlx, x, y, col);
        }
    }
}

static void	put_pixel(t_mlx_minirt *mlx, int x, int y, t_rgb color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(uint32_t *)dst = color.hex;
}
