/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:04:54 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 18:32:19 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"
#include "core/mat4.h"
#include <stdio.h>

void	vec3_print(const char *name, t_vec3 v)
{
	printf("%s:\n", name);
	printf("{%7.3f, %7.3f, %7.3f}\n", v.x, v.y, v.z);
}

// void	mat4_print(const char *name, t_mat4 m)
// {
//     printf("%s:\n", name);
// 	printf("{%f, %f, %f, %f}\n", m.m00, m.m01, m.m02, m.m03);
// 	printf("{%f, %f, %f, %f}\n", m.m10, m.m11, m.m12, m.m13);
// 	printf("{%f, %f, %f, %f}\n", m.m20, m.m21, m.m22, m.m23);
// 	printf("{%f, %f, %f, %f}\n", m.m30, m.m31, m.m32, m.m33);
// }

void	mat4_print(const char *name, t_mat4 m)
{
	printf("%s:\n", name);
	for (int i = 0; i < 4; ++i)
		printf("  [ %7.3f %7.3f %7.3f %7.3f ]\n",
			m.mat[i][0], m.mat[i][1], m.mat[i][2], m.mat[i][3]);
}