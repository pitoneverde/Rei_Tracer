/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:04:54 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 17:45:42 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"
#include "core/mat4.h"
#include <stdio.h>

void	vec3_print(t_vec3 v)
{
	printf("{%f, %f, %f}\n", v.x, v.y, v.z);
}

void	mat4_print(t_mat4 m)
{
	printf("[");
	printf("{%f, %f, %f, %f}\n", m.m00, m.m01, m.m02, m.m03);
	printf("{%f, %f, %f, %f}\n", m.m10, m.m11, m.m12, m.m13);
	printf("{%f, %f, %f, %f}\n", m.m20, m.m21, m.m22, m.m23);
	printf("{%f, %f, %f, %f}", m.m30, m.m31, m.m32, m.m33);
	printf("]\n");
}