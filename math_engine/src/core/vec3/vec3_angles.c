/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_angles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:08:33 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/23 17:43:32 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"
#include <math.h>

inline float	vec3_angle(t_vec3 a, t_vec3 b)
{
	float	den;
	float	num;

	den = 1.0f / sqrtf(vec3_length_sq(a) * vec3_length_sq(b));
	num = vec3_dot(a, b);
	return (acosf(num * den));
}

// uses formula tan(theta) = sin(theta) / cos(theta)
// (--> scaled both by len(a) * len(b), cancel out)
// (axis . (a x b)) ---> sin(theta), between projected a and projected b 
// over axis, scaled by len(a) * len(b)
// a . b ---> cos(theta), scaled by len(a) * len(b)
// axis must be normalized 
// -->(one vector of coordinate system or constants _X, _Y, _Z)
inline float	vec3_signed_angle(t_vec3 a, t_vec3 b, t_vec3 axis)
{
	float	len;
	float	dot;

	len = vec3_volume(axis, a, b);
	dot = vec3_dot(a, b);
	return (atan2f(len, dot));
}
