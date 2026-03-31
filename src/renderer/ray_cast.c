/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:08:50 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 18:49:46 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"
#include <math.h>

typedef struct s_material
{
	t_vec3 color;
	float diffuse;
	float specular;
	float shininess;
} t_material;

// duplicato: si chiama vec3_mul_comp
// t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
// {
// 	return ((t_vec3){.x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z});
// }

t_vec3 reflect(t_vec3 v, t_vec3 n)
{
	float	dot;

	dot = vec3_dot(v, n);
	t_vec3 term;
	term = vec3_scale(n, 2.0f * dot);
	return (vec3_sub(v, term));
}

// for now it's useless, only for sample shader
// // { return a * (1 - mixValue) + b * mixValue; }
// static inline t_vec3	vec3_mix(t_vec3 a, t_vec3 b, float val)
// {
// 	return (vec3_add(vec3_scale(a, 1.0f - val), vec3_scale(b, val)));
// }

// è la shader generica? ma dove sta la ricorsione dell'ambient lighting?
t_vec3 lighting(t_material material, t_math *math, t_hit hit, t_vec3 eyev)
{
	// effective_color = material.color * light.intensity
	t_vec3 effective_color = vec3_scale(material.color, math->light.intensity);

	// lightv = normalize(light.position - point)
	t_vec3 lightv = vec3_normalize(vec3_sub(math->light.point, hit.point));
	// t_vec3 lightd = vec3_normalize(lightv);
	// float length = vec3_length(lightv);

	// questo e' assolutamente necessario e' il punto che deve cambiare per ambient
	// ambient = effective_color * material.ambient
	// t_vec3 shaded = vec3_gamma_correct(math->ambient.shade, (1 - math->ambient.intensity));//vec3_mix(effective_color, math->ambient.shade, math->ambient.intensity);
	t_vec3 shaded = math->ambient.shade;
	float light_dot_normal = vec3_dot(lightv, hit.normal);
	t_vec3 diffuse;
	t_vec3 specular;

	if (light_dot_normal < 0.0f)
	{
		diffuse = vec3_zero();
		specular = vec3_zero();
	}
	else
	{
		// diffuse = effective_color * material.diffuse * light_dot_normal
		diffuse = vec3_scale(effective_color, material.diffuse * light_dot_normal);

		// reflectv = reflect(-lightv, normalv)
		t_vec3 reflectv = reflect(vec3_neg(lightv), hit.normal);
		float reflect_dot_eye = vec3_dot(reflectv, eyev);

		if (reflect_dot_eye <= 0.0f)
		{
			specular = vec3_zero();
		}
		else
		{
			float factor = powf(reflect_dot_eye, material.shininess);
			specular = vec3_scale(math->light.intensity_scaled_color, material.specular * factor);
		}
	}
	// return shaded;
	(void)shaded;
	t_vec3 shadow = vec3_scale((t_vec3){.x = 255.0f, .y = 0.0f, .z = 0.0f}, -light_dot_normal);
	return (vec3_add(vec3_add(diffuse, vec3_linear_to_srgb(vec3_gamma_correct(vec3_srgb_to_linear(shaded), 2.0f))), shadow));
	//return (diffuse);
	//return (vec3_add(shaded, vec3_add(diffuse, specular)));
	//return (vec3_add(vec3_add(vec3_linear_to_srgb(vec3_gamma_correct(vec3_srgb_to_linear(shaded), 2.0f)), diffuse), specular));
}
// duplicato: già calcolato da sphere_intersect, in t_hit *hit
// t_vec3	sphere_normal_at(t_sphere *sphere, t_vec3 point)
// {
// 	t_vector3 normal;

// 	normal = vec3_sub(point, sphere->center);
// 	return (vec3_normalize(normal));
// }

static t_rgb	vec3_to_rgb(t_vec3 color)
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint32_t	hex;

	r = (uint8_t)clamp(color.x, 0.0f, 255.0f);
	g = (uint8_t)clamp(color.y, 0.0f, 255.0f);
	b = (uint8_t)clamp(color.z, 0.0f, 255.0f);
	hex = (r << 16) | (g << 8) | b;
	return ((t_rgb){.hex = hex});
}

// here go shaders calls and texture mappings
t_rgb	ray_cast(const t_ray ray, t_math *math)
{
	t_vec3	color;
	t_hit	hit;
	int		i;

	color = vec3_zero();	// black
	if (trace(ray, math, &hit, &i))
	{
		// color = math->ambient.shade;
		t_vec3 camera_vector = vec3_neg(ray.direction);
		t_material material = {0};
		// t_vec3	lightv = vec3_sub(math->light.point, hit.point);
		// t_ray shadow = {
		// 	.origin = hit.point,
		// 	.direction = vec3_normalize(lightv),
		// 	.t_max = ray.t_max,
		// 	.t_min = ray.t_min
		// };
		// t_hit shit;
		// int j;
		// if (!trace(shadow, math, &shit, &j) /* && shit.t < vec3_length(lightv)*/)
		// {
			// Assegna materiale in base al tipo di oggetto colpito
			if (hit.obj == OBJ_SPHERE)
				material = (t_material){.color = hit.color, .diffuse = 1.0f,
										.specular = 0.5f, .shininess = 32.0f};
			else if (hit.obj == OBJ_PLANE)
				material = (t_material){.color = hit.color, .diffuse = 0.6f,
										.specular = 0.3f, .shininess = 8.0f};
			else if (hit.obj == OBJ_CYLINDER)
				material = (t_material){.color = hit.color, .diffuse = 0.5f,
										.specular = 0.4f, .shininess = 16.0f};
			// color = hit.color;
			color = lighting(material, math, hit, camera_vector);
		// }
		// else
		// {
		// 	color = lighting(material, math, hit, camera_vector);
		// }
	}
	return (vec3_to_rgb(color));	
}
