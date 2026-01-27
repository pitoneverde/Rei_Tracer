#include "core/vec3.h"
#include "utils/math_constants.h"
#include "utils/debug.h"
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

static bool float_equal(float a, float b, float epsilon)
{
    return fabsf(a - b) <= epsilon;
}

static t_vec3 random_vec3(float min, float max)
{
    float range = max - min;
    return vec3_new(
        min + (float)rand() / RAND_MAX * range,
        min + (float)rand() / RAND_MAX * range,
        min + (float)rand() / RAND_MAX * range
    );
}

static t_vec3 random_unit_vec3(void)
{
    // Generate random point on unit sphere
    float theta = (float)rand() / RAND_MAX * MATH_TAU;
    float phi = acosf(2.0f * (float)rand() / RAND_MAX - 1.0f);
    return vec3_new(
        sinf(phi) * cosf(theta),
        sinf(phi) * sinf(theta),
        cosf(phi)
    );
}

// ============================================
// UNIT TESTS - vec3_length_sq
// ============================================

static void test_vec3_length_sq_basic(void)
{
    printf("=== test_vec3_length_sq_basic ===\n");
    
    // Zero vector
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    float result = vec3_length_sq(zero);
    assert(float_equal(result, 0.0f, 1e-6f));
    
    // Unit vectors
    t_vec3 i = vec3_new(1.0f, 0.0f, 0.0f);
    result = vec3_length_sq(i);
    assert(float_equal(result, 1.0f, 1e-6f));
    
    t_vec3 j = vec3_new(0.0f, 1.0f, 0.0f);
    result = vec3_length_sq(j);
    assert(float_equal(result, 1.0f, 1e-6f));
    
    t_vec3 k = vec3_new(0.0f, 0.0f, 1.0f);
    result = vec3_length_sq(k);
    assert(float_equal(result, 1.0f, 1e-6f));
    
    // Simple vector
    t_vec3 v = vec3_new(2.0f, 3.0f, 4.0f);
    result = vec3_length_sq(v);
    float expected = 2.0f*2.0f + 3.0f*3.0f + 4.0f*4.0f; // 4 + 9 + 16 = 29
    assert(float_equal(result, expected, 1e-6f));
    
    // Negative components (squared, so sign doesn't matter)
    v = vec3_new(-2.0f, -3.0f, -4.0f);
    result = vec3_length_sq(v);
    assert(float_equal(result, expected, 1e-6f));
    
    printf("✓ Basic length squared tests passed\n");
}

static void test_vec3_length_sq_properties(void)
{
    printf("=== test_vec3_length_sq_properties ===\n");
    
    // Test that length_sq(v) = dot(v, v)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-100.0f, 100.0f);
        float length_sq = vec3_length_sq(v);
        float dot_self = vec3_dot(v, v);
        
        assert(float_equal(length_sq, dot_self, 1e-6f));
    }
    
    // Test scalar multiplication: length_sq(s*v) = s² * length_sq(v)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        float s = (float)rand() / RAND_MAX * 5.0f - 2.5f;
        
        float left = vec3_length_sq(vec3_scale(v, s));
        float right = s * s * vec3_length_sq(v);
        
        assert(float_equal(left, right, 1e-3f));
    }
    
    printf("✓ Mathematical property tests passed\n");
}

