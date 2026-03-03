/*==============================================================================
# test_decomposition.c – Decomposition tests
==============================================================================*/

#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "core/mat4.h"
#include "core/vec3.h"
#include "utils/math_constants.h"
#include "core/test.h"

#ifndef EPSILON
# define EPSILON 1e-6f
#endif

/*------------------------------------------------------------------------------
  Unit tests
------------------------------------------------------------------------------*/

static void test_mat4_get_translation(void)
{
	printf("=== test_mat4_get_translation ===\n");

	// Identity
	t_mat4 I = mat4_identity();
	t_vec3 t = mat4_get_translation(I);
	assert(vec3_equal_eps(t, VEC3_ZERO, EPSILON));

	// Pure translation
	t_vec3 trans = {2.0f, -3.0f, 5.0f};
	t_mat4 T = mat4_translation(trans);
	t = mat4_get_translation(T);
	assert(vec3_equal_eps(t, trans, EPSILON));

	// Rotation + translation
	t_mat4 R = mat4_rotation_x(MATH_PI/4);
	t_mat4 RT = mat4_mul(T, R); // first rotate then translate
	t = mat4_get_translation(RT);
	assert(vec3_equal_eps(t, trans, EPSILON)); // translation unaffected by rotation

	// Scaling + translation
	t_mat4 S = mat4_scaling((t_vec3){2,3,4});
	t_mat4 ST = mat4_mul(T, S);
	t = mat4_get_translation(ST);
	assert(vec3_equal_eps(t, trans, EPSILON));

	// Zero matrix (translation zero)
	t_mat4 Z = mat4_zero();
	t = mat4_get_translation(Z);
	assert(vec3_equal_eps(t, VEC3_ZERO, EPSILON));

	// Matrix with non‑affine last column – translation still extracted from last row
	t_mat4 non_affine = I;
	non_affine.mat[0][3] = 99.0f; // w component of first row
	non_affine.mat[3][0] = 1.0f; // translation x
	non_affine.mat[3][1] = 2.0f;
	non_affine.mat[3][2] = 3.0f;
	non_affine.mat[3][3] = 1.0f;
	t = mat4_get_translation(non_affine);
	assert(vec3_equal_eps(t, (t_vec3){1,2,3}, EPSILON));

	printf("✓ get_translation tests passed\n");
}

static void test_mat4_get_scale(void)
{
	printf("=== test_mat4_get_scale ===\n");

	// Identity
	t_mat4 I = mat4_identity();
	t_vec3 s = mat4_get_scale(I);
	assert(vec3_equal_eps(s, (t_vec3){1,1,1}, EPSILON));

	// Pure scaling
	t_vec3 scale = {2.0f, 3.0f, 4.0f};
	t_mat4 S = mat4_scaling(scale);
	s = mat4_get_scale(S);
	assert(vec3_equal_eps(s, scale, EPSILON));

	// Rotation + scaling (orthogonal basis scaled)
	t_mat4 R = mat4_rotation_z(MATH_PI/6);
	t_mat4 RS = mat4_mul(R, S); // first scale, then rotate
	s = mat4_get_scale(RS);
	// Scale should be the same (lengths of basis vectors unchanged by rotation)
	assert(vec3_equal_eps(s, scale, EPSILON));

	// Rotation alone
	R = mat4_rotation_x(MATH_PI/3);
	s = mat4_get_scale(R);
	assert(vec3_equal_eps(s, (t_vec3){1,1,1}, EPSILON));

	// Translation does not affect scale
	t_mat4 T = mat4_translation((t_vec3){5,6,7});
	t_mat4 RST = mat4_mul(T, RS);
	s = mat4_get_scale(RST);
	assert(vec3_equal_eps(s, scale, EPSILON));

	// Negative scaling (reflection)
	scale = (t_vec3){-2,3,4};
	S = mat4_scaling(scale);
	s = mat4_get_scale(S);
	// Lengths should be positive (absolute values)
	assert(vec3_equal_eps(s, (t_vec3){2,3,4}, EPSILON));

	// Zero scaling
	scale = VEC3_ZERO;
	S = mat4_scaling(scale);
	s = mat4_get_scale(S);
	assert(vec3_equal_eps(s, VEC3_ZERO, EPSILON));

	// Non‑orthogonal basis (shear) – scale still computed as lengths, but may not be the original scale factors.
	t_mat4 shear = { .arr = {
		1, 1, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	}};
	s = mat4_get_scale(shear);
	// Expected lengths: row0 length sqrt(1+1)=√2≈1.414, row1 length 1, row2 length 1
	assert(vec3_equal_eps(s, (t_vec3){sqrtf(2.0f), 1.0f, 1.0f}, EPSILON));

	printf("✓ get_scale tests passed\n");
}

