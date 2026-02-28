/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_inverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 01:25:01 by sabruma           #+#    #+#             */
/*   Updated: 2026/02/28 01:58:57 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/mat4.h"

// Gauss-Jordan method (numerically stable with partial pivoting)
t_mat4	mat4_inverse(t_mat4 m)
{
	t_mat4	s;
	
	s = mat4_identity();
	if (fwd_elimination(&m, &s))
		return mat4_identity();
	reduce_diagonal(&m, &s);
	eliminate_above(&m, &s);
	return (s);
}
