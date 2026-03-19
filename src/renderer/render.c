/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:58:38 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/19 22:51:49 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

static void	put_pixel(t_mlx_minirt *mlx, int x, int y, t_rgb color);

void	render_minirt(t_mlx_minirt *mlx, t_math *math)
{
	// printf("STARTED RENDERING\n");
	// fflush(stdout);
	t_ray	ray;
	for (int y = 0; y < IMG_HEIGHT; ++y)
	{
		// printf("Rendering scanline: %d\n", y);
		// fflush(stdout);
		for (int x = 0; x < IMG_WIDTH; ++x)
		{
			ray = camera_raygen(&math->camera, (t_pixel){.x = x, .y = y});
			t_rgb col = ray_cast(ray, math);
			put_pixel(mlx, x, y, col);
		}
		// mlx_put_image_to_window(mlx->voidptr_mlx, mlx->voidptr_win, mlx->voidptr_img, 0, 0);
	}
}

static void	put_pixel(t_mlx_minirt *mlx, int x, int y, t_rgb color)
{
	char	*dst;

	dst = mlx->charptr_addr + (y * mlx->int_line_length + x * (mlx->int_bits_per_pixel / 8));
	*(uint32_t *)dst = color.hex;
}
