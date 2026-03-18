/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_inverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 01:25:01 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 18:35:32 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"

// Gauss-Jordan method (numerically stable with partial pivoting)
// the identity is just a fallback, NOT the inverse of a singular matrix
t_mat4	mat4_inverse(t_mat4 m)
{
	t_mat4	s;

	s = mat4_identity();
	if (fwd_elimination_inv(&m, &s))
		return (mat4_identity());
	reduce_diagonal_inv(&m, &s);
	eliminate_above_inv(&m, &s);
	return (s);
}
