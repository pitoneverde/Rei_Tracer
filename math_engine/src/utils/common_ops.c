/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 01:02:50 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/30 20:19:16 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/constants.h"
#include "utils/common.h"
#include <math.h>

inline void	swapf(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

inline float	clamp(float val, float min, float max)
{
	return (fminf(fmaxf(val, min), max));
}

inline t_vec3 vec3_right()
{
	return (vec3_x());
}

inline t_vec3 vec3_up()
{
	return (vec3_y());
}

inline t_vec3 vec3_forward()
{
	return ((t_vec3){0.0f, 0.0f, -1.0f});
}
