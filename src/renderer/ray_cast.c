/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:08:50 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 15:13:37 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

static	t_rgb	vec3_to_rgb(t_vec3 color)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	r = (uint8_t)fminf(fmaxf(color.x, 0.0f), 255.0f);
	g = (uint8_t)fminf(fmaxf(color.y, 0.0f), 255.0f);
	b = (uint8_t)fminf(fmaxf(color.z, 0.0f), 255.0f);
	uint32_t hex = (r << 16) | (g << 8) | b;
	return ((t_rgb){.hex = hex});
}

// here go shaders calls and texture mappings
t_rgb	ray_cast(const t_ray ray, t_math *math)
{
	t_vec3	color;
	t_hit	hit;
	int		i;

	color = VEC3_ZERO;	// black
	if (trace(ray, math, &hit, &i))
		color = hit.color;
	return (vec3_to_rgb(color));	
}