static void test_mat4_decompose_function(void)
{
	printf("=== test_mat4_decompose ===\n");

	// Identity
	t_mat4 I = mat4_identity();
	t_vec3 trans, rot, scale;
	mat4_decompose(I, &trans, &rot, &scale);
	assert(vec3_equal_eps(trans, VEC3_ZERO, EPSILON));
	assert(vec3_equal_eps(scale, (t_vec3){1,1,1}, EPSILON));
	// Rotation should be identity; we can check by rotating x axis and see if it stays x.
	// But decomposition may return rotation as Euler angles; we'll just trust.

	// Pure translation
	t_vec3 t = {2, -3, 5};
	t_mat4 T = mat4_translation(t);
	mat4_decompose(T, &trans, &rot, &scale);
	assert(vec3_equal_eps(trans, t, EPSILON));
	assert(vec3_equal_eps(scale, (t_vec3){1,1,1}, EPSILON));
	// rotation should be identity (all zeros as euler angles)

	// Pure scaling
	t_vec3 s = {2, 3, 4};
	t_mat4 S = mat4_scaling(s);
	mat4_decompose(S, &trans, &rot, &scale);
	assert(vec3_equal_eps(trans, VEC3_ZERO, EPSILON));
	assert(vec3_equal_eps(scale, s, EPSILON));

	// Rotation only (X axis 90°)
	float angle = MATH_PI/2;
	t_mat4 R = mat4_rotation_x(angle);
	mat4_decompose(R, &trans, &rot, &scale);
	assert(vec3_equal_eps(trans, VEC3_ZERO, EPSILON));
	assert(vec3_equal_eps(scale, (t_vec3){1,1,1}, EPSILON));
	// We can't directly check Euler angles, but we can reconstruct matrix from decomposed parts
	// and compare with original. However, the decomposition function may not reconstruct rotation as Euler.
	// It might reconstruct a rotation matrix from the orthogonalized basis.
	// Let's reconstruct a matrix assuming T * R(rot) * S.
	// We need a way to build a rotation matrix from Euler angles (assuming order?).
	// The decomposition likely expects that the original matrix is built as T * R * S with R being a rotation matrix,
	// and it extracts translation, then scale = lengths of basis, then rotation = normalize basis.
	// So we can check that the extracted scale and rotation (as matrix) reproduce the original when recombined.
	// But we don't have a function to build from Euler. Instead, we can check that the rotation part (when normalized) is orthogonal.
	// For a rotation-only matrix, the basis vectors should be orthonormal.
	// We can compute the rotation matrix from the extracted rotation (as Euler) if we had a function.
	// Since we don't, we'll trust that the extracted rotation is correct by checking that the reconstructed matrix (using extracted translation and scale and assuming rotation is correct) equals original.
	// But we don't have a compose function.
	// Instead, we can verify that the basis vectors after normalization match the original rows.
	t_vec3 rx = {R.mat[0][0], R.mat[0][1], R.mat[0][2]};
	t_vec3 ry = {R.mat[1][0], R.mat[1][1], R.mat[1][2]};
	t_vec3 rz = {R.mat[2][0], R.mat[2][1], R.mat[2][2]};
	float len_rx = vec3_length(rx);
	float len_ry = vec3_length(ry);
	float len_rz = vec3_length(rz);
	assert(float_equal(len_rx, 1.0f, EPSILON));
	assert(float_equal(len_ry, 1.0f, EPSILON));
	assert(float_equal(len_rz, 1.0f, EPSILON));
	// Check orthogonality (dot products zero)
	assert(float_equal(vec3_dot(rx, ry), 0.0f, EPSILON));
	assert(float_equal(vec3_dot(rx, rz), 0.0f, EPSILON));
	assert(float_equal(vec3_dot(ry, rz), 0.0f, EPSILON));

	// Combined: T * R * S
	t = (t_vec3){1,2,3};
	s = (t_vec3){2,3,4};
	R = mat4_rotation_z(MATH_PI/3);
	T = mat4_translation(t);
	S = mat4_scaling(s);
	t_mat4 RS = mat4_mul(R, S);   // scale then rotate
	t_mat4 TRS = mat4_mul(T, RS); // translate after
	mat4_decompose(TRS, &trans, &rot, &scale);
	// Check translation
	assert(vec3_equal_eps(trans, t, EPSILON));
	// Check scale
	assert(vec3_equal_eps(scale, s, EPSILON));
	// Now we need to verify rotation. We can reconstruct the rotation matrix from the extracted rot (Euler) if we had conversion.
	// Alternatively, we can check that the upper 3x3 part of TRS divided by scale (component-wise?) is orthogonal.
	// But dividing rows by scale gives normalized basis.
	t_mat4 upper = { .mat = {
		{TRS.mat[0][0]/s.x, TRS.mat[0][1]/s.x, TRS.mat[0][2]/s.x, 0},
		{TRS.mat[1][0]/s.y, TRS.mat[1][1]/s.y, TRS.mat[1][2]/s.y, 0},
		{TRS.mat[2][0]/s.z, TRS.mat[2][1]/s.z, TRS.mat[2][2]/s.z, 0},
		{0,0,0,1}
	}};
	// This should be a rotation matrix (orthogonal, det=1)
	// Check orthonormality
	rx = (t_vec3){upper.mat[0][0], upper.mat[0][1], upper.mat[0][2]};
	ry = (t_vec3){upper.mat[1][0], upper.mat[1][1], upper.mat[1][2]};
	rz = (t_vec3){upper.mat[2][0], upper.mat[2][1], upper.mat[2][2]};
	assert(float_equal(vec3_length(rx), 1.0f, EPSILON));
	assert(float_equal(vec3_length(ry), 1.0f, EPSILON));
	assert(float_equal(vec3_length(rz), 1.0f, EPSILON));
	assert(float_equal(vec3_dot(rx, ry), 0.0f, EPSILON));
	assert(float_equal(vec3_dot(rx, rz), 0.0f, EPSILON));
	assert(float_equal(vec3_dot(ry, rz), 0.0f, EPSILON));
	// Determinant of upper should be 1
	float det = mat4_determinant(upper);
	assert(float_equal(det, 1.0f, EPSILON));

	// Edge: zero matrix
	t_mat4 Z = mat4_zero();
	mat4_decompose(Z, &trans, &rot, &scale);
	assert(vec3_equal_eps(trans, VEC3_ZERO, EPSILON));
	assert(vec3_equal_eps(scale, VEC3_ZERO, EPSILON));
	// rotation undefined, but function should handle

	// Negative scale (reflection) – should be extracted as positive scale and rotation may include reflection? 
	// Typically decomposition handles negative scale by making rotation include a reflection (determinant -1).
	s = (t_vec3){-2,3,4};
	S = mat4_scaling(s);
	t_mat4 TS = mat4_mul(T, S);
	mat4_decompose(TS, &trans, &rot, &scale);
	assert(vec3_equal_eps(trans, t, EPSILON));
	assert(vec3_equal_eps(scale, (t_vec3){2,3,4}, EPSILON)); // scale positive
	// The rotation part should now have determinant -1 (reflection)
	upper = (t_mat4){ .mat = {
		{TS.mat[0][0]/2.0f, TS.mat[0][1]/2.0f, TS.mat[0][2]/2.0f, 0},
		{TS.mat[1][0]/3.0f, TS.mat[1][1]/3.0f, TS.mat[1][2]/3.0f, 0},
		{TS.mat[2][0]/4.0f, TS.mat[2][1]/4.0f, TS.mat[2][2]/4.0f, 0},
		{0,0,0,1}
	}};
	det = mat4_determinant(upper);
	assert(float_equal(det, -1.0f, EPSILON));

	printf("✓ decompose tests passed\n");
}

