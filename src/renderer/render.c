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

static void	put_pixel(t_mlx_minirt *mlx, int x, int y, t_rgb color);

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
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(uint32_t *)dst = color.hex;
}
