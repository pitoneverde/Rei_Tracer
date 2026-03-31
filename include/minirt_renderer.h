/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_renderer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 23:59:08 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 23:39:56 by gmu              ###   ########.fr       */
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

typedef struct s_material
{
	float	specular;
	float	shininess;
}	t_material;

void	render_minirt(t_mlx_minirt *mlx, t_math *math);
t_rgb	ray_cast(const t_ray ray, t_math *math);
bool	trace(const t_ray ray, const t_math *math, t_hit *near, int *idx);
t_vec3	lighting(t_material material, t_math *math, t_hit hit);

t_math	*init_math(t_element *d);

// Internal init utils because of norminette
t_math	*init_spheres(t_math *m, t_element *d, int *i);
t_math	*init_planes(t_math *m, t_element *d, int *i);
t_math	*init_cylinders(t_math *m, t_element *d, int *i);

void	destroy_math(t_math *math_engine);

int		create_ambient(t_ambient_math *math, t_ambient *a);
int		create_camera(t_camera_math *math, t_camera *cam);
int		create_sphere(t_sphere_math *math, t_sphere *sphere);
int		create_plane(t_plane_math *math, t_plane *plane);
int		create_cylinder(t_cylinder_math *math, t_cylinder *cylinder);
int		create_light(t_light_math *math, t_light *light);

t_rgb	vec3_to_rgb(t_vec3 color);
t_vec3	reflect(t_vec3 v, t_vec3 n);

void	print_t_element(t_element *elem);

#endif
