/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 23:17:42 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/22 23:28:54 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"
#include "utils/math_constants.h"
#include <math.h>

inline t_vec3	vec3_abs(t_vec3 v)
{
	return ((t_vec3){fabsf(v.x), fabsf(v.y), fabsf(v.z)});
}

inline t_vec3	vec3_floor(t_vec3 v)
{
	return ((t_vec3){floorf(v.x), floorf(v.y), floorf(v.z)});
}

inline t_vec3	vec3_ceil(t_vec3 v)
{
	return ((t_vec3){ceilf(v.x), ceilf(v.y), ceilf(v.z)});
}

inline t_vec3	vec3_round(t_vec3 v)
{
	return ((t_vec3){roundf(v.x), roundf(v.y), roundf(v.z)});
}

inline t_vec3	vec3_mod(t_vec3 v, float divisor)
{
	if (fabsf(divisor) < MATH_EPSILON)
		return (VEC3_ZERO);
	return ((t_vec3){
		fmodf(v.x, divisor),
		fmodf(v.y, divisor),
		fmodf(v.z, divisor)
	});
}
