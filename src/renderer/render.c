/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:58:38 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:24 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// static void	put_pixel(t_mlx_minirt *mlx, int x, int y, t_rgb color);

// non necessario per codice duplicato
// #include <math.h>

// Le tue strutture: t_vec3, t_rgb, t_ray,
// t_object (con puntatore a funzione intersect)
// e la definizione di t_math come nel dump.

// void render_minirt(t_mlx_minirt *mlx, t_math *math) {
//     int     x, y, i;
//     double  pixel_size_x, pixel_size_y;
//     double  world_x, world_y;
//     t_vec3  camera_pos, dir, point_on_plane;
//     t_ray   ray;
//     t_rgb   col;
//     double  t_hit, t_min;
//     t_object *hit_obj;

// 	// sono di già nelle macro in minirt_renderer.h
//    
	// Dimensioni immagine (probabilmente definite in macro o nella struttura)
//     const int width  = IMG_WIDTH;   // 1368
//     const int height = IMG_HEIGHT;  // 786

// 	// ci pensa ancora camera_raygen(),
// e la mia convenzione è diversa per questo non funziona
//     // Calcolo pixel size in coordinate mondo
//     pixel_size_x = (math->canvas[1] - math->canvas[0]) / width;
//     pixel_size_y = (math->canvas[3] - math->canvas[2]) / height;

// 	// si chiama camera_eye()
//     // Posizione della camera (traslazione di cam_to_world,
//	se identità => (0,0,0))
//     camera_pos.x = math->cam_to_world[0][3];
//     camera_pos.y = math->cam_to_world[1][3];
//     camera_pos.z = math->cam_to_world[2][3];

//     for (y = 0; y < height; y++) {
//         // Coordinata Y mondo (top -> bottom)
//         world_y = math->canvas[3] - pixel_size_y * y;
//         for (x = 0; x < width; x++) {

// 			// lo fa camera_raygen() di già, pure per la y
//             // Coordinata X mondo (left -> right)
//             world_x = math->canvas[0] + pixel_size_x * x;

//             // Punto sul piano di proiezione (assumendo z = near_clip)
//             point_on_plane = (t_vec3){world_x, world_y, math->near_clip};

//             // Direzione del raggio (normalizzata)
//             dir = normalize(sub(point_on_plane, camera_pos));
//             ray = (t_ray){camera_pos, dir};

// 			// inizio di ray_cast, usa t_vec3
//             // Colore di sfondo (nero)
//             col = (t_rgb){0, 0, 0};
//             t_min = INFINITY;
//             hit_obj = NULL;

// 			// lo fa trace() di già, chiamata da ray_cast
//             // Verifica intersezioni con tutti gli oggetti
//             // 1) Sfere
//             for (i = 0; i < math->sphere_count; i++) {
//                 if (sphere_intersect(&math->spheres[i], ray, &t_hit)
//	&& t_hit > 1e-6) {
//                     if (t_hit < t_min) {
//                         t_min = t_hit;
//                         hit_obj = (t_object*)&math->spheres[i];
//                     }
//                 }
//             }
//             // 2) Piani
//             for (i = 0; i < math->plane_count; i++) {
//                 if (plane_intersect(&math->planes[i], ray, &t_hit)
//	&& t_hit > 1e-6) {
//                     if (t_hit < t_min) {
//                         t_min = t_hit;
//                         hit_obj = (t_object*)&math->planes[i];
//                     }
//                 }
//             }
//             // 3) Cilindri
//             for (i = 0; i < math->cylinder_count; i++) {
//                 if (cylinder_intersect(&math->cylinders[i], ray, &t_hit)
//	&& t_hit > 1e-6) {
//                     if (t_hit < t_min) {
//                         t_min = t_hit;
//                         hit_obj = (t_object*)&math->cylinders[i];
//                     }
//                 }
//             }

// 			// lo fa ray_cast() di già, e ci puoi pure richiamare le shader

//             // Se c'è un hit,
//	assegna il colore dell'oggetto (in seguito aggiungerai illuminazione)
//             if (hit_obj) {
//                 col = hit_obj->color;
//             }

//             put_pixel(mlx, x, y, col);
//         }
//     }
// }

#include "minirt_renderer.h"

static void	put_pixel(t_mlx_minirt *mlx, int x, int y, t_rgb color);

// questa già funzionava, perché modificarla?
// è abbastanza elegante visto che in 18 righe fa tutto il necessario
void	render_minirt(t_mlx_minirt *mlx, t_math *math)
{
	int		y;
	int		x;
	t_ray	ray;
	t_rgb	col;

	y = 0;
	while (y < IMG_HEIGHT)
	{
		x = 0;
		while (x < IMG_WIDTH)
		{
			ray = camera_raygen(&math->camera, (t_pixel){.x = x, .y = y});
			col = ray_cast(ray, math);
			put_pixel(mlx, x, y, col);
			x++;
		}
		y++;
	}
}

static void	put_pixel(t_mlx_minirt *mlx, int x, int y, t_rgb color)
{
	char *dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(uint32_t *)dst = color.hex;
}
