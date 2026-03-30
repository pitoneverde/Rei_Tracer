/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:57:50 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/30 21:52:43 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/constants.h"

// const t_vec3 VEC3_ZERO = {0.0f, 0.0f, 0.0f};
// const t_vec3 VEC3_ONE = {1.0f, 1.0f, 1.0f};
// const t_vec3 VEC3_X = {1.0f, 0.0f, 0.0f};
// const t_vec3 VEC3_Y = {0.0f, 1.0f, 0.0f};
// const t_vec3 VEC3_Z = {0.0f, 0.0f, 1.0f};

inline t_vec3	vec3_zero(void)
{
	return ((t_vec3){0.0f, 0.0f, 0.0f});
}

inline t_vec3	vec3_one(void)
{
	return ((t_vec3){1.0f, 1.0f, 1.0f});
}

inline t_vec3	vec3_x(void)
{
	return ((t_vec3){1.0f, 0.0f, 0.0f});
}

inline t_vec3	vec3_y(void)
{
	return ((t_vec3){0.0f, 1.0f, 0.0f});
}

inline t_vec3	vec3_z(void)
{
	return ((t_vec3){0.0f, 0.0f, 1.0f});
}
