/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:15:52 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/19 18:41:08 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt_renderer.h"
#include "geometry/plane.h"

static t_plane_data	convert_plane(const t_plane *pl)
{
	t_plane_data	pl_data;

	pl_data.color = vec3_from_color_hex(pl->color.hex);
	pl_data.normal = pl->normal;
	pl_data.point = pl->point;
	return (pl_data);
}

int create_plane(t_plane_math *math, t_plane *plane)
{
	if (!math)
		return (1);
	t_plane_data plane_data = convert_plane(plane);
	if (plane_init(math, plane_data))
		return (1);
	return (0);
}
