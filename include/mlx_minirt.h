/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_minirt.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:01:04 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/23 00:14:58 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_MINIRT_H
# define MLX_MINIRT_H 1

# include "mlx.h"
# include "math_engine.h"

typedef struct s_mlx_minirt
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_element	*data_file;
	t_math		*math;
}	t_mlx_minirt;

void	mlx_init_windows_minirt(t_element *data_file);
void	print_t_element(t_element *elem);
void	print_t_element_array_sentinel(t_element *arr);
void	print_camera_data(const t_camera_data *cam);
void	print_cam(const t_camera_math *cam);

#endif
