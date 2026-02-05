/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:23:04 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 18:57:20 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"

// Basic operations

inline t_mat4	mat4_add(t_mat4 a, t_mat4 b)
{
	return ((t_mat4){
		.mat = {
			{a.m00 + b.m00, a.m01 + b.m01, a.m02 + b.m02, a.m03 + b.m03},
			{a.m10 + b.m10, a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13},
			{a.m20 + b.m20, a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23},
			{a.m30 + b.m30, a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33}
		}
	});
}

inline t_mat4	mat4_sub(t_mat4 a, t_mat4 b)
{
	return ((t_mat4){
		.mat = {
			{a.m00 - b.m00, a.m01 - b.m01, a.m02 - b.m02, a.m03 - b.m03},
			{a.m10 - b.m10, a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13},
			{a.m20 - b.m20, a.m21 - b.m21, a.m22 - b.m22, a.m23 - b.m23},
			{a.m30 - b.m30, a.m31 - b.m31, a.m32 - b.m32, a.m33 - b.m33}
		}
	});
}

t_mat4	mat4_mul(t_mat4 a, t_mat4 b)
{
	int		i;
	int		j;
	t_mat4	mul;

	i = 0;
	j = 0;
	while (++i < 4)
	{
		while (++j < 4)
		{
			mul.mat[i][j]
				= a.mat[i][0] * b.mat[0][j]
				+ a.mat[i][1] * b.mat[1][j]
				+ a.mat[i][2] * b.mat[2][j]
				+ a.mat[i][3] * b.mat[3][j];
		}
	}
	return (mul);
}

inline t_mat4	mat4_scale(t_mat4 m, float s)
{
	return ((t_mat4){
		.mat = {
			{s * m.m00, s * m.m01, s * m.m02, s * m.m03},
			{s * m.m10, s * m.m11, s * m.m12, s * m.m13},
			{s * m.m20, s * m.m21, s * m.m22, s * m.m23},
			{s * m.m30, s * m.m31, s * m.m32, s * m.m33}
		}
	});
}

inline t_mat4	mat4_neg(t_mat4 m)
{
	return ((t_mat4){
		.mat = {
			{-m.m00, -m.m01, -m.m02, -m.m03},
			{-m.m10, -m.m11, -m.m12, -m.m13},
			{-m.m20, -m.m21, -m.m22, -m.m23},
			{-m.m30, -m.m31, -m.m32, -m.m33}
		}
	});
}
