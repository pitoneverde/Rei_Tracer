/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_constants_eps.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:20:31 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/30 20:27:20 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/math_constants.h"

// const float MATH_EPSILON = 1e-6f;
// const float MATH_EPSILON_SQ = 1e-4f;
// const float MATH_EPSILON_SQRT = 1e-3f;
// const float MATH_EPSILON_ANGLE = 1e-3f;
// const float MATH_FLOAT_EPSILON = 1.1920928955078125e-07f;

inline float	math_epsilon()
{
	return (1e-6f);
}

inline float	math_epsilon_sq()
{
	return (1e-4f);
}

inline float	math_epsilon_sqrt()
{
	return (1e-3f);
}

inline float	math_epsilon_angle()
{
	return (1e-3f);
}

inline float	math_epsilon_float()
{
	return (1.1920928955078125e-07f);
}