static void test_vec3_length_sq_edge_cases(void)
{
    printf("=== test_vec3_length_sq_edge_cases ===\n");
    
    // Infinity
    t_vec3 inf_vec = vec3_new(INFINITY, INFINITY, INFINITY);
    float result = vec3_length_sq(inf_vec);
    assert(isinf(result));
    
    // NaN
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    result = vec3_length_sq(nan_vec);
    assert(isnan(result));
    
    // Very large values
    t_vec3 large = vec3_new(FLT_MAX, FLT_MAX, FLT_MAX);
    result = vec3_length_sq(large);
    assert(isinf(result)); // 3 * FLT_MAX² overflows to infinity
    
    // Very small values
    t_vec3 small = vec3_new(FLT_MIN, FLT_MIN, FLT_MIN);
    result = vec3_length_sq(small);
    // Should be 3 * FLT_MIN², might be very small but not zero -----> actually is zero
    assert(result >= 0.0f && result < 1e-30f);
    
    // Denormalized numbers
    t_vec3 denorm = vec3_new(FLT_MIN / 2.0f, 0.0f, 0.0f);
    result = vec3_length_sq(denorm);
    // Should still work, even if result is denormalized
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_length
// ============================================

static void test_vec3_length_basic(void)
{
    printf("=== test_vec3_length_basic ===\n");
    
    // Zero vector
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    float result = vec3_length(zero);
    assert(float_equal(result, 0.0f, 1e-6f));
    
    // Unit vectors
    t_vec3 i = vec3_new(1.0f, 0.0f, 0.0f);
    result = vec3_length(i);
    assert(float_equal(result, 1.0f, 1e-6f));
    
    // Simple vector
    t_vec3 v = vec3_new(3.0f, 4.0f, 0.0f);
    result = vec3_length(v);
    assert(float_equal(result, 5.0f, 1e-6f)); // 3-4-5 triangle
    
    v = vec3_new(2.0f, 3.0f, 6.0f);
    result = vec3_length(v);
    float expected = sqrtf(4.0f + 9.0f + 36.0f); // sqrt(49) = 7
    assert(float_equal(result, expected, 1e-6f));
    
    // Negative components (length is always positive)
    v = vec3_new(-2.0f, -3.0f, -6.0f);
    result = vec3_length(v);
    assert(float_equal(result, expected, 1e-6f));
    
    printf("✓ Basic length tests passed\n");
}

static void test_vec3_length_positive_definite(void)
{
    printf("=== test_vec3_length_positive_definite ===\n");
    
    // Length should always be >= 0
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-1000.0f, 1000.0f);
        float len = vec3_length(v);
        assert(len >= 0.0f);
        
        // Length is zero only for zero vector (within epsilon)
        if (vec3_equal(v, vec3_new(0.0f, 0.0f, 0.0f), 1e-9f))
        {
            assert(len < 1e-6f);
        }
        else
        {
            assert(len > 1e-6f);
        }
    }
    
    printf("✓ Positive definite property tests passed\n");
}

static void test_vec3_length_triangle_inequality(void)
{
    printf("=== test_vec3_length_triangle_inequality ===\n");
    
    // Triangle inequality: |a + b| <= |a| + |b|
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        float left = vec3_length(vec3_add(a, b));
        float right = vec3_length(a) + vec3_length(b);
        
        // Allow tiny floating point error
        assert(left <= right + 1e-6f);
    }
    
    printf("✓ Triangle inequality tests passed\n");
}

static void test_vec3_length_scaling(void)
{
    printf("=== test_vec3_length_scaling ===\n");
    
    // Test that length(s*v) = |s| * length(v)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        float s = (float)rand() / RAND_MAX * 10.0f - 5.0f;
        
        float left = vec3_length(vec3_scale(v, s));
        float right = fabsf(s) * vec3_length(v);
        
        assert(float_equal(left, right, 1e-5f));
    }
    
    printf("✓ Scaling property tests passed\n");
}

static void test_vec3_length_relation_to_sq(void)
{
    printf("=== test_vec3_length_relation_to_sq ===\n");
    
    // Test that length(v)² = length_sq(v)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-100.0f, 100.0f);
        float len = vec3_length(v);
        float len_sq = vec3_length_sq(v);
        
        assert(float_equal(len * len, len_sq, 1e-2f));
    }
    
    printf("✓ Relationship to length squared tests passed\n");
}

