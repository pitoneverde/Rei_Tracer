/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 23:38:01 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/25 23:42:35 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

// any middle precomputations go there (idk, maybe 1/intensity?)
static t_light_data	convert_light(const t_light *light)
{
	t_light_data	light_data;

	light_data.point = light->position;
	light_data.intensity = light->brightness;
	light_data.color = vec3_from_color_hex(light->color.hex);
	light_data.intensity_scaled_color = vec3_scale(light_data.color, light_data.intensity);
	return (light_data);
}

int	create_light(t_light_math *math, t_light *light)
{
	t_light_data	light_data;

	if (!math)
		return (1);
	light_data = convert_light(light);
	if (light_init(math, light_data))
		return (1);
	return (0);
}