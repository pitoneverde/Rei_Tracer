#include <math.h>
#include "minirt.h"
#include "minirt_renderer.h"

#ifndef XK_Escape
#define XK_Escape 0xff1b
#endif

void	print_t_element(t_element *elem);
void print_t_element_array_sentinel(t_element *arr);
void print_camera_data(const t_camera_data *cam);
void print_cam(const t_camera_math *cam);

// funzione per liberare tutto
int	free_all_minirt(t_mlx_minirt *mlx)
{
	free(mlx->data_file);
	mlx_destroy_image(mlx->voidptr_mlx, mlx->voidptr_img);
	mlx_destroy_window(mlx->voidptr_mlx, mlx->voidptr_win);
	mlx_destroy_display(mlx->voidptr_mlx);
	free(mlx->voidptr_mlx);
	exit(0);
}

// funzione per catturare i tasti della tastiera
int	key_hook_minirt(int keycode, t_mlx_minirt *mlx)
{
	if (keycode == XK_Escape)
		free_all_minirt(mlx);
	return (0);
}

// minilibx e altre cose
void    mlx_init_windows_minirt(t_element *data_file)
{
	t_mlx_minirt	mlx;
	mlx.data_file = data_file;
	// cose assolutamente obbligatorie per mlx
	mlx.voidptr_mlx = mlx_init();
	mlx.voidptr_win = mlx_new_window(mlx.voidptr_mlx, IMG_WIDTH, IMG_HEIGHT, "MiniRT window");
	mlx.voidptr_img = mlx_new_image(mlx.voidptr_mlx, IMG_WIDTH, IMG_HEIGHT);
	mlx.charptr_addr = mlx_get_data_addr(mlx.voidptr_img, &mlx.int_bits_per_pixel, &mlx.int_line_length, &mlx.int_endian);


	print_t_element_array_sentinel(data_file); // da togliere, solo per debug
	(void)data_file;
	// render ray tracing
	render_minirt(&mlx);

	mlx_put_image_to_window(mlx.voidptr_mlx, mlx.voidptr_win, mlx.voidptr_img, 0, 0);
	printf("RENDERED");
	fflush(stdout);
	mlx_hook(mlx.voidptr_win, 17, 1 << 17, free_all_minirt, &mlx);
	mlx_key_hook(mlx.voidptr_win, key_hook_minirt, &mlx);
	mlx_loop(mlx.voidptr_mlx);
	(void)mlx;
}
