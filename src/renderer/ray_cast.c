/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:08:50 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/16 19:20:44 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

t_rgb	ray_cast(t_ray ray)
{
	// printf("ray:\n");
	// vec3_print("origin", ray.origin);
	// vec3_print("direction", ray.direction);
	t_vec3 color = vec3_scale(vec3_scale(vec3_add(VEC3_ONE, ray.direction), 0.5), 255.0f);
	// color = vec3_linear_to_srgb(color);
	// vec3_print("origin", ray.origin);
	// vec3_print("direction", ray.direction);
	t_rgb hit_color = {.rgba = {.red = (uint8_t)color.x, .green = (uint8_t)color.y, .blue = (uint8_t)color.z, .alpha = (uint8_t)0}};
	// printf("color: hex->%x, rgba->[%d, %d, %d, %d]", hit_color.hex, hit_color.rgba.red, hit_color.rgba.green, hit_color.rgba.blue, hit_color.rgba.alpha);
	fflush(stdout);
	return hit_color;
}