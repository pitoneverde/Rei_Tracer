/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:56:20 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/23 00:56:22 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include "core/vec3.h"

// extern const t_vec3 VEC3_ZERO;
// extern const t_vec3 VEC3_ONE;

// // standard base
// extern const t_vec3 VEC3_X;
// extern const t_vec3 VEC3_Y;
// extern const t_vec3 VEC3_Z;

# define VEC3_ZERO (t_vec3){0.0f, 0.0f, 0.0f}
# define VEC3_ONE (t_vec3){1.0f, 1.0f, 1.0f}

# define VEC3_X (t_vec3){1.0f, 0.0f, 0.0f}
# define VEC3_Y (t_vec3){0.0f, 1.0f, 0.0f}
# define VEC3_Z (t_vec3){0.0f, 0.0f, 1.0f}

#endif