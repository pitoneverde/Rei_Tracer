/*==============================================================================
# test_basic.c – Core matrix operations tests
==============================================================================*/

#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "core/mat4.h"
#include "core/vec3.h"          // mat4 uses t_vec3
#include "core/test.h"

#ifndef EPSILON
# define EPSILON 1e-6f
#endif

/*------------------------------------------------------------------------------
  Unit tests
------------------------------------------------------------------------------*/

static void test_mat4_identity(void)
{
	t_mat4 I = mat4_identity();

	// Check diagonal = 1, off-diagonal = 0
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			assert(float_equal(I.mat[i][j], (i == j) ? 1.0f : 0.0f, EPSILON));

	// Multiply any matrix by identity yields itself
	t_mat4 A = random_mat4(-10.0f, 10.0f);
	t_mat4 AI = mat4_mul(A, I);
	t_mat4 IA = mat4_mul(I, A);

	assert(mat4_equal_eps(A, AI, EPSILON));
	assert(mat4_equal_eps(A, IA, EPSILON));

	printf("✓ ");
}

static void test_mat4_zero(void)
{
	t_mat4 Z = mat4_zero();
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			assert(float_equal(Z.mat[i][j], 0.0f, EPSILON));

	printf("✓ ");
}

static void test_mat4_from_float_array(void)
{
	float arr[16] = {
		 1.0f,  2.0f,  3.0f,  4.0f,
		 5.0f,  6.0f,  7.0f,  8.0f,
		 9.0f, 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f
	};
	t_mat4 M = mat4_from_float_array(arr);

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			assert(float_equal(M.mat[i][j], arr[i*4 + j], EPSILON));

	// Edge: array with infinities / NaNs (just ensure it doesn't crash)
	float nan_arr[16];
	for (int k = 0; k < 16; ++k) nan_arr[k] = NAN;
	t_mat4 N = mat4_from_float_array(nan_arr);
	(void)N; // silence unused warning

	printf("✓ ");
}

static void test_mat4_from_basis(void)
{
	t_vec3 rx = {1.0f, 0.0f, 0.0f};
	t_vec3 up = {0.0f, 1.0f, 0.0f};
	t_vec3 fw = {0.0f, 0.0f, 1.0f};
	t_vec3 ps = {2.0f, 3.0f, 4.0f};

	t_mat4 M = mat4_from_basis(rx, up, fw, ps);

	// Check rows: row0 = (rx, 0), row1 = (up, 0), row2 = (fw, 0), row3 = (ps, 1)
	assert(float_equal(M.mat[0][0], rx.x, EPSILON) && float_equal(M.mat[0][1], rx.y, EPSILON) && float_equal(M.mat[0][2], rx.z, EPSILON) && float_equal(M.mat[0][3], 0.0f, EPSILON));
	assert(float_equal(M.mat[1][0], up.x, EPSILON) && float_equal(M.mat[1][1], up.y, EPSILON) && float_equal(M.mat[1][2], up.z, EPSILON) && float_equal(M.mat[1][3], 0.0f, EPSILON));
	assert(float_equal(M.mat[2][0], fw.x, EPSILON) && float_equal(M.mat[2][1], fw.y, EPSILON) && float_equal(M.mat[2][2], fw.z, EPSILON) && float_equal(M.mat[2][3], 0.0f, EPSILON));
	assert(float_equal(M.mat[3][0], ps.x, EPSILON) && float_equal(M.mat[3][1], ps.y, EPSILON) && float_equal(M.mat[3][2], ps.z, EPSILON) && float_equal(M.mat[3][3], 1.0f, EPSILON));

	// Non‑orthogonal basis (still works)
	rx = (t_vec3){2.0f, 0.0f, 0.0f};
	up = (t_vec3){1.0f, 1.0f, 0.0f};
	fw = (t_vec3){0.0f, 1.0f, 2.0f};
	ps = (t_vec3){-1.0f, -2.0f, -3.0f};
	M = mat4_from_basis(rx, up, fw, ps);

	assert(float_equal(M.mat[0][0], rx.x, EPSILON) && float_equal(M.mat[0][1], rx.y, EPSILON) && float_equal(M.mat[0][2], rx.z, EPSILON) && float_equal(M.mat[0][3], 0.0f, EPSILON));
	assert(float_equal(M.mat[1][0], up.x, EPSILON) && float_equal(M.mat[1][1], up.y, EPSILON) && float_equal(M.mat[1][2], up.z, EPSILON) && float_equal(M.mat[1][3], 0.0f, EPSILON));
	assert(float_equal(M.mat[2][0], fw.x, EPSILON) && float_equal(M.mat[2][1], fw.y, EPSILON) && float_equal(M.mat[2][2], fw.z, EPSILON) && float_equal(M.mat[2][3], 0.0f, EPSILON));
	assert(float_equal(M.mat[3][0], ps.x, EPSILON) && float_equal(M.mat[3][1], ps.y, EPSILON) && float_equal(M.mat[3][2], ps.z, EPSILON) && float_equal(M.mat[3][3], 1.0f, EPSILON));

	printf("✓ ");
}