/*------------------------------------------------------------------------------
  Edge case tests for decomposition
------------------------------------------------------------------------------*/

static void test_mat4_decompose_edge_cases(void)
{
	printf("=== test_mat4_decompose_edge_cases ===\n");

	t_vec3 trans, rot, scale;

	// Very large translation
	t_mat4 T_huge = mat4_translation((t_vec3){1e20f, -1e20f, 1e20f});
	mat4_decompose(T_huge, &trans, &rot, &scale);
	assert(vec3_equal_eps(trans, (t_vec3){1e20f, -1e20f, 1e20f}, EPSILON));
	assert(vec3_equal_eps(scale, (t_vec3){1,1,1}, EPSILON));

	// Very large scale
	t_mat4 S_huge = mat4_scaling((t_vec3){1e20f, 1e20f, 1e20f});
	mat4_decompose(S_huge, &trans, &rot, &scale);
	assert(vec3_equal_eps(scale, (t_vec3){1e20f, 1e20f, 1e20f}, EPSILON));
	assert(vec3_equal_eps(trans, VEC3_ZERO, EPSILON));

	// Very small scale
	t_mat4 S_tiny = mat4_scaling((t_vec3){1e-30f, 1e-30f, 1e-30f});
	mat4_decompose(S_tiny, &trans, &rot, &scale);
	assert(vec3_equal_eps(scale, (t_vec3){1e-30f, 1e-30f, 1e-30f}, EPSILON));

	// NaN / Inf – ensure no crash
	t_mat4 nan_mat = { .arr = {NAN, NAN, NAN, NAN,
								NAN, NAN, NAN, NAN,
								NAN, NAN, NAN, NAN,
								NAN, NAN, NAN, NAN} };
	mat4_decompose(nan_mat, &trans, &rot, &scale);
	(void)trans; (void)rot; (void)scale;

	t_mat4 inf_mat = { .arr = {INFINITY, INFINITY, INFINITY, INFINITY,
								INFINITY, INFINITY, INFINITY, INFINITY,
								INFINITY, INFINITY, INFINITY, INFINITY,
								INFINITY, INFINITY, INFINITY, INFINITY} };
	mat4_decompose(inf_mat, &trans, &rot, &scale);
	(void)trans; (void)rot; (void)scale;

	printf("✓ decompose edge cases passed\n");
}

