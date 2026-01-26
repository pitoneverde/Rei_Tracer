#include "core/vec3.h"
#include "utils/math_constants.h"
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
// UNIT TESTS - vec3_normalize
// ============================================

static void test_vec3_normalize_basic(void)
{
    printf("=== test_vec3_normalize_basic ===\n");
    
    // Unit vectors should stay unit vectors
    t_vec3 i = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 normalized = vec3_normalize(i);
    assert(vec3_equal(normalized, i, 1e-6f));
    assert(float_equal(vec3_length(normalized), 1.0f, 1e-6f));
    
    t_vec3 j = vec3_new(0.0f, 1.0f, 0.0f);
    normalized = vec3_normalize(j);
    assert(vec3_equal(normalized, j, 1e-6f));
    
    // Simple scaling
    t_vec3 v = vec3_new(2.0f, 0.0f, 0.0f);
    normalized = vec3_normalize(v);
    assert(vec3_equal(normalized, i, 1e-6f));
    assert(float_equal(vec3_length(normalized), 1.0f, 1e-6f));
    
    v = vec3_new(0.0f, 0.0f, 5.0f);
    normalized = vec3_normalize(v);
    t_vec3 k = vec3_new(0.0f, 0.0f, 1.0f);
    assert(vec3_equal(normalized, k, 1e-6f));
    
    // 3-4-5 triangle
    v = vec3_new(3.0f, 4.0f, 0.0f);
    normalized = vec3_normalize(v);
    t_vec3 expected = vec3_new(0.6f, 0.8f, 0.0f);
    assert(vec3_equal(normalized, expected, 1e-6f));
    assert(float_equal(vec3_length(normalized), 1.0f, 1e-6f));
    
    // Negative components
    v = vec3_new(-3.0f, -4.0f, 0.0f);
    normalized = vec3_normalize(v);
    expected = vec3_new(-0.6f, -0.8f, 0.0f);
    assert(vec3_equal(normalized, expected, 1e-6f));
    
    printf("✓ Basic normalization tests passed\n");
}

static void test_vec3_normalize_random(void)
{
    printf("=== test_vec3_normalize_random ===\n");
    
    // Test with random vectors
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-100.0f, 100.0f);
        
        // Skip zero or very small vectors
        if (vec3_length_sq(v) < 1e-12f)
            continue;
        
        t_vec3 normalized = vec3_normalize(v);
        float length = vec3_length(normalized);
        
        // Should have length 1
        assert(float_equal(length, 1.0f, 1e-6f));
        
        // Direction should be preserved (within sign for zero-length edge case)
        // Check that normalized = v / |v|
        t_vec3 scaled_back = vec3_scale(normalized, vec3_length(v));
        assert(vec3_equal(scaled_back, v, 1e-6f));
    }
    
    printf("✓ Random vector normalization tests passed\n");
}

static void test_vec3_normalize_direction_preservation(void)
{
    printf("=== test_vec3_normalize_direction_preservation ===\n");
    
    // Normalization should preserve direction (up to sign for zero vectors)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(0.1f, 100.0f); // Avoid zero
        
        t_vec3 normalized = vec3_normalize(v);
        
        // Check that normalized points in same direction as v
        // For non-zero v, the dot product should be positive
        float dot = vec3_dot(v, normalized);
        assert(dot > 0.0f);
        
        // The normalized vector should be v/|v|
        float length = vec3_length(v);
        t_vec3 expected = vec3_scale(v, 1.0f / length);
        assert(vec3_equal(normalized, expected, 1e-6f));
    }
    
    printf("✓ Direction preservation tests passed\n");
}

static void test_vec3_normalize_zero_vector(void)
{
    printf("=== test_vec3_normalize_zero_vector ===\n");
    
    // Normalizing zero vector is undefined in pure math
    // We need to see how your implementation handles it
    // Common approaches: return zero vector, return a default, or assert/crash
    
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 result = vec3_normalize(zero);
    
    // Check what happens - we'll just make sure it doesn't crash
    // The actual behavior depends on your implementation
    printf("  Note: zero vector normalization result: (%.6f, %.6f, %.6f)\n",
           result.x, result.y, result.z);
    
    // For very small vectors (near zero), should still work
    t_vec3 tiny = vec3_new(1e-10f, 1e-10f, 1e-10f);
    result = vec3_normalize(tiny);
    float length = vec3_length(result);
    
    // Should still have length approximately 1 (might have errors)
    assert(fabsf(length - 1.0f) < 1e-6f);
    
    printf("✓ Zero/near-zero vector tests passed\n");
}

