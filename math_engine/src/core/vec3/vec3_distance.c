/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 23:06:41 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/22 23:16:24 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"

// distance between two points
inline float	vec3_distance(t_vec3 a, t_vec3 b)
{
	return (vec3_length(vec3_sub(a, b)));
}

// faster version without sqrt
inline float	vec3_distance_sq(t_vec3 a, t_vec3 b)
{
	return (vec3_length_sq(vec3_sub(a, b)));
}
