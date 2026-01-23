/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:44:11 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/23 18:01:39 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"

// epsilon should be MATH_EPSILON for standard precision, or 0.0f
inline bool	vec3_is_parallel(t_vec3 a, t_vec3 b, float epsilon)
{
	return (vec3_is_zero(vec3_cross(a, b), epsilon));
}

// epsilon should be MATH_EPSILON for standard precision, or 0.0f
inline bool	vec3_is_perpendicular(t_vec3 a, t_vec3 b, float epsilon)
{
	return (vec3_dot(a, b) < epsilon);
}
