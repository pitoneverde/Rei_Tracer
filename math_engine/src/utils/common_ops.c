/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 01:02:50 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 18:33:03 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
