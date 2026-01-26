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


// ============================================
// UNIT TESTS - vec3_new
// ============================================

static void test_vec3_new_basic(void)
{
    printf("=== test_vec3_new_basic ===\n");
    
    // Normal cases
    t_vec3 v1 = vec3_new(1.0f, 2.0f, 3.0f);
    assert(v1.x == 1.0f && v1.y == 2.0f && v1.z == 3.0f);
    
    t_vec3 v2 = vec3_new(-1.5f, 0.0f, 42.42f);
    assert(v2.x == -1.5f && v2.y == 0.0f && v2.z == 42.42f);
    
    // Zero vector
    t_vec3 v3 = vec3_new(0.0f, 0.0f, 0.0f);
    assert(v3.x == 0.0f && v3.y == 0.0f && v3.z == 0.0f);
    
    // Large values
    t_vec3 v4 = vec3_new(1e6f, -1e6f, 1e-6f);
    assert(v4.x == 1e6f && v4.y == -1e6f && v4.z == 1e-6f);
    
    printf("✓ Basic tests passed\n");
}

static void test_vec3_new_edge_cases(void)
{
    printf("=== test_vec3_new_edge_cases ===\n");
    
    // Infinity and NaN tests
    t_vec3 v1 = vec3_new(INFINITY, -INFINITY, NAN);
    assert(isinf(v1.x) && isinf(v1.y) && isnan(v1.z));
    
    // Denormalized numbers (subnormal)
    t_vec3 v2 = vec3_new(FLT_MIN / 2.0f, -FLT_MIN / 2.0f, 0.0f);
    // Just ensure it doesn't crash
    
    // Maximum float values
    t_vec3 v3 = vec3_new(FLT_MAX, -FLT_MAX, FLT_EPSILON);
    assert(v3.x == FLT_MAX && v3.y == -FLT_MAX && v3.z == FLT_EPSILON);
    
    (void)v2;
    printf("✓ Edge cases tests passed\n");
}

