/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 22:19:23 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 22:42:02 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	float	dot;
	t_vec3	term;

	dot = vec3_dot(v, n);
	term = vec3_scale(n, 2.0f * dot);
	return (vec3_sub(v, term));
}

t_rgb	vec3_to_rgb(t_vec3 color)
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