static void test_vec3_length_edge_cases(void)
{
    printf("=== test_vec3_length_edge_cases ===\n");
    
    // Infinity
    t_vec3 inf_vec = vec3_new(INFINITY, 0.0f, 0.0f);
    float result = vec3_length(inf_vec);
    assert(isinf(result));
    
    // NaN
    t_vec3 nan_vec = vec3_new(NAN, 0.0f, 0.0f);
    result = vec3_length(nan_vec);
    assert(isnan(result));
    
    // Mixed infinite and finite
    t_vec3 mixed = vec3_new(INFINITY, 1.0f, 2.0f);
    result = vec3_length(mixed);
    assert(isinf(result));
    
    // Very large but finite
    t_vec3 large = vec3_new(1e10f, 1e10f, 1e10f);
    result = vec3_length(large);
    float expected = sqrtf(3.0f) * 1e10f;
    assert(result > 1e9f && result < 1e11f);
    
    // Very small (could underflow to 0, but sqrt of very small is still very small)
    t_vec3 tiny = vec3_new(1e-20f, 1e-20f, 1e-20f);
    result = vec3_length(tiny);
    // sqrt(3e-40) = sqrt(3)*1e-20 ≈ 1.732e-20
    assert(result > 0.0f && result < 2e-20f);
    
    (void)expected;
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_min, vec3_max
// ============================================

static void test_vec3_min_max_basic(void)
{
    printf("=== test_vec3_min_max_basic ===\n");
    
    // Test vec3_min (minimum component)
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    float result = vec3_min(v);
    assert(float_equal(result, 1.0f, 1e-6f));
    
    v = vec3_new(3.0f, 2.0f, 1.0f);
    result = vec3_min(v);
    assert(float_equal(result, 1.0f, 1e-6f));
    
    v = vec3_new(2.0f, 1.0f, 3.0f);
    result = vec3_min(v);
    assert(float_equal(result, 1.0f, 1e-6f));
    
    // Test vec3_max (maximum component)
    v = vec3_new(1.0f, 2.0f, 3.0f);
    result = vec3_max(v);
    assert(float_equal(result, 3.0f, 1e-6f));
    
    v = vec3_new(3.0f, 2.0f, 1.0f);
    result = vec3_max(v);
    assert(float_equal(result, 3.0f, 1e-6f));
    
    v = vec3_new(2.0f, 3.0f, 1.0f);
    result = vec3_max(v);
    assert(float_equal(result, 3.0f, 1e-6f));
    
    // Negative values
    v = vec3_new(-1.0f, -2.0f, -3.0f);
    result = vec3_min(v);
    assert(float_equal(result, -3.0f, 1e-6f));
    result = vec3_max(v);
    assert(float_equal(result, -1.0f, 1e-6f));
    
    // Mixed positive and negative
    v = vec3_new(-2.0f, 0.0f, 1.0f);
    result = vec3_min(v);
    assert(float_equal(result, -2.0f, 1e-6f));
    result = vec3_max(v);
    assert(float_equal(result, 1.0f, 1e-6f));
    
    printf("✓ Basic min/max tests passed\n");
}

static void test_vec3_min_max_edge_cases(void)
{
    printf("=== test_vec3_min_max_edge_cases ===\n");
    
    // Infinity
    t_vec3 inf_vec = vec3_new(INFINITY, -INFINITY, 0.0f);
    float result = vec3_min(inf_vec);
    assert(isinf(result) && result < 0.0f);
    
    result = vec3_max(inf_vec);
    assert(isinf(result) && result > 0.0f);
    
    // NaN - min/max with NaN should return NaN ---> false, it compares the remaining nums and ignores the nan
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    result = vec3_min(nan_vec);
    assert(!isnan(result));
    
    result = vec3_max(nan_vec);
    assert(!isnan(result));
    
    // All NaN
    nan_vec = vec3_new(NAN, NAN, NAN);
    result = vec3_min(nan_vec);
    assert(isnan(result));
    result = vec3_max(nan_vec);
    assert(isnan(result));
    
    // Very large/small values
    t_vec3 extreme = vec3_new(FLT_MAX, -FLT_MAX, FLT_MIN);
    result = vec3_min(extreme);
    assert(float_equal(result, -FLT_MAX, 1e-6f));
    result = vec3_max(extreme);
    assert(float_equal(result, FLT_MAX, 1e-6f));
    
    // Equal components
    t_vec3 equal = vec3_new(5.0f, 5.0f, 5.0f);
    result = vec3_min(equal);
    result = vec3_max(equal);
    assert(float_equal(result, 5.0f, 1e-6f));
    
    printf("✓ Edge cases min/max tests passed\n");
}

static void test_vec3_min_max_properties(void)
{
    printf("=== test_vec3_min_max_properties ===\n");
    
    // Test that min(v) <= max(v) for all vectors
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-1000.0f, 1000.0f);
        float min_val = vec3_min(v);
        float max_val = vec3_max(v);
        
        assert(min_val <= max_val);
        
        // Each component should be between min and max
        assert(v.x >= min_val - 1e-6f && v.x <= max_val + 1e-6f);
        assert(v.y >= min_val - 1e-6f && v.y <= max_val + 1e-6f);
        assert(v.z >= min_val - 1e-6f && v.z <= max_val + 1e-6f);
    }
    
    // Test that min(v) = -max(-v)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-100.0f, 100.0f);
        float min_v = vec3_min(v);
        float max_neg_v = vec3_max(vec3_neg(v));
        
        assert(float_equal(min_v, -max_neg_v, 1e-6f));
    }
    
    printf("✓ Mathematical property tests passed\n");
}

