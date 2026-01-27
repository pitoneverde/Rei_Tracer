/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_constants.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:57:42 by sabruma           #+#    #+#             */
/*   Updated: 2026/01/27 01:46:42 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/math_constants.h"

#define _GNU_SOURCE
#include <math.h>

const float MATH_PI = M_PIf;
const float MATH_PI_2 = M_PI_2f;
const float MATH_PI_4 = M_PI_4f;
const float MATH_TAU = 2.0f * M_PIf;
const float MATH_INV_PI = M_1_PIf;
const float MATH_INV_TAU = 0.5f * M_1_PIf;

const float MATH_E = M_Ef;
const float MATH_LOG2_E = M_LOG2Ef;
const float MATH_LOG10_E = M_LOG10Ef;
const float MATH_LN_2 = M_LN2f;
const float MATH_LN_10 = M_LN10f;

const float MATH_SQRT_2 = M_SQRT2f;
const float MATH_INV_SQRT_2 = M_SQRT1_2f;

// No float version in math.h, manually defined
const float MATH_SQRT_3 = 1.7320508075688772935274463415059f;
const float MATH_INV_SQRT_3 = 0.57735026918962576450914878050196f;
const float MATH_GOLDEN_RATIO = 1.6180339887498948482045868343656f;

const float MATH_EPSILON = 1e-6f;
const float MATH_EPSILON_SQ = 1e-4f;
const float MATH_EPSILON_SQRT = 1e-3f;
const float MATH_EPSILON_ANGLE = 1e-3f;
const float MATH_FLOAT_EPSILON = 1.1920928955078125e-07f;

const float DEG_TO_RAD = M_PIf / 180.0f;
const float RAD_TO_DEG = 180.0f / M_PIf;
