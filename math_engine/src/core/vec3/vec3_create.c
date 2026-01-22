/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:00:33 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/22 20:00:33 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"

inline t_vec3	vec3_new(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

inline t_vec3	vec3_from_scalar(float s)
{
	return ((t_vec3){s, s, s});
}
