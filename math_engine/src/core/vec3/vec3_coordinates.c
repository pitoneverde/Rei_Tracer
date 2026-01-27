/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_coordinates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:01:51 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/27 00:49:22 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"
#include "utils/math_constants.h"
#include "core/constants.h"

// build othonormal basis with Gram-Schmidt 
// (a remains unchanged, assumed normalized)
// if a is zero, can't build basis
// ensures right-handed system = check for negative
// b and c must be initialized to apply this method
void	vec3_coordinate_system(t_vec3 a, t_vec3 *b, t_vec3 *c)
{
	t_vec3	b_ortho;
	t_vec3	c_ortho;

	if (vec3_is_zero(a, MATH_EPSILON))
		return ;
	b_ortho = vec3_normalize_or(
		vec3_sub(*b, vec3_project(*b, a)),
		vec3_normalize_or(
			vec3_cross(a, VEC3_X),
			vec3_normalize_or(
				vec3_cross(a, VEC3_Y),
				vec3_normalize(vec3_cross(a, VEC3_Z))
	)));
	c_ortho = vec3_sub(*c, vec3_project(*c, a));
	c_ortho = vec3_sub(c_ortho, vec3_project(c_ortho, b_ortho));
	c_ortho = vec3_normalize_or(
		c_ortho,
		vec3_normalize(vec3_cross(a, b_ortho)));
	if (vec3_volume(a, b_ortho, c_ortho) < 0.0f)	//cyclic permutation
		c_ortho = vec3_scale(c_ortho, -1.0f);
	*b = b_ortho;
	*c = c_ortho;
}
