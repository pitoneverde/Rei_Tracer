/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 23:34:37 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/25 23:44:12 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
#define LIGHT_H

#include "core/vec3.h"

typedef struct s_light_math
{
	t_vec3	color;
	float	intensity;
	t_vec3	point;
	// any further precomputed values...
}	t_light_math;

typedef struct s_light_data
{
	t_vec3	color;
	float	intensity;
	t_vec3	point;
	// any precomputed values...
}	t_light_data;

int		light_init(t_light_math *light, t_light_data data);

#endif