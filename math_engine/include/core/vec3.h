#ifndef VEC3_H
# define VEC3_H

#include "minirt_types.h"
#include "core/constants.h"
#include <stdbool.h>

// create
t_vec3 vec3_new(float x, float y, float z);
t_vec3 vec3_from_scalar(float s);

// basic operations
// vector sum = vector
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_neg(t_vec3 v); // = -v
// vector scalar multiplication/division (scale)
t_vec3 vec3_mul(t_vec3 v, float s);
t_vec3 vec3_div(t_vec3 v, float s);

// vector dot product
float vec3_dot(t_vec3 a, t_vec3 b);
// vector cross product
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
// vector triple product (scalar)
float vec3_volume(t_vec3 a, t_vec3 b, t_vec3 c);	//triple product a.(b x c)
// vector triple product (vectorial)
// t_vec3 vec3_triple(t_vec3 a, t_vec3 b, t_vec3 c);

// component-wise operations
t_vec3 vec3_mul_comp(t_vec3 a, t_vec3 b);
t_vec3 vec3_div_comp(t_vec3 a, t_vec3 b);
t_vec3 vec3_min_comp(t_vec3 a, t_vec3 b);
t_vec3 vec3_max_comp(t_vec3 a, t_vec3 b);

// vector length and lenght_squared (avoid sqrt)
float vec3_length(t_vec3 v);
float vec3_length_sq(t_vec3 v);	// faster, no sqrt
// vector normalize
t_vec3 vec3_normalize(t_vec3 v);
t_vec3 vec3_normalize_or(t_vec3 v, t_vec3 fallback);	// for zero-length
bool vec3_is_normalized(t_vec3 v);

// projections and distance
t_vec3 vec3_project(t_vec3 v, t_vec3 onto);
t_vec3 vec3_reject(t_vec3 v, t_vec3 onto);
t_vec3 vec3_distance(t_vec3 a, t_vec3 b);
t_vec3 vec3_distance_sq(t_vec3 a, t_vec3 b);

// angles and direction
float vec3_angle(t_vec3 a, t_vec3 b);
float vec3_signed_angle(t_vec3 a, t_vec3 b, t_vec3 axis);
bool vec3_is_parallel(t_vec3 a, t_vec3 b, float epsilon);
bool vec3_is_perpendicular(t_vec3 a, t_vec3 b, float epsilon);

// coordinate systems
void vec3_coordinate_system(t_vec3 a, t_vec3 b, t_vec3 c);	// build orthonormal basis
//....

// comparisons
bool vec3_equal(t_vec3 a, t_vec3 b, float epsilon);
bool vec3_is_zero(t_vec3 v, float epsilon);
bool vec3_is_finite(t_vec3 v);
bool vec3_any_nan(t_vec3 v);

// utils
t_vec3 vec3_abs(t_vec3 v);
t_vec3 vec3_floor(t_vec3 v);
t_vec3 vec3_ceil(t_vec3 v);
t_vec3 vec3_round(t_vec3 v);
t_vec3 vec3_mod(t_vec3 v, float divisor);
float vec3_min(t_vec3 v);	//min coord
float vec3_max(t_vec3 v);	//max coord

//debug
t_vec3 vec3_print(t_vec3 v);


// point difference = vector
// point + vector = point
// point distance
// vector lerp/slerp (do last)

// ------------bonus------------
// reflection/refraction vectors

#endif