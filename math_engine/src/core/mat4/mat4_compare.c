/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_compare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:23:11 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/03 22:54:46 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"
#include "math.h"

inline bool	mat4_equal(t_mat4 a, t_mat4 b, float epsilon)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (!(fabsf(a.arr[i] - b.arr[i]) <= epsilon))
			return (false);
		i++;
	}
	return (true);
}

inline bool	mat4_any_nan(t_mat4 m)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (isnanf(m.arr[i]))
			return (true);
		i++;
	}
	return (false);
}

inline bool	mat4_is_finite(t_mat4 m)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (!isfinite(m.arr[i]))
			return (false);
		i++;
	}
	return (true);
}
