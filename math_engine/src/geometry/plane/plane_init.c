/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:42:59 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 22:02:06 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/plane.h"

int		plane_init(t_plane_math *pl, t_plane_data data)
{
	if (!pl)
		return (1);
	pl->color = data.color;
	pl->normal = data.normal;
	pl->point = data.point;
	pl->dot = -vec3_dot(data.point, data.normal);
	return (0);
}