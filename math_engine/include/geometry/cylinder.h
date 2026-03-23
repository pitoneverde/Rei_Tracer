/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:25:17 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/23 00:57:59 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "core/vec3.h"
# include "geometry/intersection.h"
# include "geometry/plane.h"

typedef struct s_cylinder_math
{
	t_vec3			axis;
	t_vec3			center;
	t_vec3			color;
	float			radius;
	float			radius_sq;
	float			height;
	float			half_height;
	t_plane_math	disk_up;
	t_plane_math	disk_down;
}	t_cylinder_math;

typedef struct s_cylinder_data
{
	t_vec3			axis;
	t_vec3			center;
	t_vec3			color;
	float			height;
	float			half_height;
	float			radius;
	float			radius_sq;
	t_plane_data	disk_up;
	t_plane_data	disk_down;
}	t_cylinder_data;

int		cylinder_init(t_cylinder_math *cy, t_cylinder_data data);
bool	cylinder_intersect(t_cylinder_math *c, t_ray ray, t_hit *hit);

#endif