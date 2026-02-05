// 4x4 matrices to encode transformations in homogeneus coordinates
#ifndef MAT4_H
# define MAT4_H
#include "vec3.h"

#ifndef T_MAT4_DEFINED
# define T_MAT4_DEFINED

// should reformat for norminette but i don't fucking care now
typedef union u_mat4 {
	float	arr[16];
	float	mat[4][4];
	struct {
		float	m00, m01, m02, m03;
		float	m10, m11, m12, m13;
		float	m20, m21, m22, m23;
		float	m30, m31, m32, m33;
	};
}	t_mat4;

#endif

// ===== CORE CREATION & BASIC OPERATIONS =====
t_mat4	mat4_identity(void);
t_mat4	mat4_zero(void);
t_mat4	mat4_from_float_array(const float arr[16]);
t_mat4	mat4_from_basis(t_vec3 rx, t_vec3 up, t_vec3 fw, t_vec3 pos);

t_mat4	mat4_add(t_mat4 a, t_mat4 b);
t_mat4	mat4_sub(t_mat4 a, t_mat4 b);
t_mat4	mat4_mul(t_mat4 a, t_mat4 b);
t_mat4	mat4_scale(t_mat4 m, float scalar);
t_mat4	mat4_neg(t_mat4 m);

// ===== TRANSFORMATIONS (RT ESSENTIALS) =====

t_mat4	mat4_translation(t_vec3 translation);
t_mat4	mat4_scaling(t_vec3 scale);

t_mat4	mat4_rotation_x(float angle);
t_mat4	mat4_rotation_y(float angle);
t_mat4	mat4_rotation_z(float angle);
t_mat4	mat4_rotation_axis(t_vec3 axis, float angle);

t_mat4	mat4_look_at(t_vec3 eye, t_vec3 target, t_vec3 up);

// ===== MATRIX PROPERTIES & INVERSE/TRANSPOSE =====

float	mat4_determinant(t_mat4 m);
t_mat4	mat4_inverse(t_mat4 m);
t_mat4	mat4_transpose(t_mat4 m);
float	mat4_trace(t_mat4 m);

bool	mat4_is_affine(t_mat4 m);
bool	mat4_is_orthogonal(t_mat4 m, float epsilon);
bool	mat4_is_identity(t_mat4 m, float epsilon);

bool	mat4_equal(t_mat4 a, t_mat4 b, float epsilon);
bool	mat4_any_nan(t_mat4 m);
bool	mat4_is_finite(t_mat4 m);

// ===== VECTOR TRANSFORMATIONS =====

t_vec3	mat4_transform_point(t_mat4 m, t_vec3 point);
t_vec3	mat4_transform_vector(t_mat4 m, t_vec3 vector);
t_vec3	mat4_transform_normal(t_mat4 m, t_vec3 normal);

// ===== DECOMPOSITION =====

void	mat4_decompose(t_mat4 m, t_vec3 *translation, t_vec3 *rotation, t_vec3 *scale);
t_vec3	mat4_get_translation(t_mat4 m);
t_vec3	mat4_get_scale(t_mat4 m);

// ===== SPECIAL RT OPERATIONS =====

t_mat4	mat4_align_vectors(t_vec3 from, t_vec3 to);
t_mat4	mat4_billboard(t_vec3 position, t_vec3 camera_pos, t_vec3 camera_up);
t_mat4	mat4_lerp(t_mat4 a, t_mat4 b, float t);

// ===== UTILITY =====

void	mat4_to_float_array(t_mat4 m, float out[16]);

// ======= Projection Matrices ========
// t_mat4	mat4_orthographic(float left, float right, float bottom, 
// 						float top, float near, float far);
// t_mat4	mat4_perspective(float fov, float aspect, float near, float far);

#endif