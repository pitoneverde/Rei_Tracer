/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_coordinates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:01:51 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/19 22:27:57 by sabruma          ###   ########.fr       */
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
// commented because unused and norminette freaks out
// void	vec3_coordinate_system(t_vec3 a, t_vec3 *b, t_vec3 *c)
// {
// 	t_vec3	b_ortho;
// 	t_vec3	c_ortho;

// 	if (vec3_is_zero(a, MATH_EPSILON))
// 		return ;
// 	b_ortho = vec3_normalize_or(
// 		vec3_sub(*b, vec3_project(*b, a)),
// 		vec3_normalize_or(
// 			vec3_cross(a, VEC3_X),
// 			vec3_normalize_or(
// 				vec3_cross(a, VEC3_Y),
// 				vec3_normalize(vec3_cross(a, VEC3_Z))
// 	)));
// 	c_ortho = vec3_sub(*c, vec3_project(*c, a));
// 	c_ortho = vec3_sub(c_ortho, vec3_project(c_ortho, b_ortho));
// 	c_ortho = vec3_normalize_or(
// 		c_ortho,
// 		vec3_normalize(vec3_cross(a, b_ortho)));
// 	if (vec3_volume(a, b_ortho, c_ortho) < 0.0f)	//cyclic permutation
// 		c_ortho = vec3_scale(c_ortho, -1.0f);
// 	*b = b_ortho;
// 	*c = c_ortho;
// }

// faster, use in hot path (cross-product method)
// n is a normal, so it's assumed already normalized
// t & b are tangent and bitangent, can be any vectors != 0
inline void	vec3_orthonormal_basis(t_vec3 n, t_vec3 *t, t_vec3 *b)
{
	vec3_normalize(*t);
	*b = vec3_normalize(vec3_cross(n, *t));
	*t = vec3_cross(n, *b);
}

// (b - a) x (c - a)
// a, b, c triangle vertices in CCW winding order
static inline float	edge_function(t_vec2 a, t_vec2 b, t_vec2 c)
{
	return ((c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x));
}

inline t_vec3	vec3_barycentric(t_vec2 a, t_vec2 b, t_vec2 c, t_vec2 p)
{
	float	w0;
	float	w1;
	float	w2;

	w0 = edge_function(b, c, p);
	w1 = edge_function(c, a, p);
	w2 = edge_function(a, b, p);
	return ((t_vec3){w0, w1, w2});
}
