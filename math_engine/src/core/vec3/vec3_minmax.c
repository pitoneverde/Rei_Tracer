/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_minmax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 22:39:07 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/22 23:05:43 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/vec3.h"
#include <math.h>

//min coord
inline float	vec3_min(t_vec3 v)
{
	float	t;

	t = fminf(v.x, v.y);
	return (fminf(t, v.z));
}

//max coord
inline float	vec3_max(t_vec3 v)
{
	float	t;

	t = fmaxf(v.x, v.y);
	return (fmaxf(t, v.z));
}
