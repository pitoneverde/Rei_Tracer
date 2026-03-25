/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_renderer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:59:08 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/25 23:51:51 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_RENDERER_H
# define MINIRT_RENDERER_H

# include "minirt_data.h"
# include "mlx_minirt.h"
# include "math_engine.h"

# define IMG_WIDTH 1368
# define IMG_HEIGHT 786

// #define IMG_WIDTH 400
// #define IMG_HEIGHT 300

void	render_minirt(t_mlx_minirt *mlx, t_math *math);
t_rgb	ray_cast(const t_ray ray, t_math *math);
bool	trace(const t_ray ray, const t_math *math, t_hit *near, int *idx);

t_math	*init_math(t_element *d);
void	destroy_math(t_math *math_engine);

int		create_camera(t_camera_math *math, t_camera *cam);
int		create_sphere(t_sphere_math *math, t_sphere *sphere);
int		create_plane(t_plane_math *math, t_plane *plane);
int		create_cylinder(t_cylinder_math *math, t_cylinder *cylinder);
int		create_light(t_light_math *math, t_light *light);

// int	create_ambient(t_ambient_math *math, t_ambient_data *al);

void	print_t_element(t_element *elem);

#endif