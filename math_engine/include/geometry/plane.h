/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:25:22 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/23 00:57:14 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "core/vec3.h"
# include "geometry/intersection.h"

typedef struct s_plane_math
{
	t_vec3	normal;
	t_vec3	point;
	t_vec3	color;
	float	dot;
}	t_plane_math;

typedef struct s_plane_data
{
	t_vec3	normal;
	t_vec3	point;
	t_vec3	color;
}	t_plane_data;

int		plane_init(t_plane_math *pl, t_plane_data data);
bool	plane_intersect(t_plane_math *p, t_ray ray, t_hit *hit);

#endif