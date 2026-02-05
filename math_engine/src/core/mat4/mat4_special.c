/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_special.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:24:01 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 17:24:04 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"

// Build rotation matrix that aligns 'from' vector to 'to' vector
t_mat4	mat4_align_vectors(t_vec3 from, t_vec3 to)
{
	
}

// Create billboard matrix (faces camera, useful for sprites/quads)
t_mat4	mat4_billboard(t_vec3 position, t_vec3 camera_pos, t_vec3 camera_up)
{

}

// Linear interpolation
t_mat4	mat4_lerp(t_mat4 a, t_mat4 b, float t)
{

}
