/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_constants_tau.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:32:49 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/30 21:53:06 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/math_constants.h"

float	math_tau(void)
{
	return (2.0f * M_PIf32);
}

float	math_inv_tau(void)
{
	return (0.5f * M_1_PIf32);
}
