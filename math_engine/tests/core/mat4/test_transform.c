/*==============================================================================
# test_transform.c – Vector transformation tests
==============================================================================*/

#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "core/mat4.h"
#include "core/vec3.h"
#include "core/constants.h"
#include "utils/math_constants.h"
#include "core/test.h"

#ifndef EPSILON
# define EPSILON 1e-6f
#endif

/*------------------------------------------------------------------------------
  Unit tests
------------------------------------------------------------------------------*/

static void test_mat4_transform_point(void)
{
	t_vec3 p = {1.0f, 2.0f, 3.0f};

	// Identity
	t_mat4 I = mat4_identity();
	t_vec3 tp = mat4_transform_point(I, p);
	assert(vec3_equal_eps(tp, p, EPSILON));

	// Translation
	t_vec3 t = {4.0f, 5.0f, 6.0f};
	t_mat4 T = mat4_translation(t);
	tp = mat4_transform_point(T, p);
	t_vec3 expected = vec3_add(p, t);
	assert(vec3_equal_eps(tp, expected, EPSILON));

	// Rotation (90° about Z)
	t_mat4 R = mat4_rotation_z(math_pi()/2);
	tp = mat4_transform_point(R, p);
	expected = (t_vec3){-p.y, p.x, p.z}; // ( -2, 1, 3 )
	assert(vec3_equal_eps(tp, expected, EPSILON));

	// Scaling
	t_vec3 s = {2.0f, 3.0f, 4.0f};
	t_mat4 S = mat4_scaling(s);
	tp = mat4_transform_point(S, p);
	expected = vec3_mul_comp(p, s);
	assert(vec3_equal_eps(tp, expected, EPSILON));

	// Composition: rotate then translate
	t_mat4 M = mat4_mul(R, T); // first rotate, then translate
	tp = mat4_transform_point(M, p);
	t_vec3 rotated = {-p.y, p.x, p.z};
	expected = vec3_add(rotated, t);
	assert(vec3_equal_eps(tp, expected, EPSILON));

	// Zero point
	tp = mat4_transform_point(S, vec3_zero());
	assert(vec3_equal_eps(tp, vec3_zero(), EPSILON));

	// Large values
	t_vec3 huge = {1e20f, -1e20f, 1e20f};
	tp = mat4_transform_point(I, huge);
	assert(vec3_equal_eps(tp, huge, EPSILON));

	// NaN / Inf – just ensure no crash
	t_vec3 nan_vec = {NAN, 1, 2};
	tp = mat4_transform_point(I, nan_vec);
	(void)tp;
	t_vec3 inf_vec = {INFINITY, 1, 2};
	tp = mat4_transform_point(I, inf_vec);
	(void)tp;

	printf("✓ ");
}

static void test_mat4_transform_vector(void)
{
	t_vec3 v = {1.0f, 2.0f, 3.0f};

	// Identity
	t_mat4 I = mat4_identity();
	t_vec3 tv = mat4_transform_vector(I, v);
	assert(vec3_equal_eps(tv, v, EPSILON));

	// Translation (should have no effect)
	t_vec3 t = {4.0f, 5.0f, 6.0f};
	t_mat4 T = mat4_translation(t);
	tv = mat4_transform_vector(T, v);
	assert(vec3_equal_eps(tv, v, EPSILON));

	// Rotation (90° about Z)
	t_mat4 R = mat4_rotation_z(math_pi()/2);
	tv = mat4_transform_vector(R, v);
	t_vec3 expected = {-v.y, v.x, v.z}; // ( -2, 1, 3 )
	assert(vec3_equal_eps(tv, expected, EPSILON));

	// Scaling
	t_vec3 s = {2.0f, 3.0f, 4.0f};
	t_mat4 S = mat4_scaling(s);
	tv = mat4_transform_vector(S, v);
	expected = vec3_mul_comp(v, s);
	assert(vec3_equal_eps(tv, expected, EPSILON));

	// Composition: rotate then translate – translation still ignored
	t_mat4 M = mat4_mul(T, R);
	tv = mat4_transform_vector(M, v);
	expected = (t_vec3){-v.y, v.x, v.z}; // same as rotation only
	assert(vec3_equal_eps(tv, expected, EPSILON));

	// Zero vector
	tv = mat4_transform_vector(S, vec3_zero());
	assert(vec3_equal_eps(tv, vec3_zero(), EPSILON));

	// Large values
	t_vec3 huge = {1e20f, -1e20f, 1e20f};
	tv = mat4_transform_vector(I, huge);
	assert(vec3_equal_eps(tv, huge, EPSILON));

	printf("✓ ");
}

