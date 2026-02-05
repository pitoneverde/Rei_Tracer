#ifndef VEC3_H
# define VEC3_H

#ifndef T_VEC3_DEFINED
# define T_VEC3_DEFINED

typedef struct s_vec3
{
	float x;
	float y;
	float z;
} t_vec3;

#endif

#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif

#include "core/constants.h"
#include <stdbool.h>

// ===== CORE CREATION & BASIC OPERATIONS =====

t_vec3	vec3_new(float x, float y, float z);
t_vec3	vec3_from_scalar(float s);

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_neg(t_vec3 v); // = -v
t_vec3	vec3_scale(t_vec3 v, float s);

float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
float	vec3_volume(t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3 vec3_triple(t_vec3 a, t_vec3 b, t_vec3 c);

// ===== COMPONENT-WISE OPERATIONS =====

t_vec3	vec3_mul_comp(t_vec3 a, t_vec3 b);
t_vec3	vec3_div_comp(t_vec3 a, t_vec3 b);
t_vec3	vec3_min_comp(t_vec3 a, t_vec3 b);
t_vec3	vec3_max_comp(t_vec3 a, t_vec3 b);

// ===== LENGTH & NORMALIZATION =====

float	vec3_length(t_vec3 v);
float	vec3_length_sq(t_vec3 v);

t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_normalize_or(t_vec3 v, t_vec3 fallback);
bool	vec3_is_normalized(t_vec3 v);

// ===== ANGLES & DIRECTIONS =====

float	vec3_angle(t_vec3 a, t_vec3 b);
float	vec3_signed_angle(t_vec3 a, t_vec3 b, t_vec3 axis);
bool	vec3_is_parallel(t_vec3 a, t_vec3 b, float epsilon);
bool	vec3_is_perpendicular(t_vec3 a, t_vec3 b, float epsilon);

// ===== COORDINATE SYSTEMS =====

void	vec3_coordinate_system(t_vec3 a, t_vec3 *b, t_vec3 *c); 
//t_vec3 vec3_orthonormal_basis(t_vec3 n, t_vec3* tangent, t_vec3* bitangent); // faster, use in hot path (cross-product)

// ===== PROJECTIONS =====

t_vec3	vec3_project(t_vec3 v, t_vec3 onto);
t_vec3	vec3_reject(t_vec3 v, t_vec3 onto);

// ===== POINT-SPECIFIC =====

float	vec3_distance(t_vec3 a, t_vec3 b);
float	vec3_distance_sq(t_vec3 a, t_vec3 b);
// t_vec3 vec3_midpoint(t_vec3 a, t_vec3 b);
// t_vec3 vec3_barycentric(t_vec3 a, t_vec3 b, t_vec3 c, float u, float v);

// ===== COMPARISONS =====
//use _comp variant to minmax 2 vectors

bool	vec3_equal(t_vec3 a, t_vec3 b, float epsilon);
bool	vec3_is_zero(t_vec3 v, float epsilon);
bool	vec3_is_finite(t_vec3 v);
bool	vec3_any_nan(t_vec3 v);

float	vec3_min(t_vec3 v);
float	vec3_max(t_vec3 v);

// ===== UTILS =====
t_vec3	vec3_abs(t_vec3 v);
t_vec3	vec3_floor(t_vec3 v);
t_vec3	vec3_ceil(t_vec3 v);
t_vec3	vec3_round(t_vec3 v);
t_vec3	vec3_mod(t_vec3 v, float divisor);


// t_vec3 vec3_fract(t_vec3 v);		//fractional part for shaders
// t_vec3 vec3_clamp(t_vec3 v, float min_val, float max_val);
// t_vec3 vec3_clamp_length(t_vec3 v, float max_length);
// rotations
// t_vec3 vec3_rotate_axis(t_vec3 v, t_vec3 axis, float angle);
// t_vec3 vec3_rotate_euler(t_vec3 v, float yaw, float pitch, float roll);

// colors
// t_vec3 vec3_from_color(float r, float g, float b);
// t_vec3 vec3_srgb_to_linear(t_vec3 srgb_color);
// t_vec3 vec3_linear_to_srgb(t_vec3 linear_color);
// t_vec3 vec3_saturate(t_vec3 color);           // Clamp to [0,1]
// t_vec3 vec3_gamma_correct(t_vec3 color, float gamma);
// float vec3_luminance(t_vec3 color);         // Grayscale conversion
// t_vec3 vec3_lerp_color(t_vec3 a, t_vec3 b, float t); // Better for colors?

// vector lerp/slerp (do last)
// random functions (sampling)
// swizzling (maybe?)

// ------------bonus------------
// reflection/refraction vectors

#endif