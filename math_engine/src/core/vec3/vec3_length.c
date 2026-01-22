/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_length.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:48:16 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/22 21:53:47 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"
#include <math.h>

// vector length
inline float	vec3_length(t_vec3 v)
{
	return (sqrtf(vec3_dot(v, v)));
}

// vector length sqaure: faster, no sqrt
inline float	vec3_length_sq(t_vec3 v)
{
	return (vec3_dot(v, v));
}
