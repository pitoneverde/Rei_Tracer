/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:58:38 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/19 18:21:18 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

static void	put_pixel(t_mlx_minirt *mlx, int x, int y, t_rgb color);

void	render_minirt(t_mlx_minirt *mlx)
{
	// t_camera camera = {
	// 	.fov = 90,
	// 	.viewpoint = {.x = -50.0f, .y = 0.0f, .z = 20.0f},
	// 	.orientation = {.x = 1.0f, .y = 0.0f, .z = 0.0f}
	// };
	// t_camera_math *cam = create_camera_math(&camera);
	t_math *math = init_math(mlx->data_file);
	if (!math)
		return;
	printf("STARTED RENDERING");
	fflush(stdout);
	t_ray	ray;
	// // print_cam(cam);
	for (int y = 0; y < IMG_HEIGHT; ++y)
	{
		printf("Rendering scanline: %d\n", y);
		fflush(stdout);
		for (int x = 0; x < IMG_WIDTH; ++x)
		{
			ray = camera_raygen(&math->camera, (t_pixel){.x = x, .y = y});
			// t_rgb col;
			t_rgb col = ray_cast(ray, math);
			// printf("color: %x", col.hex);
			// col.hex = 0xFF0000; // Red color for testing
			put_pixel(mlx, x, y, col);
		}
		// mlx_put_image_to_window(mlx->voidptr_mlx, mlx->voidptr_win, mlx->voidptr_img, 0, 0);
	}
	destroy_math(math);
}

static void	put_pixel(t_mlx_minirt *mlx, int x, int y, t_rgb color)
{
	char	*dst;

	dst = mlx->charptr_addr + (y * mlx->int_line_length + x * (mlx->int_bits_per_pixel / 8));
	*(uint32_t *)dst = color.hex;
}