static void test_vec3_normalize_edge_cases(void)
{
    printf("=== test_vec3_normalize_edge_cases ===\n");
    
    // Infinity - normalization of infinite vector
    t_vec3 inf_vec = vec3_new(INFINITY, 0.0f, 0.0f);
    t_vec3 result = vec3_normalize(inf_vec);
    
    // Result should be (1, 0, 0) or (NaN, NaN, NaN) depending on implementation
    printf("  Note: infinity normalization result: (%.6f, %.6f, %.6f)\n",
           result.x, result.y, result.z);
    
    // NaN
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    result = vec3_normalize(nan_vec);
    assert(isnan(result.x));
    
    // Very large values (should still normalize correctly)
    t_vec3 large = vec3_new(1e20f, 2e20f, 3e20f);
    result = vec3_normalize(large);
    float length = vec3_length(result);
    assert(float_equal(length, 1.0f, 1e-6f));
    
    // Check direction is preserved
    // large/|large| should equal result
    float large_len = vec3_length(large);
    t_vec3 expected = vec3_scale(large, 1.0f / large_len);
    assert(vec3_equal(result, expected, 1e-6f));
    
    // Very small but non-zero
    t_vec3 small = vec3_new(1e-30f, 2e-30f, 3e-30f);
    result = vec3_normalize(small);
    length = vec3_length(result);
    assert(float_equal(length, 1.0f, 1e-6f));
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_normalize_or
// ============================================

static void test_vec3_normalize_or_basic(void)
{
    printf("=== test_vec3_normalize_or_basic ===\n");
    
    // Normal case - should behave like vec3_normalize
    t_vec3 v = vec3_new(3.0f, 4.0f, 0.0f);
    t_vec3 fallback = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 result = vec3_normalize_or(v, fallback);
    
    t_vec3 expected_normalized = vec3_new(0.6f, 0.8f, 0.0f);
    assert(vec3_equal(result, expected_normalized, 1e-6f));
    
    // Zero vector - should return fallback
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    result = vec3_normalize_or(zero, fallback);
    assert(vec3_equal(result, fallback, 1e-6f));
    
    // Very small vector - might also return fallback depending on epsilon
    t_vec3 tiny = vec3_new(1e-10f, 1e-10f, 1e-10f);
    result = vec3_normalize_or(tiny, fallback);
    
    // Could return normalized tiny or fallback
    // We'll just check it doesn't crash
    printf("  Note: tiny vector with normalize_or: (%.6f, %.6f, %.6f)\n",
           result.x, result.y, result.z);
    
    printf("✓ Basic normalize_or tests passed\n");
}

static void test_vec3_normalize_or_fallback_variations(void)
{
    printf("=== test_vec3_normalize_or_fallback_variations ===\n");
    
    // Test different fallback vectors
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    
    // Fallback = zero vector
    t_vec3 result = vec3_normalize_or(zero, vec3_new(0.0f, 0.0f, 0.0f));
    assert(vec3_equal(result, vec3_new(0.0f, 0.0f, 0.0f), 1e-6f));
    
    // Fallback = unit vector
    result = vec3_normalize_or(zero, vec3_new(0.0f, 1.0f, 0.0f));
    assert(vec3_equal(result, vec3_new(0.0f, 1.0f, 0.0f), 1e-6f));
    
    // Fallback = arbitrary vector (should be returned as-is, NOT normalized)
    t_vec3 arbitrary_fallback = vec3_new(2.0f, 3.0f, 4.0f);
    result = vec3_normalize_or(zero, arbitrary_fallback);
    assert(vec3_equal(result, arbitrary_fallback, 1e-6f));
    
    // Non-zero input should ignore fallback
    t_vec3 v = vec3_new(1.0f, 0.0f, 0.0f);
    result = vec3_normalize_or(v, vec3_new(0.0f, 0.0f, 1.0f));
    assert(vec3_equal(result, v, 1e-6f)); // Should normalize to (1,0,0), not use fallback
    
    printf("✓ Fallback variation tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_is_normalized
// ============================================

static void test_vec3_is_normalized_basic(void)
{
    printf("=== test_vec3_is_normalized_basic ===\n");
    
    // Unit vectors should return true
    assert(vec3_is_normalized(vec3_new(1.0f, 0.0f, 0.0f)));
    assert(vec3_is_normalized(vec3_new(0.0f, 1.0f, 0.0f)));
    assert(vec3_is_normalized(vec3_new(0.0f, 0.0f, 1.0f)));
    
    // Normalized random vectors
    for (int i = 0; i < 50; i++)
    {
        t_vec3 unit = random_unit_vec3();
        assert(vec3_is_normalized(unit));
    }
    
    // Non-unit vectors should return false
    assert(!vec3_is_normalized(vec3_new(2.0f, 0.0f, 0.0f)));
    assert(!vec3_is_normalized(vec3_new(0.0f, 0.5f, 0.0f)));
    assert(!vec3_is_normalized(vec3_new(1.0f, 1.0f, 0.0f)));
    
    // Zero vector is not normalized
    assert(!vec3_is_normalized(vec3_new(0.0f, 0.0f, 0.0f)));
    
    // Very close to unit length (should return true with reasonable epsilon)
    t_vec3 almost_unit = vec3_new(1.000001f, 0.0f, 0.0f);
    // Depends on epsilon used in implementation
    printf("  Note: is_normalized(1.000001, 0, 0) = %d\n", vec3_is_normalized(almost_unit));
    
    printf("✓ Basic is_normalized tests passed\n");
}

static void test_vec3_is_normalized_tolerance(void)
{
    printf("=== test_vec3_is_normalized_tolerance ===\n");
    
    // Test vectors very close to unit length
    float epsilons[] = {1e-3f, 1e-6f, 1e-9f};
    
    for (int e = 0; e < 3; e++)
    {
        // We can't control the epsilon in vec3_is_normalized
        // This test just shows what the function does
        t_vec3 v1 = vec3_new(1.0f + epsilons[e], 0.0f, 0.0f);
        t_vec3 v2 = vec3_new(1.0f - epsilons[e], 0.0f, 0.0f);
        
        printf("  Epsilon ~%g: is_normalized(1±%g, 0, 0) = %d / %d\n",
               epsilons[e], epsilons[e],
               vec3_is_normalized(v1),
               vec3_is_normalized(v2));
    }
    
    // Random vectors normalized by our function should pass is_normalized
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        if (vec3_length_sq(v) > 1e-12f) // Skip near-zero
        {
            t_vec3 normalized = vec3_normalize(v);
            assert(vec3_is_normalized(normalized));
        }
    }
    
    printf("✓ Tolerance tests completed\n");
}

// ============================================
// STACK ALLOCATION TESTS
// ============================================

static void test_normalize_stack_operations(void)
{
    printf("=== test_normalize_stack_operations ===\n");
    
    // Test multiple normalization operations on stack
    
#ifdef BENCHMARK
    printf("Testing with %d operations on stack...\n", STACK_TEST_SIZE);
#endif
    
    volatile t_vec3 normalize_results[STACK_TEST_SIZE];
    volatile t_vec3 normalize_or_results[STACK_TEST_SIZE];
    volatile bool is_normalized_results[STACK_TEST_SIZE];
    
    for (int i = 0; i < STACK_TEST_SIZE; i++)
    {
        t_vec3 v = vec3_new(
            (float)i - STACK_TEST_SIZE/2,
            (float)(i * 2) - STACK_TEST_SIZE,
            (float)(i * 3) - STACK_TEST_SIZE*1.5f
        );
        
        t_vec3 fallback = vec3_new(1.0f, 0.0f, 0.0f);
        
        // Test all normalization functions
        normalize_results[i] = vec3_normalize(v);
        normalize_or_results[i] = vec3_normalize_or(v, fallback);
        is_normalized_results[i] = vec3_is_normalized(v);
    }
    
    // Verify some specific cases
    t_vec3 unit_x = vec3_new(1.0f, 0.0f, 0.0f);
    assert(vec3_is_normalized(unit_x));
    
    t_vec3 non_unit = vec3_new(2.0f, 0.0f, 0.0f);
    assert(!vec3_is_normalized(non_unit));
    
    t_vec3 normalized = vec3_normalize(non_unit);
    assert(vec3_equal(normalized, unit_x, 1e-6f));
    
    (void)normalize_or_results;
    (void)normalize_results;
    (void)is_normalized_results;
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

static void benchmark_vec3_normalize(void)
{
    printf("=== BENCHMARK: vec3_normalize ===\n");
    
    volatile t_vec3 result;
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_normalize(v);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_normalize_or(void)
{
    printf("=== BENCHMARK: vec3_normalize_or ===\n");
    
    volatile t_vec3 result;
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 fallback = vec3_new(0.0f, 1.0f, 0.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_normalize_or(v, fallback);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_is_normalized(void)
{
    printf("=== BENCHMARK: vec3_is_normalized ===\n");
    
    volatile bool result;
    t_vec3 v = vec3_new(1.0f, 0.0f, 0.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_is_normalized(v);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_normalize_mixed(void)
{
    printf("=== BENCHMARK: Mixed normalization operations ===\n");
    
    volatile t_vec3 vec_result;
    volatile bool bool_result;
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 fallback = vec3_new(0.0f, 1.0f, 0.0f);
    
    int normalize_count = 0, normalize_or_count = 0, is_normalized_count = 0;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        // Simulate realistic raytracing workload
        switch (i % 6)
        {
            case 0: case 1:  // 33% normalize
                vec_result = vec3_normalize(v);
                normalize_count++;
                break;
            case 2: case 3:  // 33% normalize_or
                vec_result = vec3_normalize_or(v, fallback);
                normalize_or_count++;
                break;
            case 4: case 5:  // 33% is_normalized
                bool_result = vec3_is_normalized(v);
                is_normalized_count++;
                break;
        }
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Total iterations: %d\n", TEST_ITERATIONS);
    printf("Normalize calls: %d, Normalize_or calls: %d, Is_normalized calls: %d\n",
           normalize_count, normalize_or_count, is_normalized_count);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Operations per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)vec_result;
    (void)bool_result;
}

#endif // BENCHMARK

// ============================================
// INTEGRATION TESTS
// ============================================

static void test_normalize_integration(void)
{
    printf("=== test_normalize_integration ===\n");
    
    // 1. normalize(v) should always produce a vector with length 1 (for non-zero v)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(0.1f, 100.0f); // Avoid zero
        t_vec3 normalized = vec3_normalize(v);
        
        assert(float_equal(vec3_length(normalized), 1.0f, 1e-6f));
        assert(vec3_is_normalized(normalized));
    }
    
    // 2. normalize_or(v, fallback) should return fallback for zero vectors
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 fallback = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 result = vec3_normalize_or(zero, fallback);
    
    assert(vec3_equal(result, fallback, 1e-6f));
    
    // 3. For non-zero vectors, normalize_or should behave like normalize
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(0.1f, 100.0f);
        t_vec3 fallback = random_vec3(-10.0f, 10.0f);
        
        t_vec3 result1 = vec3_normalize(v);
        t_vec3 result2 = vec3_normalize_or(v, fallback);
        
        // They should be equal (or opposite if v points opposite direction?)
        // Actually normalize preserves direction, so they should be equal
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    // 4. Double normalization should be idempotent
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(0.1f, 100.0f);
        t_vec3 once = vec3_normalize(v);
        t_vec3 twice = vec3_normalize(once);
        
        assert(vec3_equal(once, twice, 1e-6f));
    }
    
    // 5. normalize(scale(v, s)) = normalize(v) for any s > 0
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(0.1f, 100.0f);
        float s = (float)rand() / RAND_MAX * 10.0f + 0.1f; // Positive
        
        t_vec3 result1 = vec3_normalize(v);
        t_vec3 result2 = vec3_normalize(vec3_scale(v, s));
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    printf("✓ Integration tests passed\n");
}

// ============================================
// MINIRT SPECIFIC TESTS
// ============================================

static void test_normalize_minirt_context(void)
{
    printf("=== test_normalize_minirt_context ===\n");
    
    // 1. Normalizing ray directions
    t_vec3 ray_dir = vec3_new(1.0f, 1.0f, 1.0f);
    t_vec3 ray_dir_normalized = vec3_normalize(ray_dir);
    
    // In raytracing, we often need unit length ray directions
    assert(float_equal(vec3_length(ray_dir_normalized), 1.0f, 1e-6f));
    
    // 2. Surface normals should be normalized
    t_vec3 triangle_normal = vec3_new(0.0f, 1.0f, 1.0f);
    t_vec3 triangle_normal_normalized = vec3_normalize(triangle_normal);
    
    // Shading calculations assume normalized normals
    assert(vec3_is_normalized(triangle_normal_normalized));
    
    // 3. Reflection calculations require normalized vectors
    t_vec3 incident = vec3_new(1.0f, -1.0f, 0.0f);
    t_vec3 normal = vec3_new(0.0f, 1.0f, 0.0f);
    
    incident = vec3_normalize(incident);
    normal = vec3_normalize(normal);
    
    // Now we can compute reflection: R = I - 2*(I·N)*N
    float I_dot_N = vec3_dot(incident, normal);
    t_vec3 reflection = vec3_sub(incident, vec3_scale(normal, 2.0f * I_dot_N));
    
    // Reflection vector should also be normalized
    assert(float_equal(vec3_length(reflection), 1.0f, 1e-6f));
    
    // 4. Normalize_or for safe normal calculations
    // Sometimes we compute normals from degenerate triangles (zero area)
    t_vec3 degenerate_normal = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 default_up = vec3_new(0.0f, 1.0f, 0.0f);
    
    t_vec3 safe_normal = vec3_normalize_or(degenerate_normal, default_up);
    
    // Should use fallback for zero normal
    assert(vec3_equal(safe_normal, default_up, 1e-6f));
    
    // 5. Checking if vectors are normalized before expensive operations
    t_vec3 v1 = vec3_new(0.70710678f, 0.70710678f, 0.0f); // sqrt(2)/2
    t_vec3 v2 = vec3_new(1.0f, 1.0f, 0.0f);
    
    // v1 should be normalized, v2 should not
    assert(vec3_is_normalized(v1));
    assert(!vec3_is_normalized(v2));
    
    // In shading, we might skip normalization if already normalized
    if (!vec3_is_normalized(v1))
    {
        v1 = vec3_normalize(v1);
    }
    
    // v1 should still be normalized
    assert(vec3_is_normalized(v1));
    
    printf("✓ Minirt context tests passed\n");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

int main()
{
    printf("\n=======================================\n");
    printf("VEC3 NORMALIZATION TEST SUITE\n");
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
    test_vec3_normalize_basic();
    test_vec3_normalize_random();
    test_vec3_normalize_direction_preservation();
    test_vec3_normalize_zero_vector();
    test_vec3_normalize_edge_cases();
    
    test_vec3_normalize_or_basic();
    test_vec3_normalize_or_fallback_variations();
    
    test_vec3_is_normalized_basic();
    test_vec3_is_normalized_tolerance();
    
    test_normalize_integration();
    test_normalize_minirt_context();
    
    // Stack allocation test
    test_normalize_stack_operations();
    
#ifdef BENCHMARK
    printf("\n=======================================\n");
    printf("RUNNING BENCHMARKS\n");
    printf("=======================================\n\n");
    
    benchmark_vec3_normalize();
    benchmark_vec3_normalize_or();
    benchmark_vec3_is_normalized();
    benchmark_normalize_mixed();
#endif
    
    printf("\n=======================================\n");
    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    printf("=======================================\n");
    
    return 0;
}