/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 22:18:38 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 23:27:12 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

static t_vec3	specular(t_math *math, t_material m, t_vec3 lv, t_hit hit)
{
	t_vec3	specular;
	t_vec3	reflectv;
	float	reflect_dot_eye;
	float	factor;

	reflectv = reflect(vec3_neg(lv), hit.normal);
	reflect_dot_eye = vec3_dot(reflectv, vec3_neg(hit.ray.direction));
	if (reflect_dot_eye <= 0.0f)
		specular = vec3_zero();
	else
	{
		factor = powf(reflect_dot_eye, m.shininess);
		specular = vec3_scale(math->light.shade, m.specular * factor);
	}
	return (specular);
}

t_vec3	lighting(t_material material, t_math *math, t_hit hit, t_vec3 eyev)
{
	t_vec3	lightv;
	t_vec3	ambient;
	float	dot;
	t_vec3	diff;
	t_vec3	shiny;

	lightv = vec3_normalize(vec3_sub(math->light.point, hit.point));
	ambient = vec3_scale(hit.color, math->ambient.intensity);
	dot = vec3_dot(lightv, hit.normal);
	diff = vec3_zero();
	shiny = vec3_zero();
	if (dot >= 0.0f)
	{
		diff = vec3_scale(vec3_scale(hit.color, math->light.intensity), dot);
		shiny = specular(math, material, lightv, hit);
	}
	return (vec3_add(vec3_add(vec3_linear_to_srgb(vec3_gamma_correct(vec3_srgb_to_linear(ambient), 2.0f)), diff), shiny));
}
