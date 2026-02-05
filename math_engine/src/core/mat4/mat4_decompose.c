/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_decompose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:23:40 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 22:20:52 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"

// DOESN'T WORK LIKE THAT (need SVD)

// Extract components from transform matrix
void	mat4_decompose(t_mat4 m, t_vec3 *translation, t_vec3 *rotation, t_vec3 *scale)
{
	// TODO
}

t_vec3	mat4_get_translation(t_mat4 m)
{
	// NOT LIKE THIS FFS
	// return ((t_vec3){m.m30, m.m31, m.m32});
	// TODO
}

t_vec3	mat4_get_scale(t_mat4 m)
{
	// NOT LIKE THIS FFS
	// return ((t_vec3){m.m11, m.m22, m.m33});
	// TODO
}