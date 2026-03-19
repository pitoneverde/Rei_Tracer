/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:08:50 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/19 18:25:22 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"
#include <math.h>

static	t_rgb	vec3_to_rgb(t_vec3 color)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	r = (uint8_t)clamp(color.x, 0.0f, 255.0f);
	g = (uint8_t)clamp(color.y, 0.0f, 255.0f);
	b = (uint8_t)clamp(color.z, 0.0f, 255.0f);
	uint32_t hex = (r << 16) | (g << 8) | b;
	return ((t_rgb){.hex = hex});
}

static inline t_vec3 vec3_mix(t_vec3 a, t_vec3 b, float val)
{
	return (vec3_add(vec3_scale(a, 1.0f - val), vec3_scale(b, val)));
}
// { return a * (1 - mixValue) + b * mixValue; }
// here go shaders calls and texture mappings
t_rgb	ray_cast(const t_ray ray, t_math *math)
{
	t_vec3	color;
	t_hit	hit;
	int		i;

	color = VEC3_ZERO;	// black
	if (trace(ray, math, &hit, &i))
		color = hit.color;
	// basic checkerboard shader to give some volume
	if (hit.obj == OBJ_SPHERE)
	{
		float scale = 5.0f;
		t_vec2 tex;
		tex.x = (1 + atan2(hit.normal.z, hit.normal.x) / MATH_PI) * 0.5;
        tex.y = acosf(hit.normal.y) / MATH_PI;
		float pattern = ((fmodf(tex.x * scale, 1.0f) > 0.5f) ^ (fmodf(tex.y * scale, 1.0f) > 0.5f));
		color = vec3_max_comp(VEC3_ZERO, vec3_scale(vec3_mix(hit.color, vec3_scale(hit.color, 0.8f), pattern), vec3_dot(hit.normal, vec3_neg(ray.direction))));
	}
	return (vec3_to_rgb(color));	
}