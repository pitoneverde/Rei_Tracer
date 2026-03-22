/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:15:52 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/23 00:04:27 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

static t_plane_data	convert_plane(const t_plane *pl)
{
	t_plane_data	pl_data;

	pl_data.color = vec3_from_color_hex(pl->color.hex);
	pl_data.normal = pl->normal;
	pl_data.point = pl->point;
	return (pl_data);
}

int	create_plane(t_plane_math *math, t_plane *plane)
{
	t_plane_data	plane_data;

	if (!math)
		return (1);
	plane_data = convert_plane(plane);
	if (plane_init(math, plane_data))
		return (1);
	return (0);
}
