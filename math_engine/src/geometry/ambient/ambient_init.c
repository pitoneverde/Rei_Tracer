/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:37:20 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 23:56:37 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/ambient.h"

int	ambient_init(t_ambient_math *math, t_ambient_data data)
{
	if (!math)
		return (1);
	math->intensity = data.intensity;
	math->color = data.color;
	math->shade = vec3_scale(data.color, data.intensity);
	return (0);
}
