/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_comp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 22:32:51 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/22 22:36:28 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"
#include <math.h>

inline t_vec3	vec3_mul_comp(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z});
}

// avoid if possible (division is 3x-10x slower than multiplication)
inline t_vec3	vec3_div_comp(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x / b.x, a.y / b.y, a.z / b.z});
}

inline t_vec3	vec3_min_comp(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){fminf(a.x, b.x), fminf(a.y, b.y), fminf(a.z, b.z)});
}

inline t_vec3	vec3_max_comp(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){fmaxf(a.x, b.x), fmaxf(a.y, b.y), fmaxf(a.z, b.z)});
}
