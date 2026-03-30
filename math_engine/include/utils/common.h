/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:10:32 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/30 20:14:37 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

// Definition of vec3 constants (macros)
# include "core/vec3.h"

// extern const t_vec3 VEC3_RIGHT;		// alias for x
// extern const t_vec3 VEC3_UP;		// alias for y
// extern const t_vec3 VEC3_FORWARD;	// alias for -z

// # define VEC3_RIGHT VEC3_X
// # define VEC3_UP VEC3_Y
// # define VEC3_FORWARD (t_vec3){0.0f, 0.0f, -1.0f}

t_vec3 vec3_right();
t_vec3 vec3_up();
t_vec3 vec3_forward();

void	swapf(float *a, float *b);
float	clamp(float val, float min, float max);

#endif