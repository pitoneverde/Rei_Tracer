#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <float.h>
#include <stdint.h>
#include "core/vec3.h"
#include "core/test.h"

// ============================================
// UNIT TESTS - vec3_add
// ============================================

static void test_vec3_add_basic(void)
{
	// Basic addition
	t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
	t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
	t_vec3 result = vec3_add(a, b);
	t_vec3 expected = vec3_new(5.0f, 7.0f, 9.0f);
	
	assert(vec3_equal(result, expected, 1e-6f));
	
	// Addition with negative numbers
	a = vec3_new(-1.0f, -2.0f, -3.0f);
	b = vec3_new(1.0f, 2.0f, 3.0f);
	result = vec3_add(a, b);
	expected = vec3_new(0.0f, 0.0f, 0.0f);
	
	assert(vec3_equal(result, expected, 1e-6f));
	
	// Addition with zero
	a = vec3_new(5.0f, 10.0f, 15.0f);
	b = vec3_new(0.0f, 0.0f, 0.0f);
	result = vec3_add(a, b);
	
	assert(vec3_equal(result, a, 1e-6f));
	
	printf("✓ ");
}

static void test_vec3_add_commutative(void)
{
	// Test commutative property: a + b = b + a
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		t_vec3 b = random_vec3(-100.0f, 100.0f);
		
		t_vec3 result1 = vec3_add(a, b);
		t_vec3 result2 = vec3_add(b, a);
		
		assert(vec3_equal(result1, result2, 1e-6f));
	}
	
	printf("✓ ");
}

static void test_vec3_add_associative(void)
{
	// Test associative property: (a + b) + c = a + (b + c)
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		t_vec3 b = random_vec3(-100.0f, 100.0f);
		t_vec3 c = random_vec3(-100.0f, 100.0f);
		
		t_vec3 result1 = vec3_add(vec3_add(a, b), c);
		t_vec3 result2 = vec3_add(a, vec3_add(b, c));
		
		assert(vec3_equal(result1, result2, 1e-4f));        // considered guarateed 7 significant digits on float32
	}
	
	printf("✓ ");
}

static void test_vec3_add_identity(void)
{
	// Test identity element: a + 0 = a
	t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
	
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		t_vec3 result = vec3_add(a, zero);
		
		assert(vec3_equal(result, a, 1e-6f));
	}
	
	printf("✓ ");
}

static void test_vec3_add_edge_cases(void)
{
	// Infinity cases
	t_vec3 inf_vec = vec3_new(INFINITY, -INFINITY, INFINITY);
	t_vec3 finite_vec = vec3_new(1.0f, 2.0f, 3.0f);
	
	t_vec3 result = vec3_add(inf_vec, finite_vec);
	assert(isinf(result.x) && isinf(result.y) && isinf(result.z));
	
	// NaN cases
	t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
	result = vec3_add(nan_vec, finite_vec);
	assert(isnan(result.x));
	
	// Large values (check for overflow)
	t_vec3 large1 = vec3_new(FLT_MAX, FLT_MAX, FLT_MAX);
	t_vec3 large2 = vec3_new(FLT_MAX, FLT_MAX, FLT_MAX);
	result = vec3_add(large1, large2);
	assert(isinf(result.x) && isinf(result.y) && isinf(result.z));
	
	printf("✓ ");
}

// ============================================
// UNIT TESTS - vec3_sub
// ============================================

static void test_vec3_sub_basic(void)
{
	// Basic subtraction
	t_vec3 a = vec3_new(5.0f, 10.0f, 15.0f);
	t_vec3 b = vec3_new(1.0f, 2.0f, 3.0f);
	t_vec3 result = vec3_sub(a, b);
	t_vec3 expected = vec3_new(4.0f, 8.0f, 12.0f);
	
	assert(vec3_equal(result, expected, 1e-6f));
	
	// Subtraction resulting in negative values
	a = vec3_new(1.0f, 2.0f, 3.0f);
	b = vec3_new(5.0f, 10.0f, 15.0f);
	result = vec3_sub(a, b);
	expected = vec3_new(-4.0f, -8.0f, -12.0f);
	
	assert(vec3_equal(result, expected, 1e-6f));
	
	// Subtraction with zero
	a = vec3_new(5.0f, 10.0f, 15.0f);
	b = vec3_new(0.0f, 0.0f, 0.0f);
	result = vec3_sub(a, b);
	
	assert(vec3_equal(result, a, 1e-6f));
	
	printf("✓ ");
}