static void test_vec3_new_consistency(void)
{
    printf("=== test_vec3_new_consistency ===\n");
    
    // Test that multiple calls with same parameters produce same results
    for (int i = 0; i < 100; i++)
    {
        float x = (float)rand() / RAND_MAX * 1000.0f - 500.0f;
        float y = (float)rand() / RAND_MAX * 1000.0f - 500.0f;
        float z = (float)rand() / RAND_MAX * 1000.0f - 500.0f;
        
        t_vec3 v1 = vec3_new(x, y, z);
        t_vec3 v2 = vec3_new(x, y, z);
        
        assert(v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
    }
    
    printf("✓ Consistency tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_from_scalar
// ============================================

static void test_vec3_from_scalar_basic(void)
{
    printf("=== test_vec3_from_scalar_basic ===\n");
    
    // Positive scalar
    t_vec3 v1 = vec3_from_scalar(5.0f);
    assert(v1.x == 5.0f && v1.y == 5.0f && v1.z == 5.0f);
    
    // Negative scalar
    t_vec3 v2 = vec3_from_scalar(-3.14f);
    assert(v2.x == -3.14f && v2.y == -3.14f && v2.z == -3.14f);
    
    // Zero
    t_vec3 v3 = vec3_from_scalar(0.0f);
    assert(v3.x == 0.0f && v3.y == 0.0f && v3.z == 0.0f);
    
    // One
    t_vec3 v4 = vec3_from_scalar(1.0f);
    assert(v4.x == 1.0f && v4.y == 1.0f && v4.z == 1.0f);
    
    printf("✓ Basic tests passed\n");
}

static void test_vec3_from_scalar_edge_cases(void)
{
    printf("=== test_vec3_from_scalar_edge_cases ===\n");
    
    // Infinity
    t_vec3 v1 = vec3_from_scalar(INFINITY);
    assert(isinf(v1.x) && isinf(v1.y) && isinf(v1.z));
    
    // NaN
    t_vec3 v2 = vec3_from_scalar(NAN);
    assert(isnan(v2.x) && isnan(v2.y) && isnan(v2.z));
    
    // Very large
    t_vec3 v3 = vec3_from_scalar(FLT_MAX);
    assert(v3.x == FLT_MAX && v3.y == FLT_MAX && v3.z == FLT_MAX);
    
    // Very small
    t_vec3 v4 = vec3_from_scalar(FLT_MIN);
    assert(v4.x == FLT_MIN && v4.y == FLT_MIN && v4.z == FLT_MIN);
    
    // Denormalized
    t_vec3 v5 = vec3_from_scalar(FLT_MIN / 2.0f);
    // Just ensure it doesn't crash
    (void)v5;
    printf("✓ Edge cases tests passed\n");
}

static void test_vec3_from_scalar_consistency(void)
{
    printf("=== test_vec3_from_scalar_consistency ===\n");
    
    // Test that it's truly uniform
    t_vec3 v = vec3_from_scalar(7.5f);
    assert(v.x == v.y && v.y == v.z);
    
    // Multiple calls consistency
    for (int i = 0; i < 100; i++)
    {
        float s = (float)rand() / RAND_MAX * 200.0f - 100.0f;
        t_vec3 v1 = vec3_from_scalar(s);
        t_vec3 v2 = vec3_from_scalar(s);
        
        assert(v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
        assert(v1.x == v1.y && v1.y == v1.z);
    }
    
    printf("✓ Consistency tests passed\n");
}

// ============================================
// STACK ALLOCATION TESTS
// ============================================

static void test_create_stack_overflow(void)
{
    printf("=== test_create_stack_overflow ===\n");
    
    // Test creating many vectors on stack - this tests stack allocation limits
    // This is important for raytracing where many temporary vectors are created
    
#ifdef BENCHMARK
    printf("Testing with %d vectors on stack...\n", STACK_TEST_SIZE);
#endif
    
    // Use volatile to prevent optimization
    volatile t_vec3 stack_vectors[STACK_TEST_SIZE];
    
    // Initialize with patterns
    for (int i = 0; i < STACK_TEST_SIZE; i++)
    {
        stack_vectors[i] = vec3_new((float)i, (float)(i * 2), (float)(i * 3));
    }
    
    // Verify some samples
    assert(vec3_equal(stack_vectors[0], vec3_new(0.0f, 0.0f, 0.0f), 1e-6f));
    if (STACK_TEST_SIZE > 100)
    {
        assert(vec3_equal(stack_vectors[100], vec3_new(100.0f, 200.0f, 300.0f), 1e-6f));
    }
    
    printf("✓ Stack allocation test passed (created %d vectors)\n", STACK_TEST_SIZE);
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

static void benchmark_vec3_new(void)
{
    printf("=== BENCHMARK: vec3_new ===\n");
    
    volatile t_vec3 result; // volatile to prevent optimization
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_new((float)i, (float)(i + 1), (float)(i + 2));
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    // Use result to prevent optimization
    (void)result;
}

static void benchmark_vec3_from_scalar(void)
{
    printf("=== BENCHMARK: vec3_from_scalar ===\n");
    
    volatile t_vec3 result;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_from_scalar((float)i);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_create_mixed(void)
{
    printf("=== BENCHMARK: Mixed create operations ===\n");
    
    volatile t_vec3 result;
    int new_count = 0, scalar_count = 0;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        // Alternate between functions to simulate realistic workload
        if (i % 3 == 0)
        {
            result = vec3_from_scalar((float)i);
            scalar_count++;
        }
        else
        {
            result = vec3_new((float)i, (float)(i * 2), (float)(i * 3));
            new_count++;
        }
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Total iterations: %d\n", TEST_ITERATIONS);
    printf("vec3_new calls: %d\n", new_count);
    printf("vec3_from_scalar calls: %d\n", scalar_count);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Operations per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

#endif // BENCHMARK

// ============================================
// INTEGRATION TESTS
// ============================================

static void test_create_integration(void)
{
    printf("=== test_create_integration ===\n");
    
    // Test that vec3_from_scalar is equivalent to vec3_new with same value
    for (int i = 0; i < 10; i++)
    {
        float val = (float)i * 0.5f;
        t_vec3 v1 = vec3_from_scalar(val);
        t_vec3 v2 = vec3_new(val, val, val);
        
        assert(vec3_equal(v1, v2, 1e-6f));
    }
    
    // Test composition: vec3_new from vec3_from_scalar components
    t_vec3 base = vec3_from_scalar(2.0f);
    t_vec3 composed = vec3_new(base.x * 3.0f, base.y * 4.0f, base.z * 5.0f);
    t_vec3 expected = vec3_new(6.0f, 8.0f, 10.0f);
    
    assert(vec3_equal(composed, expected, 1e-6f));
    
    printf("✓ Integration tests passed\n");
}

// ============================================
// MINIRT SPECIFIC TESTS
// ============================================

static void test_create_minirt_context(void)
{
    printf("=== test_create_minirt_context ===\n");
    
    // Common vectors used in raytracing
    t_vec3 origin = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 right = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 up = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 forward = vec3_new(0.0f, 0.0f, 1.0f);
    
    // Test coordinate system basis vectors
    assert(vec3_equal(origin, vec3_new(0.0f, 0.0f, 0.0f), 1e-6f));
    assert(right.x == 1.0f && right.y == 0.0f && right.z == 0.0f);
    assert(up.x == 0.0f && up.y == 1.0f && up.z == 0.0f);
    assert(forward.x == 0.0f && forward.y == 0.0f && forward.z == 1.0f);
    
    // Colors as vectors (common in minirt)
    t_vec3 red = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 green = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 blue = vec3_new(0.0f, 0.0f, 1.0f);
    t_vec3 white = vec3_from_scalar(1.0f);
    t_vec3 black = vec3_from_scalar(0.0f);
    
    assert(red.x == 1.0f && red.y == 0.0f && red.z == 0.0f);
    assert(vec3_equal(white, vec3_new(1.0f, 1.0f, 1.0f), 1e-6f));
    assert(vec3_equal(black, vec3_new(0.0f, 0.0f, 0.0f), 1e-6f));
    
    (void)green;
    (void)blue;
    printf("✓ Minirt context tests passed\n");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

int main()
{
    printf("\n=======================================\n");
    printf("VEC3 CREATE TEST SUITE\n");
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
    test_vec3_new_basic();
    test_vec3_new_edge_cases();
    test_vec3_new_consistency();
    
    test_vec3_from_scalar_basic();
    test_vec3_from_scalar_edge_cases();
    test_vec3_from_scalar_consistency();
    
    test_create_integration();
    test_create_minirt_context();
    
    // Stack allocation test (important for performance)
    test_create_stack_overflow();
    
#ifdef BENCHMARK
    printf("\n=======================================\n");
    printf("RUNNING BENCHMARKS\n");
    printf("=======================================\n\n");
    
    benchmark_vec3_new();
    benchmark_vec3_from_scalar();
    benchmark_create_mixed();
#endif
    
    printf("\n=======================================\n");
    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    printf("=======================================\n");
    
    return 0;
}