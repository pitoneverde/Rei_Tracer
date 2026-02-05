/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:24:09 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 22:32:57 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"
#include "math.h"
#include "utils/math_constants.h"

bool	mat4_is_affine(t_mat4 m, float epsilon)
{
	return (
		fabsf(m.m03) <= epsilon
		&& fabsf(m.m13) <= epsilon
		&& fabsf(m.m23) <= epsilon
		&& fabsf(m.m33 - 1.0f) <= epsilon
	);
}

// Formula -> M * M^T = I
// semantically incorrect for translation matrices (or with translation component)
bool	mat4_is_orthogonal(t_mat4 m, float epsilon)
{
	return (mat4_is_identity(mat4_mul(m, mat4_transpose(m)), MATH_EPSILON));
}

bool	mat4_is_identity(t_mat4 m, float epsilon)
{
	return (
		fabsf(m.m00 - 1.0f) <= epsilon
		&& fabsf(m.m01) <= epsilon
		&& fabsf(m.m02) <= epsilon
		&& fabsf(m.m03) <= epsilon
		&& fabsf(m.m10) <= epsilon
		&& fabsf(m.m11 - 1.0f) <= epsilon
		&& fabsf(m.m12) <= epsilon
		&& fabsf(m.m13) <= epsilon
		&& fabsf(m.m20) <= epsilon
		&& fabsf(m.m21) <= epsilon
		&& fabsf(m.m22 - 1.0f) <= epsilon
		&& fabsf(m.m23) <= epsilon
		&& fabsf(m.m30) <= epsilon
		&& fabsf(m.m31) <= epsilon
		&& fabsf(m.m32) <= epsilon
		&& fabsf(m.m33 - 1.0f) <= epsilon
	);
}