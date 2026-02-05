/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_affine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:22:14 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 20:00:15 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"

// Creates affine transformations matrices

inline t_mat4	mat4_translation(t_vec3 translation)
{
	return ((t_mat4){
		.mat = {
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{translation.x, translation.y, translation.z, 1.0f}
		}
	});
}

inline t_mat4	mat4_scaling(t_vec3 scale)
{
	return ((t_mat4){
		.mat = {
			{scale.x, 0.0f, 0.0f, 0.0f},
			{0.0f, scale.y, 0.0f, 0.0f},
			{0.0f, 0.0f, scale.z, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		}
	});
}