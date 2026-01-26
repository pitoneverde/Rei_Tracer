#include "core/vec3.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <float.h>
#include <stdint.h>

#ifdef QUICK_TEST
#define TEST_ITERATIONS 100
#define STACK_TEST_SIZE 1000
#elif defined(BENCHMARK)
#define TEST_ITERATIONS 1000000
#define STACK_TEST_SIZE 1000000
#else
#define TEST_ITERATIONS 10000
#define STACK_TEST_SIZE 100000
#endif

// ============================================
// TEST HELPERS
// ============================================

static t_vec3 random_vec3(float min, float max)
{
    float range = max - min;
    return vec3_new(
        min + (float)rand() / RAND_MAX * range,
        min + (float)rand() / RAND_MAX * range,
        min + (float)rand() / RAND_MAX * range
    );
}

// ============================================
// UNIT TESTS - vec3_add
// ============================================

static void test_vec3_add_basic(void)
{
    printf("=== test_vec3_add_basic ===\n");
    
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
    
    printf("✓ Basic addition tests passed\n");
}

static void test_vec3_add_commutative(void)
{
    printf("=== test_vec3_add_commutative ===\n");
    
    // Test commutative property: a + b = b + a
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        
        t_vec3 result1 = vec3_add(a, b);
        t_vec3 result2 = vec3_add(b, a);
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    printf("✓ Commutative property tests passed\n");
}

static void test_vec3_add_associative(void)
{
    printf("=== test_vec3_add_associative ===\n");
    
    // Test associative property: (a + b) + c = a + (b + c)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        t_vec3 c = random_vec3(-100.0f, 100.0f);
        
        t_vec3 result1 = vec3_add(vec3_add(a, b), c);
        t_vec3 result2 = vec3_add(a, vec3_add(b, c));
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    printf("✓ Associative property tests passed\n");
}

static void test_vec3_add_identity(void)
{
    printf("=== test_vec3_add_identity ===\n");
    
    // Test identity element: a + 0 = a
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 result = vec3_add(a, zero);
        
        assert(vec3_equal(result, a, 1e-6f));
    }
    
    printf("✓ Identity element tests passed\n");
}

