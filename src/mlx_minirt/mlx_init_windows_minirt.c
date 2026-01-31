#include "minirt.h"

#ifndef XK_Escape
#define XK_Escape 0xff1b
#endif

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


// minilibx e altre cose
void    mlx_init_windows_minirt(t_element *data_file)
{
	t_mlx_minirt	mlx;
	mlx.data_file = data_file;
	// cose assolutamente obbligatorie per mlx
	int width = 1366;
	int height = 768;
	mlx.voidptr_mlx = mlx_init();
	mlx.voidptr_win = mlx_new_window(mlx.voidptr_mlx, width, height, "MiniRT window");
	mlx.voidptr_img = mlx_new_image(mlx.voidptr_mlx, width, height);
	mlx.charptr_addr = mlx_get_data_addr(mlx.voidptr_img, &mlx.int_bits_per_pixel, &mlx.int_line_length, &mlx.int_endian);


	//render ray tracing
	//render_rt(&mlx);

	mlx_put_image_to_window(mlx.voidptr_mlx, mlx.voidptr_win, mlx.voidptr_img, 0, 0);
	mlx_hook(mlx.voidptr_win, 17, 1 << 17, free_all_minirt, &mlx);
	mlx_key_hook(mlx.voidptr_win, key_hook_minirt, &mlx);
	mlx_loop(mlx.voidptr_mlx);
}