static void test_mat4_add(void)
{
	t_mat4 A = random_mat4(-5.0f, 5.0f);
	t_mat4 B = random_mat4(-5.0f, 5.0f);
	t_mat4 Z = mat4_zero();

	// Addition with zero
	t_mat4 AplusZ = mat4_add(A, Z);
	assert(mat4_equal_eps(A, AplusZ, EPSILON));

	// Commutativity
	t_mat4 AplusB = mat4_add(A, B);
	t_mat4 BplusA = mat4_add(B, A);
	assert(mat4_equal_eps(AplusB, BplusA, EPSILON));

	// Element‑wise check
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			assert(float_equal(AplusB.mat[i][j], A.mat[i][j] + B.mat[i][j], EPSILON));

	// Edge: large numbers, infinities, NaNs
	t_mat4 Large = { .arr = {1e30f, 1e30f, 1e30f, 1e30f,
							 1e30f, 1e30f, 1e30f, 1e30f,
							 1e30f, 1e30f, 1e30f, 1e30f,
							 1e30f, 1e30f, 1e30f, 1e30f} };
	t_mat4 Inf   = { .arr = {INFINITY, INFINITY, INFINITY, INFINITY,
							 INFINITY, INFINITY, INFINITY, INFINITY,
							 INFINITY, INFINITY, INFINITY, INFINITY,
							 INFINITY, INFINITY, INFINITY, INFINITY} };
	t_mat4 NaN   = { .arr = {NAN, NAN, NAN, NAN,
							 NAN, NAN, NAN, NAN,
							 NAN, NAN, NAN, NAN,
							 NAN, NAN, NAN, NAN} };

	t_mat4 LargeInf = mat4_add(Large, Inf);
	(void)LargeInf; // just ensure it compiles

	t_mat4 InfNaN = mat4_add(Inf, NaN);
	(void)InfNaN;

	printf("✓ ");
}

static void test_mat4_sub(void)
{
	t_mat4 A = random_mat4(-5.0f, 5.0f);
	t_mat4 B = random_mat4(-5.0f, 5.0f);
	t_mat4 Z = mat4_zero();

	// Subtraction with zero
	t_mat4 AminZ = mat4_sub(A, Z);
	assert(mat4_equal_eps(A, AminZ, EPSILON));

	// Self subtraction yields zero
	t_mat4 AminA = mat4_sub(A, A);
	assert(mat4_equal_eps(AminA, Z, EPSILON));

	// Element‑wise check
	t_mat4 AminusB = mat4_sub(A, B);
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			assert(float_equal(AminusB.mat[i][j], A.mat[i][j] - B.mat[i][j], EPSILON));

	// Relation with negation: A - B = A + (-B)
	t_mat4 negB = mat4_neg(B);
	t_mat4 AplusNegB = mat4_add(A, negB);
	assert(mat4_equal_eps(AminusB, AplusNegB, EPSILON));

	printf("✓ ");
}

static void test_mat4_mul(void)
{
	t_mat4 A = random_mat4(-2.0f, 2.0f);
	t_mat4 B = random_mat4(-2.0f, 2.0f);
	t_mat4 I = mat4_identity();
	t_mat4 Z = mat4_zero();

	// Multiply by identity
	t_mat4 AI = mat4_mul(A, I);
	t_mat4 IA = mat4_mul(I, A);
	assert(mat4_equal_eps(A, AI, EPSILON));
	assert(mat4_equal_eps(A, IA, EPSILON));

	// Multiply by zero
	t_mat4 AZ = mat4_mul(A, Z);
	t_mat4 ZA = mat4_mul(Z, A);
	assert(mat4_equal_eps(AZ, Z, EPSILON));
	assert(mat4_equal_eps(ZA, Z, EPSILON));

	// Associativity (A*B)*C == A*(B*C)
	t_mat4 C = random_mat4(-2.0f, 2.0f);
	t_mat4 AB   = mat4_mul(A, B);
	t_mat4 AB_C = mat4_mul(AB, C);
	t_mat4 BC   = mat4_mul(B, C);
	t_mat4 A_BC = mat4_mul(A, BC);
	assert(mat4_equal_eps(AB_C, A_BC, EPSILON * 10.0f)); // allow a bit more due to FP accumulation

	// Manual element‑wise verification for one case
	float a[4][4] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2}
	};
	float b[4][4] = {
		{-2, 1, 2, 3},
		{ 3, 2, 1,-1},
		{ 4, 3, 6, 5},
		{ 1, 2, 7, 8}
	};
	t_mat4 A2 = mat4_from_float_array((float*)a);
	t_mat4 B2 = mat4_from_float_array((float*)b);
	t_mat4 P = mat4_mul(A2, B2);

	// Expected product computed by hand
	float expected[4][4] = {
		{ 20, 22, 50, 48 },   // row0 * cols
		{ 44, 54, 114, 108 },
		{ 40, 58, 110, 102 },
		{ 16, 26, 46, 42 }
	};

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			assert(float_equal(P.mat[i][j], expected[i][j], 1e-5f));

	printf("✓ ");
}

