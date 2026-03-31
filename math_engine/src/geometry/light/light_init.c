/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 23:42:54 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 23:20:35 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/light.h"

// any precomputations used by the engine go there
int	light_init(t_light_math *light, t_light_data data)
{
	if (!light)
		return (1);
	light->color = data.color;
	light->intensity = data.intensity;
	light->point = data.point;
	light->shade = data.shade;
	return (0);
}
