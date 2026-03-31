/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:08:50 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 22:27:30 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"
#include <math.h>

// duplicato: si chiama vec3_mul_comp
// t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
// {
// 	return ((t_vec3){.x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z});
// }

// for now it's useless, only for sample shader
// // { return a * (1 - mixValue) + b * mixValue; }
// static inline t_vec3	vec3_mix(t_vec3 a, t_vec3 b, float val)
// {
// 	return (vec3_add(vec3_scale(a, 1.0f - val), vec3_scale(b, val)));
// }

// here go shaders calls and texture mappings
t_rgb	ray_cast(const t_ray ray, t_math *math)
{
	t_vec3	color;
	t_hit	hit;
	int		i;

	color = vec3_zero();	// black
	if (trace(ray, math, &hit, &i))
	{
		color = vec3_scale(hit.color, math->ambient.intensity);
		color = vec3_linear_to_srgb(vec3_gamma_correct(vec3_srgb_to_linear(color), 2.0f));
		t_vec3 camera_vector = vec3_neg(ray.direction);
		t_material material = {0};
		t_vec3	lightv = vec3_sub(math->light.point, hit.point);
		t_ray shadow = {
			.origin = hit.point,
			.direction = vec3_normalize(lightv),
			.t_max = ray.t_max,
			.t_min = ray.t_min
		};
		t_hit shit;
		int j;
		if (!trace(shadow, math, &shit, &j))
		{
			if (hit.obj == OBJ_SPHERE)
				material = (t_material){.color = hit.color, .specular = 0.5f, .shininess = 32.0f};
			else if (hit.obj == OBJ_PLANE)
				material = (t_material){.color = hit.color, .specular = 0.3f, .shininess = 8.0f};
			else if (hit.obj == OBJ_CYLINDER)
				material = (t_material){.color = hit.color, .specular = 0.4f, .shininess = 16.0f};
			color = lighting(material, math, hit, camera_vector);
		}	
	}
	return (vec3_to_rgb(color));	
}

// static t_vec3	cast_shadows(const t_hit *hit, t_math *math, t_ray shadow)