static void test_mat4_transform_normal(void)
{
	t_vec3 n = {1.0f, 0.0f, 0.0f}; // unit normal along X

	// Identity
	t_mat4 I = mat4_identity();
	t_vec3 tn = mat4_transform_normal(I, n);
	assert(vec3_equal_eps(tn, n, EPSILON));

	// Translation (should have no effect)
	t_vec3 t = {4.0f, 5.0f, 6.0f};
	t_mat4 T = mat4_translation(t);
	tn = mat4_transform_normal(T, n);
	assert(vec3_equal_eps(tn, n, EPSILON));

	// Rotation (90° about Z) – normal rotates like vector
	t_mat4 R = mat4_rotation_z(math_pi()/2);
	tn = mat4_transform_normal(R, n);
	t_vec3 expected = {0.0f, 1.0f, 0.0f}; // X -> Y
	assert(vec3_equal_eps(tn, expected, EPSILON));

	// Uniform scaling: scale factor 2 -> normal scales by 1/2
	t_vec3 s_uniform = {2.0f, 2.0f, 2.0f};
	t_mat4 Suni = mat4_scaling(s_uniform);
	tn = mat4_transform_normal(Suni, n);
	expected = (t_vec3){0.5f, 0.0f, 0.0f};
	assert(vec3_equal_eps(tn, expected, EPSILON));

	// Non-uniform scaling
	t_vec3 s_non = {2.0f, 3.0f, 4.0f};
	t_mat4 S = mat4_scaling(s_non);
	tn = mat4_transform_normal(S, n);
	expected = (t_vec3){1.0f/2.0f, 0.0f, 0.0f};
	assert(vec3_equal_eps(tn, expected, EPSILON));

	// Normal along Y
	n = (t_vec3){0.0f, 1.0f, 0.0f};
	tn = mat4_transform_normal(S, n);
	expected = (t_vec3){0.0f, 1.0f/3.0f, 0.0f};
	assert(vec3_equal_eps(tn, expected, EPSILON));

	// Normal along Z
	n = (t_vec3){0.0f, 0.0f, 1.0f};
	tn = mat4_transform_normal(S, n);
	expected = (t_vec3){0.0f, 0.0f, 1.0f/4.0f};
	assert(vec3_equal_eps(tn, expected, EPSILON));

	// Arbitrary normal and non-uniform scaling
	n = (t_vec3){1.0f, 1.0f, 1.0f}; vec3_normalize(n); // ~(0.577,0.577,0.577)
	tn = mat4_transform_normal(S, n);
	// Expected: multiply by inverse-transpose of scaling = diag(1/2, 1/3, 1/4)
	expected = (t_vec3){n.x/2.0f, n.y/3.0f, n.z/4.0f};
	assert(vec3_equal_eps(tn, expected, EPSILON));

	// Test orthogonality with a tangent after transformation
	// For a surface with normal n and tangent t, after applying matrix M (with possibly non-uniform scale),
	// the transformed normal should be perpendicular to transformed tangent.
	// We'll use a simple shear matrix.
	t_mat4 shear = { .arr = {
		1, 1, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	}};
	n = (t_vec3){0.0f, 1.0f, 0.0f}; // normal originally vertical
	t_vec3 tangent = (t_vec3){1.0f, 0.0f, 0.0f}; // originally horizontal
	tn = mat4_transform_normal(shear, n);
	t_vec3 tt = mat4_transform_vector(shear, tangent);
	float dot = vec3_dot(tn, tt);
	assert(float_equal(dot, 0.0f, EPSILON));

	// Zero normal
	tn = mat4_transform_normal(S, vec3_zero());
	assert(vec3_equal_eps(tn, vec3_zero(), EPSILON));

	// Large values
	t_vec3 huge = {1e20f, 0.0f, 0.0f};
	tn = mat4_transform_normal(I, huge);
	assert(vec3_equal_eps(tn, huge, EPSILON));

	// NaN / Inf – just ensure no crash
	t_vec3 nan_vec = {NAN, 1, 2};
	tn = mat4_transform_normal(I, nan_vec);
	(void)tn;
	t_vec3 inf_vec = {INFINITY, 1, 2};
	tn = mat4_transform_normal(I, inf_vec);
	(void)tn;

	printf("✓ ");
}

/*------------------------------------------------------------------------------
  Edge case tests combining multiple functions
------------------------------------------------------------------------------*/

