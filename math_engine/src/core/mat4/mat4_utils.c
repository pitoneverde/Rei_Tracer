/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:24:12 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 18:31:35 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"

inline void	mat4_to_float_array(t_mat4 m, float out[16])
{
	out[0] = m.m00;
	out[1] = m.m01;
	out[2] = m.m02;
	out[3] = m.m03;
	out[4] = m.m10;
	out[5] = m.m11;
	out[6] = m.m12;
	out[7] = m.m13;
	out[8] = m.m20;
	out[9] = m.m21;
	out[10] = m.m22;
	out[11] = m.m23;
	out[12] = m.m30;
	out[13] = m.m31;
	out[14] = m.m32;
	out[15] = m.m33;
}