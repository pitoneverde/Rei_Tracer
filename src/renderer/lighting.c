/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 22:18:38 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 22:22:42 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

t_vec3 lighting(t_material material, t_math *math, t_hit hit, t_vec3 eyev)
{
	t_vec3 effective_color = vec3_scale(material.color, math->light.intensity);
	t_vec3 lightv = vec3_normalize(vec3_sub(math->light.point, hit.point));
	t_vec3 shaded = vec3_scale(material.color, math->ambient.intensity);
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
		diffuse = vec3_scale(effective_color, light_dot_normal);
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
	return (vec3_add(vec3_add(vec3_linear_to_srgb(vec3_gamma_correct(vec3_srgb_to_linear(shaded), 2.0f)), diffuse), specular));
}