// ============================================
// STACK ALLOCATION TESTS
// ============================================

static void test_length_stack_operations(void)
{
    printf("=== test_length_stack_operations ===\n");
    
    // Test multiple length operations on stack-allocated vectors
    
#ifdef BENCHMARK
    printf("Testing with %d operations on stack...\n", STACK_TEST_SIZE);
#endif
    
    volatile float length_results[STACK_TEST_SIZE];
    volatile float length_sq_results[STACK_TEST_SIZE];
    volatile float min_results[STACK_TEST_SIZE];
    volatile float max_results[STACK_TEST_SIZE];
    
    for (int i = 0; i < STACK_TEST_SIZE; i++)
    {
        t_vec3 v = vec3_new(
            (float)i - STACK_TEST_SIZE/2,
            (float)(i * 2) - STACK_TEST_SIZE,
            (float)(i * 3) - STACK_TEST_SIZE*1.5f
        );
        
        // Test all functions
        length_results[i] = vec3_length(v);
        length_sq_results[i] = vec3_length_sq(v);
        min_results[i] = vec3_min(v);
        max_results[i] = vec3_max(v);
    }
    
    // Verify some results
    t_vec3 test1 = vec3_new(3.0f, 4.0f, 0.0f);
    assert(float_equal(vec3_length(test1), 5.0f, 1e-6f));
    assert(float_equal(vec3_length_sq(test1), 25.0f, 1e-6f));
    assert(float_equal(vec3_min(test1), 0.0f, 1e-6f));
    assert(float_equal(vec3_max(test1), 4.0f, 1e-6f));
    
    t_vec3 test2 = vec3_new(-2.0f, 5.0f, -1.0f);
    assert(float_equal(vec3_min(test2), -2.0f, 1e-6f));
    assert(float_equal(vec3_max(test2), 5.0f, 1e-6f));
    
    (void)length_results;
    (void)length_sq_results;
    (void)min_results;
    (void)max_results;
    printf("✓ Stack operations test passed (%d vectors)\n", STACK_TEST_SIZE);
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

static void benchmark_vec3_length(void)
{
    printf("=== BENCHMARK: vec3_length ===\n");
    
    volatile float result;
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_length(v);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_length_sq(void)
{
    printf("=== BENCHMARK: vec3_length_sq ===\n");
    
    volatile float result;
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_length_sq(v);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_length_mixed(void)
{
    printf("=== BENCHMARK: Mixed length operations ===\n");
    
    volatile float result;
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    
    int length_count = 0, length_sq_count = 0, min_count = 0, max_count = 0;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        // Simulate realistic raytracing workload
        switch (i % 8)
        {
            case 0: case 1:  // 25% length
                result = vec3_length(v);
                length_count++;
                break;
            case 2: case 3:  // 25% length squared
                result = vec3_length_sq(v);
                length_sq_count++;
                break;
            case 4: case 5:  // 25% min
                result = vec3_min(v);
                min_count++;
                break;
            case 6: case 7:  // 25% max
                result = vec3_max(v);
                max_count++;
                break;
        }
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Total iterations: %d\n", TEST_ITERATIONS);
    printf("Length calls: %d, LengthSq calls: %d, Min calls: %d, Max calls: %d\n",
           length_count, length_sq_count, min_count, max_count);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Operations per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

#endif // BENCHMARK

// ============================================
// INTEGRATION TESTS
// ============================================

static void test_length_integration(void)
{
    printf("=== test_length_integration ===\n");
    
    // Test relationships between length functions and other operations
    
    // 1. length(v) = sqrt(length_sq(v))
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-100.0f, 100.0f);
        float len = vec3_length(v);
        float len_sq = vec3_length_sq(v);
        
        assert(float_equal(len * len, len_sq, 1e-2f));
        assert(float_equal(len, sqrtf(len_sq), 1e-2f));
    }
    
    // 2. length_sq(v) = dot(v, v)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-100.0f, 100.0f);
        float len_sq = vec3_length_sq(v);
        float dot_self = vec3_dot(v, v);
        
        assert(float_equal(len_sq, dot_self, 1e-6f));
    }
    
    // 3. min(v) <= length(v) <= max(v) * sqrt(3)
    //    Actually: max(|v.x|, |v.y|, |v.z|) <= length(v) <= sqrt(3) * max(|v.x|, |v.y|, |v.z|)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        float len = vec3_length(v);
        
        // Compute maximum absolute component
        float max_abs = fmaxf(fmaxf(fabsf(v.x), fabsf(v.y)), fabsf(v.z));
        
        // Lower bound
        assert(len >= max_abs - 1e-6f);
        
        // Upper bound
        assert(len <= sqrtf(3.0f) * max_abs + 1e-6f);
    }
    
    // 4. For unit vectors, length = 1
    for (int i = 0; i < 100; i++)
    {
        t_vec3 unit = random_unit_vec3();
        float len = vec3_length(unit);
        assert(float_equal(len, 1.0f, 1e-6f));
    }
    
    printf("✓ Integration tests passed\n");
}

