/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_from_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 22:07:22 by gmu               #+#    #+#             */
/*   Updated: 2026/03/30 22:09:24 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/color.h"
#include "minirt_types.h"
#include <stdint.h>

t_vec3	vec3_from_color(float r, float g, float b)
{
	return (vec3_new(r, g, b));
}

t_vec3	vec3_from_color_hex(uint32_t hex)
{
	float	r;
	float	g;
	float	b;
	t_rgb	converter;

	converter.hex = hex;
	r = converter.rgba.red;
	g = converter.rgba.green;
	b = converter.rgba.blue;
	return (vec3_new(r, g, b));
}
