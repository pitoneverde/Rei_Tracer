/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:22:26 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/22 23:30:10 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

// contains the functions to intersect with sphere, plane, cylinder
// contains also t_hit and normal calcs to enable shading

# include <stdbool.h>
# include "core/vec3.h"
# include "geometry/ray.h"

typedef enum s_obj_type
{
	OBJ_NULL = 0,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct s_hit
{
	float		t;
	t_ray		ray;
	t_vec3		point;
	t_vec3		normal;
	t_vec3		color;
	t_obj_type	obj;
}	t_hit;

// quadratic equation: ax² + bx + c = 0
typedef struct s_quad
{
	float	a;
	float	b;
	float	c;
	float	x0;
	float	x1;
}	t_quad;

bool	solve_quadratic(t_quad *eq);

#endif