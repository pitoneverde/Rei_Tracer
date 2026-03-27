/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:08:50 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/23 00:43:36 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"
#include <math.h>

typedef struct s_material
{
	t_vec3 color;
	float ambient;
	float diffuse;
	float specular;
	float shininess;
} t_material;

t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){.x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z});
}

t_vec3 reflect(t_vec3 v, t_vec3 n)
{
	float	dot;

	dot = vec3_dot(v, n);
	t_vec3 term;
	term = vec3_scale(n, 2.0f * dot);
	return (vec3_sub(v, term));
}

t_vec3 lighting(t_material material, t_light_math light, t_vec3 point, t_vec3 eyev, t_vec3 normalv)
{
    // effective_color = material.color * light.intensity
    t_vec3 effective_color = vec3_mul(material.color, light.intensity);

    // lightv = normalize(light.position - point)
    t_vec3 lightv = vec3_norm(vec3_sub(light.point, point));

    // ambient = effective_color * material.ambient
    t_vec3 ambient = vec3_scale(effective_color, material.ambient);

    float light_dot_normal = vec3_dot(lightv, normalv);
    t_vec3 diffuse;
    t_vec3 specular;

    if (light_dot_normal < 0.0f)
    {
        diffuse = VEC3_ZERO;
        specular = VEC3_ZERO;
    }
    else
    {
        // diffuse = effective_color * material.diffuse * light_dot_normal
        diffuse = vec3_scale(effective_color, material.diffuse * light_dot_normal);

        // reflectv = reflect(-lightv, normalv)
        t_vec3 reflectv = reflect(vec3_neg(lightv), normalv);
        float reflect_dot_eye = vec3_dot(reflectv, eyev);

        if (reflect_dot_eye <= 0.0f)
        {
            specular = VEC3_ZERO;
        }
        else
        {
            float factor = powf(reflect_dot_eye, material.shininess);
            specular = vec3_scale(light.intensity_scaled_color, material.specular * factor);
        }
    }
    return vec3_add(ambient, vec3_add(diffuse, specular));
}

t_vec3	sphere_normal_at(t_sphere *sphere, t_vec3 point)
{
	t_vector3 normal;

	normal = vec3_sub(point, sphere->center);
	return (vec3_normalize(normal));
}

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

// { return a * (1 - mixValue) + b * mixValue; }
static inline t_vec3	vec3_mix(t_vec3 a, t_vec3 b, float val)
{
	return (vec3_add(vec3_scale(a, 1.0f - val), vec3_scale(b, val)));
}

// here go shaders calls and texture mappings
t_rgb ray_cast(const t_ray ray, t_math *math)
{
    t_hit   hit;
    int     idx;

    // Se c'è un'intersezione
    if (trace(ray, math, &hit, &idx))
    {
        t_vec3 camera_vector = vec3_neg(ray.direction);
        t_material material;

        // Assegna materiale in base al tipo di oggetto colpito
        if (hit.obj == OBJ_SPHERE)
            material = (t_material){.color = hit.color, .ambient = 0.1f, .diffuse = 0.7f,
                                    .specular = 0.5f, .shininess = 32.0f};
        else if (hit.obj == OBJ_PLANE)
            material = (t_material){.color = hit.color, .ambient = 0.1f, .diffuse = 0.6f,
                                    .specular = 0.3f, .shininess = 8.0f};
        else if (hit.obj == OBJ_CYLINDER)
            material = (t_material){.color = hit.color, .ambient = 0.1f, .diffuse = 0.5f,
                                    .specular = 0.4f, .shininess = 16.0f};
        else
            return (vec3_to_rgb(VEC3_ZERO));  // caso non previsto

        t_vec3 color = lighting(material, math->light, hit.point, camera_vector, hit.normal);
        return (vec3_to_rgb(color));
    }
    else
    {
        // Nessuna intersezione → colore di sfondo (nero)
        return (vec3_to_rgb(VEC3_ZERO));
    }
	// basic checkerboard shader to give some volume
	// if (hit.obj == OBJ_SPHERE)
	// {
	// 	float scale = 5.0f;
	// 	t_vec2 tex;
	// 	tex.x = (1 + atan2(hit.normal.z, hit.normal.x) / MATH_PI) * 0.5;
    //     tex.y = acosf(hit.normal.y) / MATH_PI;
	// 	float pattern = ((fmodf(tex.x * scale, 1.0f) > 0.5f) ^ (fmodf(tex.y * scale, 1.0f) > 0.5f));
	// 	color = vec3_max_comp(VEC3_ZERO, vec3_scale(vec3_mix(hit.color, vec3_scale(hit.color, 0.8f), pattern), vec3_dot(hit.normal, vec3_neg(ray.direction))));
	// }
}
