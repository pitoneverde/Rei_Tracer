/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:30:50 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 16:34:47 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_H
# define AMBIENT_H

#include "core/vec3.h"

typedef struct s_ambient_data
{
	t_vec3	color;
	float	intensity;
}	t_ambient_data;

typedef struct s_ambient_math
{
	t_vec3	color;
	float	intensity;
	t_vec3	shade;		// color * insensity
}	t_ambient_math;

int	ambient_init(t_ambient_math *math, t_ambient_data data);

#endif