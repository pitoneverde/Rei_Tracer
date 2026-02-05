/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_compare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:23:11 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 20:07:53 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"
#include "math.h"

bool	mat4_equal(t_mat4 a, t_mat4 b, float epsilon)
{
	return (
		fabsf(a.m00 - b.m00) <= epsilon
		&& fabsf(a.m01 - b.m01) <= epsilon
		&& fabsf(a.m02 - b.m02) <= epsilon
		&& fabsf(a.m03 - b.m03) <= epsilon
		&& fabsf(a.m10 - b.m10) <= epsilon
		&& fabsf(a.m11 - b.m11) <= epsilon
		&& fabsf(a.m12 - b.m12) <= epsilon
		&& fabsf(a.m13 - b.m13) <= epsilon
		&& fabsf(a.m20 - b.m20) <= epsilon
		&& fabsf(a.m21 - b.m21) <= epsilon
		&& fabsf(a.m22 - b.m22) <= epsilon
		&& fabsf(a.m23 - b.m23) <= epsilon
		&& fabsf(a.m30 - b.m30) <= epsilon
		&& fabsf(a.m31 - b.m31) <= epsilon
		&& fabsf(a.m32 - b.m32) <= epsilon
		&& fabsf(a.m33 - b.m33) <= epsilon
	);
}

bool	mat4_any_nan(t_mat4 m)
{
	return (
		isnanf(m.m00)
		|| isnanf(m.m01)
		|| isnanf(m.m02)
		|| isnanf(m.m03)
		|| isnanf(m.m10)
		|| isnanf(m.m11)
		|| isnanf(m.m12)
		|| isnanf(m.m13)
		|| isnanf(m.m20)
		|| isnanf(m.m21)
		|| isnanf(m.m22)
		|| isnanf(m.m23)
		|| isnanf(m.m30)
		|| isnanf(m.m31)
		|| isnanf(m.m32)
		|| isnanf(m.m33)
	);
}

bool	mat4_is_finite(t_mat4 m)
{
	return (
		isfinite(m.m00)
		&& isfinite(m.m01)
		&& isfinite(m.m02)
		&& isfinite(m.m03)
		&& isfinite(m.m10)
		&& isfinite(m.m11)
		&& isfinite(m.m12)
		&& isfinite(m.m13)
		&& isfinite(m.m20)
		&& isfinite(m.m21)
		&& isfinite(m.m22)
		&& isfinite(m.m23)
		&& isfinite(m.m30)
		&& isfinite(m.m31)
		&& isfinite(m.m32)
		&& isfinite(m.m33)
	);
}
