/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_inverse_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 23:55:27 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 18:34:28 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"
#include "utils/common.h"
// #include "utils/debug.h"

#include <math.h>

// 1 on error, 0 on success
int	fwd_elimination_inv(t_mat4 *m, t_mat4 *s)
{
	int		pivot;
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		pivot = choose_pivot(m, i);
		if (pivot == -1)
			return (1);
		if (pivot != i)
		{
			j = 0;
			while (j < 4)
			{
				swapf(&m->mat[i][j], &m->mat[pivot][j]);
				swapf(&s->mat[i][j], &s->mat[pivot][j]);
				j++;
			}
		}
		eliminate_below_inv(m, s, i);
		i++;
	}
	return (0);
}

// returns -1 on singular matrix
int	choose_pivot(t_mat4 *m, int i)
{
	int		pivot;
	int		j;
	float	pivot_value;
	float	tmp;

	pivot = i;
	pivot_value = fabsf(m->mat[i][i]);
	j = i + 1;
	while (j < 4)
	{
		tmp = fabsf(m->mat[j][i]);
		if (tmp > pivot_value)
		{
			pivot = j;
			pivot_value = tmp;
		}
		j++;
	}
	if (fabsf(pivot_value) < 1e-6)
		return (-1);
	return (pivot);
}

// set under diagonal to 0 to improve stability
void	eliminate_below_inv(t_mat4 *m, t_mat4 *s, int i)
{
	int		j;
	int		k;
	float	ratio;

	j = i + 1;
	while (j < 4)
	{
		ratio = m->mat[j][i] / m->mat[i][i];
		k = 0;
		while (k < 4)
		{
			m->mat[j][k] -= ratio * m->mat[i][k];
			s->mat[j][k] -= ratio * s->mat[i][k];
			k++;
		}
		m->mat[j][i] = 0.0f;
		j++;
	}
}

// set diagonal to 1 to improve stability
void	reduce_diagonal_inv(t_mat4 *m, t_mat4 *s)
{
	int		i;
	int		j;
	float	div;

	i = 0;
	while (i < 4)
	{
		div = m->mat[i][i];
		j = 0;
		while (j < 4)
		{
			m->mat[i][j] = m->mat[i][j] / div;
			s->mat[i][j] = s->mat[i][j] / div;
			j++;
		}
		m->mat[i][i] = 1.0f;
		i++;
	}
}

// set above diagonal to 0 to improve stability
void	eliminate_above_inv(t_mat4 *m, t_mat4 *s)
{
	int		i;
	int		j;
	int		k;
	float	x;

	i = 0;
	while (i < 3)
	{
		j = i + 1;
		while (j < 4)
		{
			x = m->mat[i][j];
			k = 0;
			while (k < 4)
			{
				m->mat[i][k] -= m->mat[j][k] * x;
				s->mat[i][k] -= s->mat[j][k] * x;
				k++;
			}
			m->mat[i][j] = 0.0f;
			j++;
		}
		i++;
	}
}
