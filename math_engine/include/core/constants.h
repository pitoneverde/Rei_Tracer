/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:56:20 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/30 20:13:46 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include "vec3.h"

// extern const t_vec3 VEC3_ZERO;
// extern const t_vec3 VEC3_ONE;

// // standard base
// extern const t_vec3 VEC3_X;
// extern const t_vec3 VEC3_Y;
// extern const t_vec3 VEC3_Z;

// # define VEC3_ZERO (t_vec3){0.0f, 0.0f, 0.0f}
// # define VEC3_ONE (t_vec3){1.0f, 1.0f, 1.0f}

// # define VEC3_X (t_vec3){1.0f, 0.0f, 0.0f}
// # define VEC3_Y (t_vec3){0.0f, 1.0f, 0.0f}
// # define VEC3_Z (t_vec3){0.0f, 0.0f, 1.0f}

t_vec3	vec3_zero();
t_vec3	vec3_one();
t_vec3	vec3_x();
t_vec3	vec3_y();
t_vec3	vec3_z();

#endif