/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:57:18 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/23 00:57:19 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "core/vec3.h"
# include "geometry/intersection.h"

typedef struct s_sphere_math
{
	t_vec3	center;
	float	radius;
	t_vec3	color;
	float	radius_sq;
}	t_sphere_math;

typedef struct s_sphere_data
{
	t_vec3	center;
	float	radius;
	t_vec3	color;
}	t_sphere_data;

int		sphere_init(t_sphere_math *sp, t_sphere_data data);
bool	sphere_intersect(t_sphere_math *s, t_ray ray, t_hit *hit);

#endif