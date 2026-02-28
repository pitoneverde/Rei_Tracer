/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_determinant.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 23:55:30 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/28 17:47:01 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"
#include "utils/common.h"

static int fwd_elimination(t_mat4 *m, int *swap_count);
static void eliminate_below(t_mat4 *m, int i);

// just like the inverse, it's mainly LU decomposition in disguise
// once the matrix is reduced to upper-triangular form, the determinant is
// simply the product of the diagonal entries by definition.
// This approach is efficient, numerically stable and favors reusing of code
float	mat4_determinant(t_mat4 m)
{
	float	det;
	int		i;
	int		swap_count;

	swap_count = 0;
	if (fwd_elimination(&m, &swap_count) == -1)
		return (0.0f);
	i = 0;
	det = 1.0f;
	while (i < 4)
	{
		det *= m.mat[i][i];
		i++;
	}
	if (swap_count & 1)
		det = -det;
	return (det);
}

// 1 on error, 0 on success + swap_count is valid
static int fwd_elimination(t_mat4 *m, int *swap_count)
{
	int		i;
	int		j;
	int		pivot;

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
				j++;
			}
			(*swap_count)++;
		}
		eliminate_below(m, i);
		i++;
	}
	return (0);
}

// set under diagonal to 0 to improve stability
static void eliminate_below(t_mat4 *m, int i)
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
			k++;
		}
		m->mat[j][i] = 0.0f;
		j++;
	}
}
