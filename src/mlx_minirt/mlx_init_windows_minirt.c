#include "minirt.h"
#include "minirt_renderer.h"

#ifndef XK_Escape
#define XK_Escape 0xff1b
#endif

void	print_t_element(t_element *elem);
void print_t_element_array_sentinel(t_element *arr);
void print_camera_data(const t_camera_data *cam);
void print_cam(const t_camera_math *cam);

typedef struct s_mlx_minirt
{
	void			*voidptr_mlx;
	void			*voidptr_win;
	void			*voidptr_img;
	char			*charptr_addr;
	int				int_bits_per_pixel;
	int				int_line_length;
	int				int_endian;
	t_element		*data_file;
}					t_mlx_minirt;

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

void	put_pixel(t_mlx_minirt *mlx, int x, int y, t_rgb color)
{
	char	*dst;

	dst = mlx->charptr_addr + (y * mlx->int_line_length + x * (mlx->int_bits_per_pixel / 8));
	*(uint32_t *)dst = color.hex;
}
#include <math.h>

void	render_minirt(t_mlx_minirt *mlx)
{
	// t_camera camera = {
	// 	.fov = 90,
	// 	.viewpoint = {.x = -50.0f, .y = 0.0f, .z = 20.0f},
	// 	.orientation = {.x = 1.0f, .y = 0.0f, .z = 0.0f}
	// };
	// t_camera_math *cam = create_camera_math(&camera);
	t_math *math = init_math(mlx->data_file);
	t_ray	ray;
	// // print_cam(cam);
	for (int y = 0; y < IMG_HEIGHT; ++y)
	{
		for (int x = 0; x < IMG_WIDTH; ++x)
		{
			ray = camera_raygen(&math->camera, (t_pixel){.x = x, .y = y});
			// t_rgb col;
			t_rgb col = ray_cast(ray, math);
			// printf("color: %x", col.hex);
			// col.hex = 0xFF0000; // Red color for testing
			put_pixel(mlx, x, y, col);
		}
		// printf("Rendering scanline: %d\n", y);
		fflush(stdout);
		// mlx_put_image_to_window(mlx->voidptr_mlx, mlx->voidptr_win, mlx->voidptr_img, 0, 0);
	}
	destroy_math(math);
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
