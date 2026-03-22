/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 23:56:14 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/23 00:04:48 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

static t_cylinder_data	convert_cylinder(t_cylinder *cylinder)
{
	t_cylinder_data	cy_data;
	float			hh;

	cy_data.axis = cylinder->axis;
	cy_data.center = cylinder->center;
	cy_data.color = vec3_from_color_hex(cylinder->color.hex);
	cy_data.height = cylinder->height;
	cy_data.radius = cylinder->diameter * 0.5f;
	cy_data.half_height = cy_data.height * 0.5f;
	cy_data.radius_sq = cy_data.radius * cy_data.radius;
	hh = cy_data.half_height;
	cy_data.disk_up = (t_plane_data){
		.color = cy_data.color,
		.normal = cy_data.axis,
		.point = vec3_add(cy_data.center, vec3_scale(cy_data.axis, hh)),
	};
	cy_data.disk_down = (t_plane_data){
		.color = cy_data.color,
		.normal = vec3_neg(cy_data.axis),
		.point = vec3_sub(cy_data.center, vec3_scale(cy_data.axis, hh)),
	};
	return (cy_data);
}

int	create_cylinder(t_cylinder_math *math, t_cylinder *cylinder)
{
	t_cylinder_data	cylinder_data;

	if (!math)
		return (1);
	cylinder_data = convert_cylinder(cylinder);
	if (cylinder_init(math, cylinder_data))
		return (1);
	return (0);
}
