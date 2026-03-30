/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:52:39 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/30 20:26:30 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/intersection.h"
#include "utils/math_constants.h"
#include "utils/common.h"
#include <math.h>

bool	solve_quadratic(t_quad *eq)
{
	float	delta;
	float	q;

	delta = eq->b * eq->b - 4 * eq->a * eq->c;
	if (delta < 0.0f)
		return (false);
	else if (delta <= math_epsilon())
	{
		eq->x0 = -0.5f * eq->b / eq->a;
		eq->x1 = eq->x0;
	}
	else
	{
		if (eq->b > 0.0f)
			q = -0.5f * (eq->b + sqrtf(delta));
		else
			q = -0.5f * (eq->b - sqrtf(delta));
		eq->x0 = q / eq->a;
		eq->x1 = eq->c / q;
	}
	if (eq->x0 > eq->x1)
		swapf(&eq->x0, &eq->x1);
	return (true);
}
