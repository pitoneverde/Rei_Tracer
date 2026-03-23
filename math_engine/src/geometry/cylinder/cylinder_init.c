/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 22:29:51 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/22 23:09:40 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/cylinder.h"

int	cylinder_init(t_cylinder_math *cy, t_cylinder_data data)
{
	if (!cy)
		return (1);
	cy->axis = data.axis;
	cy->center = data.center;
	cy->color = data.color;
	cy->half_height = data.half_height;
	cy->height = data.height;
	cy->radius = data.radius;
	cy->radius_sq = data.radius_sq;
	if (plane_init(&cy->disk_up, data.disk_up))
		return (1);
	if (plane_init(&cy->disk_down, data.disk_down))
		return (1);
	return (0);
}
