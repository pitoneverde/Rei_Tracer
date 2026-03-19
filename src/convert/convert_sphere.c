/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 20:11:23 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/19 18:38:20 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt_renderer.h"
#include "geometry/sphere.h"

static t_sphere_data convert_sphere(const t_sphere *sp)
{
	t_sphere_data	sp_data;

	sp_data.center = sp->center;
	sp_data.color = vec3_from_color_hex(sp->color.hex);
	sp_data.radius = sp->diameter * 0.5f;
	return (sp_data);
}

int create_sphere(t_sphere_math *math, t_sphere *sphere)
{
	if (!math)
		return (1);
	t_sphere_data	sphere_data = convert_sphere(sphere);
	if (sphere_init(math, sphere_data))
		return (1);
	return (0);	
}