// ============================================
// MINIRT SPECIFIC TESTS
// ============================================

static void test_length_minirt_context(void)
{
    printf("=== test_length_minirt_context ===\n");
    
    // 1. Distance checking for intersection tests
    // Often we compare squared distances to avoid sqrt
    t_vec3 point1 = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 point2 = vec3_new(3.0f, 4.0f, 0.0f);
    
    float dist_sq = vec3_length_sq(vec3_sub(point2, point1));
    float dist = vec3_length(vec3_sub(point2, point1));
    
    assert(float_equal(dist_sq, 25.0f, 1e-6f));
    assert(float_equal(dist, 5.0f, 1e-6f));
    
    // 2. Bounding box checks (using min/max of coordinates)
    t_vec3 bbox_min = vec3_new(-1.0f, -1.0f, -1.0f);
    t_vec3 bbox_max = vec3_new(1.0f, 1.0f, 1.0f);
    t_vec3 point = vec3_new(0.5f, 0.5f, 0.5f);
    
    // Check if point is inside bbox (component-wise)
    assert(vec3_min(point) >= vec3_min(bbox_min) - 1e-6f);
    assert(vec3_max(point) <= vec3_max(bbox_max) + 1e-6f);
    
    // 3. Ray length limiting
    t_vec3 ray_dir = vec3_new(1.0f, 1.0f, 1.0f);
    float ray_length = vec3_length(ray_dir);
    ray_dir = vec3_scale(ray_dir, 1.0f / ray_length); // Normalize
    
    // Now ray_dir should have length 1
    assert(float_equal(vec3_length(ray_dir), 1.0f, 1e-6f));
    
    // 4. Sphere intersection uses squared radius comparison
    t_vec3 sphere_center = vec3_new(0.0f, 0.0f, 0.0f);
    float sphere_radius = 2.0f;
    float sphere_radius_sq = sphere_radius * sphere_radius;
    
    t_vec3 test_point = vec3_new(1.0f, 1.0f, 1.0f);
    float dist_to_center_sq = vec3_length_sq(vec3_sub(test_point, sphere_center));
    
    if (dist_to_center_sq <= sphere_radius_sq)
    {
        // Point is inside sphere
        assert(dist_to_center_sq <= 4.0f + 1e-6f); // radius² = 4
    }
    
    // 5. Light attenuation (inverse square law)
    float light_distance = vec3_length(vec3_sub(test_point, vec3_new(0.0f, 5.0f, 0.0f)));
    float attenuation = 1.0f / (light_distance * light_distance);
    // Just testing the concept
    (void)attenuation;
    printf("✓ Minirt context tests passed\n");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

int main()
{
    printf("\n=======================================\n");
    printf("VEC3 LENGTH & MIN/MAX TEST SUITE\n");
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
    test_vec3_length_sq_basic();
    test_vec3_length_sq_properties();
    test_vec3_length_sq_edge_cases();
    
    test_vec3_length_basic();
    test_vec3_length_positive_definite();
    test_vec3_length_triangle_inequality();
    test_vec3_length_scaling();
    test_vec3_length_relation_to_sq();
    test_vec3_length_edge_cases();
    
    test_vec3_min_max_basic();
    test_vec3_min_max_edge_cases();
    test_vec3_min_max_properties();
    
    test_length_integration();
    test_length_minirt_context();
    
    // Stack allocation test
    test_length_stack_operations();
    
#ifdef BENCHMARK
    printf("\n=======================================\n");
    printf("RUNNING BENCHMARKS\n");
    printf("=======================================\n\n");
    
    benchmark_vec3_length();
    benchmark_vec3_length_sq();
    benchmark_length_mixed();
#endif
    
    printf("\n=======================================\n");
    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    printf("=======================================\n");
    
    return 0;
}