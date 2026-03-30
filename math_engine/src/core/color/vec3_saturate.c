/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_saturate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 22:10:51 by gmu               #+#    #+#             */
/*   Updated: 2026/03/30 22:11:56 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/color.h"

/*Se supera 1 lo imposta a i se e' sotto 0 lo imposta a zero*/
t_vec3	vec3_saturate(t_vec3 color)
{
	t_vec3	result;

	if (color.x < 0.0f)
		result.x = 0.0f;
	else if (color.x > 1.0f)
		result.x = 1.0f;
	else
		result.x = color.x;
	if (color.y < 0.0f)
		result.y = 0.0f;
	else if (color.y > 1.0f)
		result.y = 1.0f;
	else
		result.y = color.y;
	if (color.z < 0.0f)
		result.z = 0.0f;
	else if (color.z > 1.0f)
		result.z = 1.0f;
	else
		result.z = color.z;
	return (result);
}