static void test_vec3_sub_anticommutative(void)
{
	// Test that a - b = -(b - a)
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		t_vec3 b = random_vec3(-100.0f, 100.0f);
		
		t_vec3 result1 = vec3_sub(a, b);
		t_vec3 result2 = vec3_neg(vec3_sub(b, a));
		
		assert(vec3_equal(result1, result2, 1e-6f));
	}
	
	printf("✓ ");
}

static void test_vec3_sub_identity(void)
{
	// Test identity element: a - 0 = a
	t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
	
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		t_vec3 result = vec3_sub(a, zero);
		
		assert(vec3_equal(result, a, 1e-6f));
	}
	
	// Test self-subtraction: a - a = 0
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		t_vec3 result = vec3_sub(a, a);
		
		assert(vec3_equal(result, zero, 1e-6f));
	}
	
	printf("✓ ");
}

// ============================================
// UNIT TESTS - vec3_neg
// ============================================

static void test_vec3_neg_basic(void)
{
	// Basic negation
	t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
	t_vec3 result = vec3_neg(v);
	t_vec3 expected = vec3_new(-1.0f, -2.0f, -3.0f);
	
	assert(vec3_equal(result, expected, 1e-6f));
	
	// Negation of negative vector
	v = vec3_new(-4.0f, -5.0f, -6.0f);
	result = vec3_neg(v);
	expected = vec3_new(4.0f, 5.0f, 6.0f);
	
	assert(vec3_equal(result, expected, 1e-6f));
	
	// Negation of zero vector
	v = vec3_new(0.0f, 0.0f, 0.0f);
	result = vec3_neg(v);
	
	assert(vec3_equal(result, v, 1e-6f));
	
	printf("✓ ");
}

static void test_vec3_neg_involutive(void)
{
	// Test that neg(neg(a)) = a (involutive property)
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		t_vec3 result = vec3_neg(vec3_neg(a));
		
		assert(vec3_equal(result, a, 1e-6f));
	}
	
	printf("✓ ");
}

static void test_vec3_neg_relation_to_sub(void)
{
	// Test that neg(a) = 0 - a
	t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
	
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		t_vec3 result1 = vec3_neg(a);
		t_vec3 result2 = vec3_sub(zero, a);
		
		assert(vec3_equal(result1, result2, 1e-6f));
	}
	
	printf("✓ ");
}

// ============================================
// UNIT TESTS - vec3_scale
// ============================================

static void test_vec3_scale_basic(void)
{
	// Basic scaling
	t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
	t_vec3 result = vec3_scale(v, 2.0f);
	t_vec3 expected = vec3_new(2.0f, 4.0f, 6.0f);
	
	assert(vec3_equal(result, expected, 1e-6f));
	
	// Scaling by 1 (identity)
	result = vec3_scale(v, 1.0f);
	assert(vec3_equal(result, v, 1e-6f));
	
	// Scaling by 0
	result = vec3_scale(v, 0.0f);
	expected = vec3_new(0.0f, 0.0f, 0.0f);
	assert(vec3_equal(result, expected, 1e-6f));
	
	// Scaling by -1 (equivalent to negation)
	result = vec3_scale(v, -1.0f);
	t_vec3 neg_v = vec3_neg(v);
	assert(vec3_equal(result, neg_v, 1e-6f));
	
	printf("✓ ");
}

static void test_vec3_scale_distributive(void)
{
	// Test distributive property: s*(a + b) = s*a + s*b
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		t_vec3 b = random_vec3(-100.0f, 100.0f);
		float s = (float)rand() / RAND_MAX * 10.0f - 5.0f;
		
		t_vec3 result1 = vec3_scale(vec3_add(a, b), s);
		t_vec3 result2 = vec3_add(vec3_scale(a, s), vec3_scale(b, s));
		
		assert(vec3_equal(result1, result2, 1e-3f));
	}
	
	printf("✓ ");
}

static void test_vec3_scale_associative(void)
{
	// Test associative property for scalars: (s*t)*a = s*(t*a)
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		float s = (float)rand() / RAND_MAX * 10.0f - 5.0f;
		float t = (float)rand() / RAND_MAX * 10.0f - 5.0f;
		
		t_vec3 result1 = vec3_scale(a, s * t);
		t_vec3 result2 = vec3_scale(vec3_scale(a, t), s);

		assert(vec3_equal(result1, result2, 1e-3f));
	}
	
	printf("✓ ");
}