static void test_mat4_transform_edge_cases(void)
{
	// Matrices with NaN, Inf – ensure functions don't crash
	t_mat4 nan_mat = { .arr = {NAN, NAN, NAN, NAN,
								NAN, NAN, NAN, NAN,
								NAN, NAN, NAN, NAN,
								NAN, NAN, NAN, NAN} };
	t_mat4 inf_mat = { .arr = {INFINITY, INFINITY, INFINITY, INFINITY,
								INFINITY, INFINITY, INFINITY, INFINITY,
								INFINITY, INFINITY, INFINITY, INFINITY,
								INFINITY, INFINITY, INFINITY, INFINITY} };

	t_vec3 p = {1,2,3};
	t_vec3 v = {4,5,6};
	t_vec3 n = {0,1,0};

	t_vec3 res;

	res = mat4_transform_point(nan_mat, p);
	(void)res;
	res = mat4_transform_vector(nan_mat, v);
	(void)res;
	res = mat4_transform_normal(nan_mat, n);
	(void)res;

	res = mat4_transform_point(inf_mat, p);
	(void)res;
	res = mat4_transform_vector(inf_mat, v);
	(void)res;
	res = mat4_transform_normal(inf_mat, n);
	(void)res;

	// Very small/large vectors with near-singular matrices
	t_mat4 tiny_scale = mat4_scaling((t_vec3){1e-30f, 1e-30f, 1e-30f});
	t_vec3 huge_vec = {1e30f, 1e30f, 1e30f};
	res = mat4_transform_point(tiny_scale, huge_vec); // should be ~ (1,1,1) because 1e-30 * 1e30 = 1
	t_vec3 expected = (t_vec3){1.0f, 1.0f, 1.0f};
	assert(vec3_equal_eps(res, expected, 1e-6f));

	// Zero matrix
	t_mat4 Z = mat4_zero();
	res = mat4_transform_point(Z, p);
	assert(vec3_equal_eps(res, vec3_zero(), EPSILON));
	res = mat4_transform_vector(Z, v);
	assert(vec3_equal_eps(res, vec3_zero(), EPSILON));
	// meaningless, can't apply a singular matrix to a normal
	// res = mat4_transform_normal(Z, n);
	// assert(vec3_equal_eps(res, vec3_zero(), EPSILON));

	printf("✓ ");
}

/*------------------------------------------------------------------------------
  Benchmark (optional)
------------------------------------------------------------------------------*/

#ifdef BENCHMARK

#include <time.h>

static void bench_mat4_transform_point(void)
{
	t_mat4 M = random_mat4(-10, 10);
	t_vec3 p = {1,2,3};
	t_vec3 r;

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < TEST_ITERATIONS; ++i)
		r = mat4_transform_point(M, p);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("mat4_transform_point: %d ops in %.3f s -> %.1f Mops/s\n",
		   TEST_ITERATIONS, sec, TEST_ITERATIONS / sec / 1e6);
	(void)r;
}

static void bench_mat4_transform_vector(void)
{
	t_mat4 M = random_mat4(-10, 10);
	t_vec3 v = {4,5,6};
	t_vec3 r;

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < TEST_ITERATIONS; ++i)
		r = mat4_transform_vector(M, v);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("mat4_transform_vector: %d ops in %.3f s -> %.1f Mops/s\n",
		   TEST_ITERATIONS, sec, TEST_ITERATIONS / sec / 1e6);
	(void)r;
}

static void bench_mat4_transform_normal(void)
{
	t_mat4 M = random_mat4(-10, 10);
	t_vec3 n = {0,1,0};
	t_vec3 r;

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < TEST_ITERATIONS; ++i)
		r = mat4_transform_normal(M, n);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("mat4_transform_normal: %d ops in %.3f s -> %.1f Mops/s\n",
		   TEST_ITERATIONS, sec, TEST_ITERATIONS / sec / 1e6);
	(void)r;
}

static void bench_mat4_transform_normal2(void)
{
	t_mat4 M = random_mat4(-10, 10);
	t_vec3 n = {0,1,0};
	t_vec3 r;

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < TEST_ITERATIONS; ++i)
		r = mat4_transform_normal2(M, n);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("mat4_transform_normal2: %d ops in %.3f s -> %.1f Mops/s\n",
		   TEST_ITERATIONS, sec, TEST_ITERATIONS / sec / 1e6);
	(void)r;
}

static void run_benchmarks(void)
{
	printf("\n=== Running benchmarks (vector transformations) ===\n");
	bench_mat4_transform_point();
	bench_mat4_transform_vector();
	bench_mat4_transform_normal();
	bench_mat4_transform_normal2();
}

#endif /* BENCHMARK */

/*------------------------------------------------------------------------------
  Main – dispatch tests or benchmarks
------------------------------------------------------------------------------*/

void test_mat4_transform()
{
	srand(42);

#ifdef BENCHMARK
	run_benchmarks();
#else
	test_mat4_transform_point();
	test_mat4_transform_vector();
	test_mat4_transform_normal();
	test_mat4_transform_edge_cases();
	printf("\n");
#endif
}