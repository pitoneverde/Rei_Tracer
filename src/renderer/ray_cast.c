/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:08:50 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 12:22:05 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

// here go shaders calls and texture mappings
t_rgb	ray_cast(const t_ray ray, t_math *math)
{
	t_vec3	color;
	t_hit	hit;
	int		i;

	color = VEC3_ZERO;	// black
	if (trace(ray, math, &hit, &i))
	{
		// color = hit.color;
		
		color = vec3_scale(hit.color, 255.0f);
		vec3_print("color", color);
		// vec3_print("hit", hit.color);
		// // color = vec3_scale(color, 255.0f);
	}
	t_rgb hit_color = {.rgba = 
		{.red = (uint8_t)color.x, .green = (uint8_t)color.y, .blue = (uint8_t)color.z, .alpha = (uint8_t)0}
	};
	return (hit_color);
}