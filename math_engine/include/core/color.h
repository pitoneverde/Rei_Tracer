/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:15:04 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 20:51:05 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "core/vec3.h"
# include <math.h>
# include <stdint.h>

// colors
t_vec3	vec3_from_color_hex(uint32_t hex);
t_vec3	vec3_from_color(float r, float g, float b);
t_vec3	vec3_srgb_to_linear(t_vec3 srgb_color);
t_vec3	vec3_linear_to_srgb(t_vec3 linear_color);
// Clamp to [0,1]
t_vec3	vec3_saturate(t_vec3 color);
t_vec3	vec3_gamma_correct(t_vec3 color, float gamma);
// Grayscale conversion
float	vec3_luminance(t_vec3 color);
// Better for colors?
t_vec3 vec3_lerp_color(t_vec3 a, t_vec3 b, float t);

#endif