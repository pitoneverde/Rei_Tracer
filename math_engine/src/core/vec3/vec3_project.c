/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_project.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 22:43:42 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/24 02:07:21 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"
#include "utils/math_constants.h"

// by formula, can't project onto zero vector
inline t_vec3	vec3_project(t_vec3 v, t_vec3 onto)
{
	float	len_sq;

	len_sq = vec3_length_sq(onto);
	if (len_sq > MATH_EPSILON_SQ)
		return (vec3_scale(onto, vec3_dot(v, onto) / len_sq));
	return (VEC3_ZERO);
}

// rejection = v - projection over onto
inline t_vec3	vec3_reject(t_vec3 v, t_vec3 onto)
{
	return (vec3_sub(v, vec3_project(v, onto)));
}
