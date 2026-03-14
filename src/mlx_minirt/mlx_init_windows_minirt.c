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

void	put_pixel(t_mlx_minirt *mlx, int x, int y, t_rgb color)
{
	char	*dst;

	dst = mlx->charptr_addr + (y * mlx->int_line_length + x * (mlx->int_bits_per_pixel / 8));
	*(uint32_t *)dst = color.hex;
}

void	render_minirt(t_mlx_minirt *mlx)
{
	int width = 1366;
	int height = 768;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			t_rgb col;
			col.hex = 0xFF0000; // Red color for testing
			put_pixel(mlx, x, y, col);
		}
	}
}

#include <string.h>
#include <stdio.h>
void	print_t_element(t_element *elem)
{
	if (!elem || !elem->id)
	{
		printf("NULL element\n");
		return ;
	}
	printf("Element id: %s\n", elem->id);
	if (strcmp(elem->id, "A") == 0)
	{
		printf("  Ambient Lighting:\n");
		printf("    brightness: %.2f\n", elem->value.a.brightness);
		printf("    color: R=%u G=%u B=%u\n",
			elem->value.a.color.rgba.red,
			elem->value.a.color.rgba.green,
			elem->value.a.color.rgba.blue);
	}
	else if (strcmp(elem->id, "C") == 0)
	{
		printf("  Camera:\n");
		printf("    viewpoint: (%.2f, %.2f, %.2f)\n",
			elem->value.c.viewpoint.x,
			elem->value.c.viewpoint.y,
			elem->value.c.viewpoint.z);
		printf("    orientation: (%.2f, %.2f, %.2f)\n",
			elem->value.c.orientation.x,
			elem->value.c.orientation.y,
			elem->value.c.orientation.z);
		printf("    FOV: %.2f\n", elem->value.c.fov);
	}
	else if (strcmp(elem->id, "L") == 0)
	{
		printf("  Light:\n");
		printf("    position: (%.2f, %.2f, %.2f)\n",
			elem->value.l.position.x,
			elem->value.l.position.y,
			elem->value.l.position.z);
		printf("    brightness: %.2f\n", elem->value.l.brightness);
		printf("    color: R=%u G=%u B=%u\n",
			elem->value.l.color.rgba.red,
			elem->value.l.color.rgba.green,
			elem->value.l.color.rgba.blue);
	}
	else if (strcmp(elem->id, "sp") == 0)
	{
		printf("  Sphere:\n");
		printf("    center: (%.2f, %.2f, %.2f)\n",
			elem->value.sp.center.x,
			elem->value.sp.center.y,
			elem->value.sp.center.z);
		printf("    diameter: %.2f\n", elem->value.sp.diameter);
		printf("    color: R=%u G=%u B=%u\n",
			elem->value.sp.color.rgba.red,
			elem->value.sp.color.rgba.green,
			elem->value.sp.color.rgba.blue);
	}
	else if (strcmp(elem->id, "pl") == 0)
	{
		printf("  Plane:\n");
		printf("    point: (%.2f, %.2f, %.2f)\n",
			elem->value.pl.point.x,
			elem->value.pl.point.y,
			elem->value.pl.point.z);
		printf("    normal: (%.2f, %.2f, %.2f)\n",
			elem->value.pl.normal.x,
			elem->value.pl.normal.y,
			elem->value.pl.normal.z);
		printf("    color: R=%u G=%u B=%u\n",
			elem->value.pl.color.rgba.red,
			elem->value.pl.color.rgba.green,
			elem->value.pl.color.rgba.blue);
	}
	else if (strcmp(elem->id, "cy") == 0)
	{
		printf("  Cylinder:\n");
		printf("    center: (%.2f, %.2f, %.2f)\n",
			elem->value.cy.center.x,
			elem->value.cy.center.y,
			elem->value.cy.center.z);
		printf("    axis: (%.2f, %.2f, %.2f)\n",
			elem->value.cy.axis.x,
			elem->value.cy.axis.y,
			elem->value.cy.axis.z);
		printf("    diameter: %.2f\n", elem->value.cy.diameter);
		printf("    height: %.2f\n", elem->value.cy.height);
		printf("    color: R=%u G=%u B=%u\n",
			elem->value.cy.color.rgba.red,
			elem->value.cy.color.rgba.green,
			elem->value.cy.color.rgba.blue);
	}
	else
	{
		printf("  Unknown element type\n");
	}
}

void print_t_element_array_sentinel(t_element *arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr->id)
    {
        printf("\n=== Element %d ===\n", i++);
        print_t_element(arr);
        arr++;
    }
}
// minilibx e altre cose
void    mlx_init_windows_minirt(t_element *data_file)
{
	t_mlx_minirt	mlx;
	mlx.data_file = data_file;
	// cose assolutamente obbligatorie per mlx
	// int width = 1366;
	// int height = 768;
	// mlx.voidptr_mlx = mlx_init();
	// mlx.voidptr_win = mlx_new_window(mlx.voidptr_mlx, width, height, "MiniRT window");
	// mlx.voidptr_img = mlx_new_image(mlx.voidptr_mlx, width, height);
	// mlx.charptr_addr = mlx_get_data_addr(mlx.voidptr_img, &mlx.int_bits_per_pixel, &mlx.int_line_length, &mlx.int_endian);


	print_t_element_array_sentinel(data_file); // da togliere, solo per debug
	//render ray tracing
	// render_minirt(&mlx);

	// mlx_put_image_to_window(mlx.voidptr_mlx, mlx.voidptr_win, mlx.voidptr_img, 0, 0);
	// mlx_hook(mlx.voidptr_win, 17, 1 << 17, free_all_minirt, &mlx);
	// mlx_key_hook(mlx.voidptr_win, key_hook_minirt, &mlx);
	// mlx_loop(mlx.voidptr_mlx);
	(void)mlx;
}
