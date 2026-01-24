/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:54:29 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/24 02:07:21 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"
#include "utils/math_constants.h"
#include <math.h>

// compiler will likely optimize 1/sqrtf to 
// rsqrtf with release build (loses a bit of precision).
// use only if certain the vector has len > 0, 
// otherwise you get infinity or NaN (and you deserve the crash) 
inline t_vec3	vec3_normalize(t_vec3 v)
{
	float	inv;

	inv = 1.0f / sqrtf(vec3_length_sq(v));
	return (vec3_scale(v, inv));
}

// handles zero-length comparing len_sq to epsilon_sq is
// mathematically equivalent of lenght to epsilon 
inline t_vec3	vec3_normalize_or(t_vec3 v, t_vec3 fallback)
{
	float	len_sq;
	float	len_inv;

	len_sq = vec3_length_sq(v);
	if (len_sq > MATH_EPSILON_SQ)
	{
		len_inv = 1.0f / sqrtf(len_sq);
		return (vec3_scale(v, len_inv));
	}
	return (fallback);
}

inline bool	vec3_is_normalized(t_vec3 v)
{
	return (!vec3_is_zero(v, MATH_EPSILON) && vec3_length(v) == 1);
}