static void test_mat4_scale(void)
{
	t_mat4 A = random_mat4(-3.0f, 3.0f);
	float s = 2.5f;

	t_mat4 S = mat4_scale(A, s);

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			assert(float_equal(S.mat[i][j], A.mat[i][j] * s, EPSILON));

	// Scale by 0 → zero matrix
	t_mat4 Z = mat4_scale(A, 0.0f);
	t_mat4 zero = mat4_zero();
	assert(mat4_equal_eps(Z, zero, EPSILON));

	// Scale by 1 → identity
	t_mat4 A1 = mat4_scale(A, 1.0f);
	assert(mat4_equal_eps(A, A1, EPSILON));

	// Scale by -1 → negation
	t_mat4 negA = mat4_neg(A);
	t_mat4 Aneg1 = mat4_scale(A, -1.0f);
	assert(mat4_equal_eps(negA, Aneg1, EPSILON));

	// Very large / small scalars
	t_mat4 huge = mat4_scale(A, 1e20f);
	(void)huge;
	t_mat4 tiny = mat4_scale(A, 1e-20f);
	(void)tiny;

	printf("✓ ");
}

static void test_mat4_neg(void)
{
	t_mat4 A = random_mat4(-5.0f, 5.0f);
	t_mat4 negA = mat4_neg(A);

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			assert(float_equal(negA.mat[i][j], -A.mat[i][j], EPSILON));

	// Negating twice gives original
	t_mat4 negnegA = mat4_neg(negA);
	assert(mat4_equal_eps(A, negnegA, EPSILON));

	// Negation of zero is zero
	t_mat4 Z = mat4_zero();
	t_mat4 negZ = mat4_neg(Z);
	assert(mat4_equal_eps(Z, negZ, EPSILON));

	printf("✓ ");
}

/*------------------------------------------------------------------------------
  Benchmark (optional)
------------------------------------------------------------------------------*/

#ifdef BENCHMARK

#include <time.h>

static void bench_mat4_add(void)
{
	t_mat4 A = random_mat4(-10, 10);
	t_mat4 B = random_mat4(-10, 10);
	t_mat4 C;

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < TEST_ITERATIONS; ++i)
		C = mat4_add(A, B);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("mat4_add: %d ops in %.3f s -> %.1f Mops/s\n",
		   TEST_ITERATIONS, sec, TEST_ITERATIONS / sec / 1e6);
	(void)C;
}

static void bench_mat4_mul(void)
{
	t_mat4 A = random_mat4(-10, 10);
	t_mat4 B = random_mat4(-10, 10);
	t_mat4 C;

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < TEST_ITERATIONS; ++i)
		C = mat4_mul(A, B);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("mat4_mul: %d ops in %.3f s -> %.1f Mops/s\n",
		   TEST_ITERATIONS, sec, TEST_ITERATIONS / sec / 1e6);
	(void)C;
}

static void run_benchmarks(void)
{
	printf("\n=== Running benchmarks (core) ===\n");
	bench_mat4_add();
	bench_mat4_mul();
}

#endif /* BENCHMARK */

/*------------------------------------------------------------------------------
  Main – dispatch tests or benchmarks
------------------------------------------------------------------------------*/

void test_mat4_basic()
{
	srand(42);  // deterministic seed for reproducibility

#ifdef BENCHMARK
	run_benchmarks();
#else
	test_mat4_identity();
	test_mat4_zero();
	test_mat4_from_float_array();
	test_mat4_from_basis();
	test_mat4_add();
	test_mat4_sub();
	test_mat4_mul();
	test_mat4_scale();
	test_mat4_neg();
	printf("\n");
#endif
}