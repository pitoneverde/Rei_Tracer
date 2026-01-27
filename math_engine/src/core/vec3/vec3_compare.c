/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_compare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:48:33 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/26 23:23:07 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"
#include <math.h>

inline bool	vec3_equal(t_vec3 a, t_vec3 b, float epsilon)
{
	return (
		fabsf(a.x - b.x) <= epsilon
		&& fabsf(a.y - b.y) <= epsilon
		&& fabsf(a.z - b.z) <= epsilon
	);
}

inline bool	vec3_is_zero(t_vec3 v, float epsilon)
{
	return (fabsf(v.x) <= epsilon
		&& fabsf(v.y) <= epsilon && fabsf(v.z) <= epsilon);
}

inline bool	vec3_is_finite(t_vec3 v)
{
	return (isfinite(v.x) && isfinite(v.y) && isfinite(v.z));
}

inline bool	vec3_any_nan(t_vec3 v)
{
	return (isnan(v.x) || isnan(v.y) || isnan(v.z));
}
