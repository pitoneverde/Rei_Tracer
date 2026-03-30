/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_constants_sqrt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:41:51 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/30 21:53:22 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/math_constants.h"

inline float	math_sqrt_2(void)
{
	return (M_SQRT2f32);
}

inline float	math_inv_sqrt_2(void)
{
	return (M_SQRT1_2f32);
}

inline float	math_sqrt_3(void)
{
	return (1.7320508075688772935274463415059f);
}

inline float	math_inv_sqrt_3(void)
{
	return (0.57735026918962576450914878050196f);
}

inline float	math_golden_ratio(void)
{
	return (1.6180339887498948482045868343656f);
}
