/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:24:06 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/05 17:24:07 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"

// Transform point (w=1, includes translation)
t_vec3	mat4_transform_point(t_mat4 m, t_vec3 point)
{

}

// Transform vector (w=0, excludes translation - for directions)
t_vec3	mat4_transform_vector(t_mat4 m, t_vec3 vector)
{

}

// Transform normal (inverse-transpose for non-uniform scaling)
t_vec3	mat4_transform_normal(t_mat4 m, t_vec3 normal)
{

}
