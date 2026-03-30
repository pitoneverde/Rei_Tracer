/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:57:50 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/30 20:07:37 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/constants.h"

// const t_vec3 VEC3_ZERO = {0.0f, 0.0f, 0.0f};
// const t_vec3 VEC3_ONE = {1.0f, 1.0f, 1.0f};
// const t_vec3 VEC3_X = {1.0f, 0.0f, 0.0f};
// const t_vec3 VEC3_Y = {0.0f, 1.0f, 0.0f};
// const t_vec3 VEC3_Z = {0.0f, 0.0f, 1.0f};

inline t_vec3	vec3_zero()
{
	return ((t_vec3){0.0f, 0.0f, 0.0f});
}

inline t_vec3	vec3_one()
{
	return ((t_vec3){1.0f, 1.0f, 1.0f});
}

inline t_vec3	vec3_x()
{
	return ((t_vec3){1.0f, 0.0f, 0.0f});
}

inline t_vec3	vec3_y()
{
	return ((t_vec3){0.0f, 1.0f, 0.0f});
}

inline t_vec3	vec3_z()
{
	return ((t_vec3){0.0f, 0.0f, 1.0f});
}