static void test_vec3_add_edge_cases(void)
{
    printf("=== test_vec3_add_edge_cases ===\n");
    
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
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_sub
// ============================================

static void test_vec3_sub_basic(void)
{
    printf("=== test_vec3_sub_basic ===\n");
    
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
    
    printf("✓ Basic subtraction tests passed\n");
}

static void test_vec3_sub_anticommutative(void)
{
    printf("=== test_vec3_sub_anticommutative ===\n");
    
    // Test that a - b = -(b - a)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        
        t_vec3 result1 = vec3_sub(a, b);
        t_vec3 result2 = vec3_neg(vec3_sub(b, a));
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    printf("✓ Anticommutative property tests passed\n");
}

static void test_vec3_sub_identity(void)
{
    printf("=== test_vec3_sub_identity ===\n");
    
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
    
    printf("✓ Identity and self-subtraction tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_neg
// ============================================

static void test_vec3_neg_basic(void)
{
    printf("=== test_vec3_neg_basic ===\n");
    
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
    
    printf("✓ Basic negation tests passed\n");
}

static void test_vec3_neg_involutive(void)
{
    printf("=== test_vec3_neg_involutive ===\n");
    
    // Test that neg(neg(a)) = a (involutive property)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 result = vec3_neg(vec3_neg(a));
        
        assert(vec3_equal(result, a, 1e-6f));
    }
    
    printf("✓ Involutive property tests passed\n");
}

static void test_vec3_neg_relation_to_sub(void)
{
    printf("=== test_vec3_neg_relation_to_sub ===\n");
    
    // Test that neg(a) = 0 - a
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 result1 = vec3_neg(a);
        t_vec3 result2 = vec3_sub(zero, a);
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    printf("✓ Relation to subtraction tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_scale
// ============================================

static void test_vec3_scale_basic(void)
{
    printf("=== test_vec3_scale_basic ===\n");
    
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
    
    printf("✓ Basic scaling tests passed\n");
}

static void test_vec3_scale_distributive(void)
{
    printf("=== test_vec3_scale_distributive ===\n");
    
    // Test distributive property: s*(a + b) = s*a + s*b
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        float s = (float)rand() / RAND_MAX * 10.0f - 5.0f;
        
        t_vec3 result1 = vec3_scale(vec3_add(a, b), s);
        t_vec3 result2 = vec3_add(vec3_scale(a, s), vec3_scale(b, s));
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    printf("✓ Distributive property tests passed\n");
}

static void test_vec3_scale_associative(void)
{
    printf("=== test_vec3_scale_associative ===\n");
    
    // Test associative property for scalars: (s*t)*a = s*(t*a)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        float s = (float)rand() / RAND_MAX * 10.0f - 5.0f;
        float t = (float)rand() / RAND_MAX * 10.0f - 5.0f;
        
        t_vec3 result1 = vec3_scale(a, s * t);
        t_vec3 result2 = vec3_scale(vec3_scale(a, t), s);
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    printf("✓ Associative property tests passed\n");
}

static void test_vec3_scale_edge_cases(void)
{
    printf("=== test_vec3_scale_edge_cases ===\n");
    
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
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// STACK ALLOCATION TESTS
// ============================================

static void test_basic_stack_operations(void)
{
    printf("=== test_basic_stack_operations ===\n");
    
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
    t_vec3 expected_neg = vec3_new(0.0f, -1.0f, -2.0f);
    
    assert(vec3_equal(stack_results[0], expected_add, 1e-6f));
    assert(vec3_equal(stack_results[2], expected_neg, 1e-6f));
    
    printf("✓ Stack operations test passed (%d operations)\n", STACK_TEST_SIZE);
}

// ============================================
// BENCHMARKS
// ============================================

#ifdef BENCHMARK

static double get_time(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

static void benchmark_vec3_add(void)
{
    printf("=== BENCHMARK: vec3_add ===\n");
    
    volatile t_vec3 result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_add(a, b);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_sub(void)
{
    printf("=== BENCHMARK: vec3_sub ===\n");
    
    volatile t_vec3 result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_sub(a, b);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_neg(void)
{
    printf("=== BENCHMARK: vec3_neg ===\n");
    
    volatile t_vec3 result;
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_neg(v);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_scale(void)
{
    printf("=== BENCHMARK: vec3_scale ===\n");
    
    volatile t_vec3 result;
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    float s = 2.5f;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_scale(v, s);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_basic_mixed(void)
{
    printf("=== BENCHMARK: Mixed basic operations ===\n");
    
    volatile t_vec3 result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    
    int add_count = 0, sub_count = 0, neg_count = 0, scale_count = 0;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        // Simulate realistic raytracing workload pattern
        switch (i % 8)
        {
            case 0: case 1:  // 25% add
                result = vec3_add(a, b);
                add_count++;
                break;
            case 2: case 3:  // 25% sub
                result = vec3_sub(a, b);
                sub_count++;
                break;
            case 4: case 5:  // 25% scale
                result = vec3_scale(a, 0.5f);
                scale_count++;
                break;
            case 6: case 7:  // 25% neg
                result = vec3_neg(a);
                neg_count++;
                break;
        }
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Total iterations: %d\n", TEST_ITERATIONS);
    printf("Add calls: %d, Sub calls: %d, Neg calls: %d, Scale calls: %d\n",
           add_count, sub_count, neg_count, scale_count);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Operations per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

#endif // BENCHMARK

// ============================================
// INTEGRATION TESTS
// ============================================

static void test_basic_integration(void)
{
    printf("=== test_basic_integration ===\n");
    
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
    
    printf("✓ Integration tests passed\n");
}

// ============================================
// MINIRT SPECIFIC TESTS
// ============================================

static void test_basic_minirt_context(void)
{
    printf("=== test_basic_minirt_context ===\n");
    
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
    
    printf("✓ Minirt context tests passed\n");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

int main(void)
{
    printf("\n=======================================\n");
    printf("VEC3 BASIC OPERATIONS TEST SUITE\n");
    printf("Mode: ");
#ifdef QUICK_TEST
    printf("QUICK_TEST (%d iterations)\n", TEST_ITERATIONS);
#elif defined(BENCHMARK)
    printf("BENCHMARK (%d iterations)\n", TEST_ITERATIONS);
#else
    printf("FULL_TEST (%d iterations)\n", TEST_ITERATIONS);
#endif
    printf("=======================================\n\n");
    
    srand(time(NULL));
    
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
    
#ifdef BENCHMARK
    printf("\n=======================================\n");
    printf("RUNNING BENCHMARKS\n");
    printf("=======================================\n\n");
    
    benchmark_vec3_add();
    benchmark_vec3_sub();
    benchmark_vec3_neg();
    benchmark_vec3_scale();
    benchmark_basic_mixed();
#endif
    
    printf("\n=======================================\n");
    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    printf("=======================================\n");
    
    return 0;
}