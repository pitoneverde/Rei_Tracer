#ifndef MLX_MINIRT_H
# define MLX_MINIRT_H 1

#include "mlx.h"

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

void    mlx_init_windows_minirt(t_element *data_file);

#endif