static void test_vec3_scale_edge_cases(void)
{
	// Scaling by infinity
	t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
	t_vec3 result = vec3_scale(v, INFINITY);
	assert(isinf(result.x) && isinf(result.y) && isinf(result.z));
	
	// Scaling by NaN
	result = vec3_scale(v, NAN);
	assert(isnan(result.x) && isnan(result.y) && isnan(result.z));
	
	// Scaling vector with NaN/Inf components
	t_vec3 bad_vec = vec3_new(NAN, INFINITY, -INFINITY);
	result = vec3_scale(bad_vec, 2.0f);
	assert(isnan(result.x) && isinf(result.y) && isinf(result.z));
	
	// Very large scalar causing overflow
	v = vec3_new(1.0f, 1.0f, 1.0f);
	result = vec3_scale(v, FLT_MAX);
	assert(result.x == FLT_MAX && result.y == FLT_MAX && result.z == FLT_MAX);
	
	// Very small scalar (denormalized)
	result = vec3_scale(v, FLT_MIN / 2.0f);
	// Just ensure it doesn't crash
	
	printf("✓ ");
}

// ============================================
// STACK ALLOCATION TESTS
// ============================================

static void test_basic_stack_operations(void)
{
	// Test multiple operations on stack-allocated vectors
	// This simulates typical raytracing workload
	
#ifdef BENCHMARK
	printf("Testing with %d operations on stack...\n", STACK_TEST_SIZE);
#endif
	
	volatile t_vec3 stack_results[STACK_TEST_SIZE];
	
	for (int i = 0; i < STACK_TEST_SIZE; i++)
	{
		t_vec3 a = vec3_new((float)i, (float)(i + 1), (float)(i + 2));
		t_vec3 b = vec3_new((float)(i * 2), (float)(i * 3), (float)(i * 4));
		
		// Mix different operations
		if (i % 4 == 0)
			stack_results[i] = vec3_add(a, b);
		else if (i % 4 == 1)
			stack_results[i] = vec3_sub(a, b);
		else if (i % 4 == 2)
			stack_results[i] = vec3_neg(a);
		else
			stack_results[i] = vec3_scale(a, 0.5f);
	}
	
	// Verify some results
	// t_vec3 a = vec3_new(0.0f, 1.0f, 2.0f);
	// t_vec3 b = vec3_new(0.0f, 0.0f, 0.0f);
	t_vec3 expected_add = vec3_new(0.0f, 1.0f, 2.0f);
	t_vec3 expected_neg = vec3_new(-2.0f, -3.0f, -4.0f);
	
	assert(vec3_equal(stack_results[0], expected_add, 1e-6f));
	assert(vec3_equal(stack_results[2], expected_neg, 1e-6f));
	
	printf("✓\tStack operations test passed (%d operations)\n", STACK_TEST_SIZE);
}

// ============================================
// BENCHMARKS
// ============================================

#ifdef BENCHMARK

#include <time.h>

static void bench_vec3_add(void)
{
	volatile t_vec3 result;
	t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
	t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < TEST_ITERATIONS; i++)
		result = vec3_add(a, b);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("vec3_add: %d ops in %.3f s -> %.1f Mops/s\n",
		   TEST_ITERATIONS, sec, TEST_ITERATIONS / sec / 1e6);
	(void)result;
}

static void bench_vec3_sub(void)
{
	volatile t_vec3 result;
	t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
	t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < TEST_ITERATIONS; i++)
		result = vec3_sub(a, b);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("vec3_sub: %d ops in %.3f s -> %.1f Mops/s\n",
		   TEST_ITERATIONS, sec, TEST_ITERATIONS / sec / 1e6);
	(void)result;
}

static void bench_vec3_neg(void)
{
	volatile t_vec3 result;
	t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < TEST_ITERATIONS; i++)
		result = vec3_neg(v);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("vec3_neg: %d ops in %.3f s -> %.1f Mops/s\n",
		   TEST_ITERATIONS, sec, TEST_ITERATIONS / sec / 1e6);
	(void)result;
}

static void bench_vec3_scale(void)
{
	volatile t_vec3 result;
	t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
	float s = 2.5f;

	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < TEST_ITERATIONS; i++)
		result = vec3_scale(v, s);
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("vec3_scale: %d ops in %.3f s -> %.1f Mops/s\n",
		   TEST_ITERATIONS, sec, TEST_ITERATIONS / sec / 1e6);
	(void)result;
}

static void bench_basic_mixed(void)
{
	volatile t_vec3 result;
	t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
	t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
	
	struct timespec t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < TEST_ITERATIONS; i++)
	{
		// Simulate realistic raytracing workload pattern
		switch (i & 7)
		{
			case 0: case 1:  // 25% add
				result = vec3_add(a, b);
				break;
			case 2: case 3:  // 25% sub
				result = vec3_sub(a, b);
				break;
			case 4: case 5:  // 25% scale
				result = vec3_scale(a, 0.5f);
				break;
			case 6: case 7:  // 25% neg
				result = vec3_neg(a);
				break;
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &t2);

	double sec = time_diff_sec(t1, t2);
	printf("mixed basic: %d ops in %.3f s -> %.1f Mops/s\n",
		   TEST_ITERATIONS, sec, TEST_ITERATIONS / sec / 1e6);
	(void)result;
}

