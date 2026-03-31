/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_lerp_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 20:52:01 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 23:56:11 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/color.h"

t_vec3	vec3_lerp_color(t_vec3 a, t_vec3 b, float t)
{
	t_vec3	result;

	if (t < 0.0f)
		t = 0.0f;
	if (t > 1.0f)
		t = 1.0f;
	result.x = a.x + (b.x - a.x) * t;
	result.y = a.y + (b.y - a.y) * t;
	result.z = a.z + (b.z - a.z) * t;
	return (result);
}
