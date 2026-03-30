/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_constants_pi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:27:28 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/30 21:54:04 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/math_constants.h"

inline float	math_pi(void)
{
	return (M_PIf32);
}

inline float	math_pi_2(void)
{
	return (M_PI_2f32);
}

inline float	math_pi_4(void)
{
	return (M_PI_4f32);
}

inline float	math_inv_pi(void)
{
	return (M_1_PIf32);
}