#endif // BENCHMARK

// ============================================
// INTEGRATION TESTS
// ============================================

static void test_basic_integration(void)
{
	// Test relationships between operations
	
	// 1. a + (-a) = 0
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		t_vec3 result = vec3_add(a, vec3_neg(a));
		t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
		
		assert(vec3_equal(result, zero, 1e-6f));
	}
	
	// 2. a - b = a + (-b)
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		t_vec3 b = random_vec3(-100.0f, 100.0f);
		
		t_vec3 result1 = vec3_sub(a, b);
		t_vec3 result2 = vec3_add(a, vec3_neg(b));
		
		assert(vec3_equal(result1, result2, 1e-6f));
	}
	
	// 3. scale(-1, a) = -a
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		
		t_vec3 result1 = vec3_scale(a, -1.0f);
		t_vec3 result2 = vec3_neg(a);
		
		assert(vec3_equal(result1, result2, 1e-6f));
	}
	
	// 4. scale(0, a) = 0
	t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 100; i++)
	{
		t_vec3 a = random_vec3(-100.0f, 100.0f);
		t_vec3 result = vec3_scale(a, 0.0f);
		
		assert(vec3_equal(result, zero, 1e-6f));
	}
	
	printf("✓ ");
}

// ============================================
// MINIRT SPECIFIC TESTS
// ============================================

static void test_basic_minirt_context(void)
{
	// Ray equation: origin + t*direction
	t_vec3 ray_origin = vec3_new(0.0f, 0.0f, 0.0f);
	t_vec3 ray_direction = vec3_new(1.0f, 0.0f, 0.0f);
	float t = 5.0f;
	
	t_vec3 point_on_ray = vec3_add(ray_origin, vec3_scale(ray_direction, t));
	t_vec3 expected_point = vec3_new(5.0f, 0.0f, 0.0f);
	
	assert(vec3_equal(point_on_ray, expected_point, 1e-6f));
	
	// Surface normal calculation (often involves negation)
	t_vec3 incoming_ray = vec3_new(0.0f, 0.0f, -1.0f);
	t_vec3 normal = vec3_new(0.0f, 0.0f, 1.0f);
	
	// If ray is coming from opposite direction of normal
	if (vec3_dot(incoming_ray, normal) > 0)
	{
		normal = vec3_neg(normal);
	}
	
	assert(vec3_equal(normal, vec3_new(0.0f, 0.0f, 1.0f), 1e-6f));
	
	// Color mixing (additive)
	t_vec3 color1 = vec3_new(0.5f, 0.2f, 0.1f);
	t_vec3 color2 = vec3_new(0.1f, 0.3f, 0.4f);
	t_vec3 mixed_color = vec3_add(color1, color2);
	t_vec3 expected_color = vec3_new(0.6f, 0.5f, 0.5f);
	
	assert(vec3_equal(mixed_color, expected_color, 1e-6f));
	
	// Attenuation (scaling)
	t_vec3 light_color = vec3_new(1.0f, 1.0f, 1.0f);
	float attenuation = 0.5f;
	t_vec3 attenuated_color = vec3_scale(light_color, attenuation);
	
	assert(vec3_equal(attenuated_color, vec3_new(0.5f, 0.5f, 0.5f), 1e-6f));
	
	printf("✓ ");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

void test_vec3_basic()
{ 
#ifdef BENCHMARK
    printf("\n=== Running benchmarks (basic) ===\n");
	bench_vec3_add();
	bench_vec3_sub();
	bench_vec3_neg();
	bench_vec3_scale();
	bench_basic_mixed();
#else
	srand(42);
	
	// Run unit tests
	test_vec3_add_basic();
	test_vec3_add_commutative();
	test_vec3_add_associative();
	test_vec3_add_identity();
	test_vec3_add_edge_cases();
	
	test_vec3_sub_basic();
	test_vec3_sub_anticommutative();
	test_vec3_sub_identity();
	
	test_vec3_neg_basic();
	test_vec3_neg_involutive();
	test_vec3_neg_relation_to_sub();
	
	test_vec3_scale_basic();
	test_vec3_scale_distributive();
	test_vec3_scale_associative();
	test_vec3_scale_edge_cases();
	
	test_basic_integration();
	test_basic_minirt_context();
	
	// Stack allocation test
	test_basic_stack_operations();
#endif
}