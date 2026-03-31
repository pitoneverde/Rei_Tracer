/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:43:43 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 16:44:45 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"

static t_ambient_data	convert_ambient(const t_ambient *a)
{
	t_ambient_data	ambient_data;

	ambient_data.color = vec3_from_color_hex(a->color.hex);
	ambient_data.intensity = a->brightness;
	return (ambient_data);
}

int	create_ambient(t_ambient_math *math, t_ambient *a)
{
	t_ambient_data	ambient_data;

	if (!math)
		return (1);
	ambient_data = convert_ambient(a);
	if (ambient_init(math, ambient_data))
		return (1);
	return (0);
}
