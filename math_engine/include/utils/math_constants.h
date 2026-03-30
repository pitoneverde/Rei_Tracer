/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_constants.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:23:36 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/30 21:47:57 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_CONSTANTS_H
# define MATH_CONSTANTS_H

# define _GNU_SOURCE
# include <math.h>

// extern const float MATH_PI;			// pi
// extern const float MATH_PI_2;		// pi/2
// extern const float MATH_PI_4;		// pi/4
// extern const float MATH_TAU;		// 2*pi
// extern const float MATH_INV_PI;		// 1/pi
// extern const float MATH_INV_TAU;	// 1/2*pi

float	math_pi(void);
float	math_pi_2(void);
float	math_pi_4(void);
float	math_tau(void);
float	math_inv_pi(void);
float	math_inv_tau(void);

// extern const float MATH_E;				// e
// extern const float MATH_LOG2_E;			// log2(e)
// extern const float MATH_LOG10_E;		// log10(e)
// extern const float MATH_LN_2;			// ln(2)
// extern const float MATH_LN_10;			// ln(10)

// extern const float MATH_SQRT_2;			// sqrt(2)
// extern const float MATH_INV_SQRT_2;		// 1/sqrt(2)
// extern const float MATH_SQRT_3;			// sqrt(3)
// extern const float MATH_INV_SQRT_3;		// 1/sqrt(3)
// extern const float MATH_GOLDEN_RATIO;	// phi

float	math_sqrt_2(void);
float	math_inv_sqrt_2(void);
float	math_sqrt_3(void);
float	math_inv_sqrt_3(void);
float	math_golden_ratio(void);

// extern const float MATH_EPSILON;		// 1e-6
// extern const float MATH_EPSILON_SQ;		// epsilon^2
// extern const float MATH_EPSILON_SQRT;	// sqrt(epsilon)
// extern const float MATH_EPSILON_ANGLE;	// 1e-4
// extern const float MATH_FLOAT_EPSILON;	// 2^-23, float32 machine epsilon

float	math_epsilon(void);
float	math_epsilon_sq(void);
float	math_epsilon_sqrt(void);
float	math_epsilon_angle(void);
float	math_epsilon_float(void);

// Angle convertion coefficients
// extern const float DEG_TO_RAD;		// pi/180
// extern const float RAD_TO_DEG;		// 180/pi

float	deg_to_rad(float deg);
float	rad_to_deg(float rad);

// ... short aliases if needed

#endif