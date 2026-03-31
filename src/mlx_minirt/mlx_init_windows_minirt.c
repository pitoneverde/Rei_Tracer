/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_windows_minirt.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:16:23 by gmu               #+#    #+#             */
/*   Updated: 2026/03/31 23:53:15 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include <math.h>
#include "minirt.h"
#include "minirt_renderer.h"
#ifndef XK_ESCAPE
# define XK_ESCAPE 0xff1b
#endif

// funzione per liberare tutto
int	free_all_minirt(t_mlx_minirt *mlx)
{
	free(mlx->data_file);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	destroy_math(mlx->math);
	free(mlx->mlx);
	exit(0);
}

// funzione per catturare i tasti della tastiera
int	key_hook_minirt(int keycode, t_mlx_minirt *mlx)
{
	if (keycode == XK_ESCAPE)
		free_all_minirt(mlx);
	return (0);
}

// uncomment for benchmarking rendering
// #include <time.h>
// #define N_RUNS 5

// double time_diff_sec(struct timespec start, struct timespec end)
// {
// 	return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
// }

// minilibx e altre cose
// cose assolutamente obbligatorie per mlx
void	mlx_init_windows_minirt(t_element *data_file)
{
	t_mlx_minirt	mlx;

	mlx.math = init_math(data_file);
	if (!mlx.math)
	{
		printf("Malloc error: failed to initialize math engine");
		free(data_file);
		return ;
	}
	mlx.data_file = data_file;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, IMG_WIDTH, IMG_HEIGHT, "MiniRT window");
	mlx.img = mlx_new_image(mlx.mlx, IMG_WIDTH, IMG_HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_len, &mlx.endian);
	printf("RENDERING\n");
	render_minirt(&mlx, mlx.math);
	printf("RENDERED\n");
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_hook(mlx.win, 17, 1 << 17, free_all_minirt, &mlx);
	mlx_key_hook(mlx.win, key_hook_minirt, &mlx);
	mlx_loop(mlx.mlx);
}

// ===== BENCH RENDERING =====
// double total_time = 0.0;
// for (int run = 0; run < N_RUNS; run++) {
// 	struct timespec t1, t2;
// 	clock_gettime(CLOCK_MONOTONIC, &t1);
// 	render_minirt(&mlx, mlx.math);
// 	clock_gettime(CLOCK_MONOTONIC, &t2);
// 	total_time += time_diff_sec(t1, t2) * 1000;
// }
// printf("Average over %d runs: %.2f ms\n", N_RUNS, total_time / N_RUNS);