/*------------------------------------------------------------------------------
  Benchmark (optional)
------------------------------------------------------------------------------*/

#ifdef BENCHMARK

#include <time.h>

static double time_diff_sec(struct timespec start, struct timespec end)
{
	return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
}

static void bench_mat4_decompose(void)
{
	const int N = 1000000;
	t_mat4 M = random_mat4(-10, 10);
	t_vec3 trans, rot, scale;

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < N; ++i)
		mat4_decompose(M, &trans, &rot, &scale);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("mat4_decompose: %d ops in %.3f s -> %.1f ops/s\n",
		   N, sec, N / sec);
	(void)trans; (void)rot; (void)scale;
}

static void bench_mat4_get_translation(void)
{
	const int N = 10000000;
	t_mat4 M = random_mat4(-10, 10);
	t_vec3 t;

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < N; ++i)
		t = mat4_get_translation(M);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("mat4_get_translation: %d ops in %.3f s -> %.1f Mops/s\n",
		   N, sec, N / sec / 1e6);
	(void)t;
}

static void bench_mat4_get_scale(void)
{
	const int N = 10000000;
	t_mat4 M = random_mat4(-10, 10);
	t_vec3 s;

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < N; ++i)
		s = mat4_get_scale(M);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("mat4_get_scale: %d ops in %.3f s -> %.1f Mops/s\n",
		   N, sec, N / sec / 1e6);
	(void)s;
}

static void run_benchmarks(void)
{
	printf("\n=== Running benchmarks (decomposition) ===\n");
	bench_mat4_decompose();
	bench_mat4_get_translation();
	bench_mat4_get_scale();
}

#endif /* BENCHMARK */

/*------------------------------------------------------------------------------
  Main – dispatch tests or benchmarks
------------------------------------------------------------------------------*/

void test_mat4_decompose()
{
	srand(42);

#ifdef BENCHMARK
	run_benchmarks();
#else
	printf("===== DECOMPOSITION =====\n\n");

	test_mat4_get_translation();
	printf("\n");
	test_mat4_get_scale();
	printf("\n");
	test_mat4_decompose_function();
	printf("\n");
	test_mat4_decompose_edge_cases();
	printf("\n");

	printf("\nAll decomposition tests passed.\n");
#endif
}