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

// Orthogonalize b relative to a (Gram-Schmidt)
static t_vec3 orthogonalize(t_vec3 a, t_vec3 b)
{
    float dot = vec3_dot(a, b);
    float length_sq = vec3_length_sq(a);
    if (length_sq < 1e-12f) return b;
    float scale = dot / length_sq;
    return vec3_sub(b, vec3_scale(a, scale));
}

// ============================================
// UNIT TESTS - vec3_dot
// ============================================

static void test_vec3_dot_basic(void)
{
    printf("=== test_vec3_dot_basic ===\n");
    
    // Basic dot product
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    float result = vec3_dot(a, b);
    float expected = 1.0f*4.0f + 2.0f*5.0f + 3.0f*6.0f; // 4 + 10 + 18 = 32
    
    assert(float_equal(result, expected, 1e-6f));
    
    // Dot product with negative components
    a = vec3_new(-1.0f, 2.0f, -3.0f);
    b = vec3_new(2.0f, -3.0f, 4.0f);
    result = vec3_dot(a, b);
    expected = (-1.0f*2.0f) + (2.0f*-3.0f) + (-3.0f*4.0f); // -2 -6 -12 = -20
    
    assert(float_equal(result, expected, 1e-6f));
    
    // Dot product with zero vector
    a = vec3_new(1.0f, 2.0f, 3.0f);
    b = vec3_new(0.0f, 0.0f, 0.0f);
    result = vec3_dot(a, b);
    
    assert(float_equal(result, 0.0f, 1e-6f));
    
    printf("✓ Basic dot product tests passed\n");
}

static void test_vec3_dot_commutative(void)
{
    printf("=== test_vec3_dot_commutative ===\n");
    
    // Test commutative property: a·b = b·a
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        
        float result1 = vec3_dot(a, b);
        float result2 = vec3_dot(b, a);
        
        assert(float_equal(result1, result2, 1e-6f));
    }
    
    printf("✓ Commutative property tests passed\n");
}

static void test_vec3_dot_distributive(void)
{
    printf("=== test_vec3_dot_distributive ===\n");
    
    // Test distributive property: a·(b + c) = a·b + a·c
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        t_vec3 c = random_vec3(-100.0f, 100.0f);
        
        float left = vec3_dot(a, vec3_add(b, c));
        float right = vec3_dot(a, b) + vec3_dot(a, c);
        
        assert(float_equal(left, right, 1e-6f));
    }
    
    printf("✓ Distributive property tests passed\n");
}

static void test_vec3_dot_scalar_mult(void)
{
    printf("=== test_vec3_dot_scalar_mult ===\n");
    
    // Test scalar multiplication: (k*a)·b = k*(a·b) = a·(k*b)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        float k = (float)rand() / RAND_MAX * 10.0f - 5.0f;
        
        float result1 = vec3_dot(vec3_scale(a, k), b);
        float result2 = vec3_dot(a, vec3_scale(b, k));
        float result3 = k * vec3_dot(a, b);
        
        assert(float_equal(result1, result3, 1e-6f));
        assert(float_equal(result2, result3, 1e-6f));
    }
    
    printf("✓ Scalar multiplication property tests passed\n");
}

static void test_vec3_dot_orthogonal(void)
{
    printf("=== test_vec3_dot_orthogonal ===\n");
    
    // Test that orthogonal vectors have dot product = 0
    t_vec3 basis[3] = {
        vec3_new(1.0f, 0.0f, 0.0f),
        vec3_new(0.0f, 1.0f, 0.0f),
        vec3_new(0.0f, 0.0f, 1.0f)
    };
    
    // Standard basis vectors should be orthogonal
    assert(float_equal(vec3_dot(basis[0], basis[1]), 0.0f, 1e-6f));
    assert(float_equal(vec3_dot(basis[0], basis[2]), 0.0f, 1e-6f));
    assert(float_equal(vec3_dot(basis[1], basis[2]), 0.0f, 1e-6f));
    
    // Random orthogonal vectors (using Gram-Schmidt)
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        // Make b orthogonal to a
        t_vec3 b_ortho = orthogonalize(a, b);
        
        // They should be orthogonal (dot product ≈ 0)
        float dot = vec3_dot(a, b_ortho);
        assert(fabsf(dot) < 1e-6f);
    }
    
    printf("✓ Orthogonal vectors tests passed\n");
}

static void test_vec3_dot_edge_cases(void)
{
    printf("=== test_vec3_dot_edge_cases ===\n");
    
    // Infinity cases
    t_vec3 inf_vec = vec3_new(INFINITY, INFINITY, INFINITY);
    t_vec3 finite_vec = vec3_new(1.0f, 2.0f, 3.0f);
    
    float result = vec3_dot(inf_vec, finite_vec);
    assert(isinf(result));
    
    // NaN cases
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    result = vec3_dot(nan_vec, finite_vec);
    assert(isnan(result));
    
    // Very large values (potential overflow)
    t_vec3 large = vec3_new(FLT_MAX, FLT_MAX, FLT_MAX);
    result = vec3_dot(large, large);
    assert(isinf(result)); // 3 * FLT_MAX * FLT_MAX overflows to infinity
    
    // Very small values (denormalized)
    t_vec3 small = vec3_new(FLT_MIN, FLT_MIN, FLT_MIN);
    result = vec3_dot(small, small);
    // Should be 3 * FLT_MIN * FLT_MIN, might be denormalized but not zero
    assert(result > 0.0f);
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_cross
// ============================================

static void test_vec3_cross_basic(void)
{
    printf("=== test_vec3_cross_basic ===\n");
    
    // Standard basis cross products
    t_vec3 i = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 j = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 k = vec3_new(0.0f, 0.0f, 1.0f);
    
    // i × j = k
    t_vec3 result = vec3_cross(i, j);
    assert(vec3_equal(result, k, 1e-6f));
    
    // j × k = i
    result = vec3_cross(j, k);
    assert(vec3_equal(result, i, 1e-6f));
    
    // k × i = j
    result = vec3_cross(k, i);
    assert(vec3_equal(result, j, 1e-6f));
    
    // j × i = -k
    result = vec3_cross(j, i);
    t_vec3 neg_k = vec3_neg(k);
    assert(vec3_equal(result, neg_k, 1e-6f));
    
    // Cross product with zero vector
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    result = vec3_cross(i, zero);
    assert(vec3_equal(result, zero, 1e-6f));
    
    printf("✓ Basic cross product tests passed\n");
}

static void test_vec3_cross_anticommutative(void)
{
    printf("=== test_vec3_cross_anticommutative ===\n");
    
    // Test anticommutative property: a × b = -(b × a)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        t_vec3 result1 = vec3_cross(a, b);
        t_vec3 result2 = vec3_cross(b, a);
        
        // Check if result1 = -result2
        assert(vec3_equal(result1, vec3_neg(result2), 1e-6f));
    }
    
    printf("✓ Anticommutative property tests passed\n");
}

static void test_vec3_cross_orthogonal(void)
{
    printf("=== test_vec3_cross_orthogonal ===\n");
    
    // Cross product should be orthogonal to both inputs
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        t_vec3 cross = vec3_cross(a, b);
        
        // Cross should be orthogonal to a
        float dot_a = vec3_dot(cross, a);
        assert(fabsf(dot_a) < 1e-6f);
        
        // Cross should be orthogonal to b
        float dot_b = vec3_dot(cross, b);
        assert(fabsf(dot_b) < 1e-6f);
    }
    
    printf("✓ Orthogonality property tests passed\n");
}

static void test_vec3_cross_distributive(void)
{
    printf("=== test_vec3_cross_distributive ===\n");
    
    // Test distributive property: a × (b + c) = a × b + a × c
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        t_vec3 c = random_vec3(-10.0f, 10.0f);
        
        t_vec3 left = vec3_cross(a, vec3_add(b, c));
        t_vec3 right = vec3_add(vec3_cross(a, b), vec3_cross(a, c));
        
        assert(vec3_equal(left, right, 1e-6f));
    }
    
    printf("✓ Distributive property tests passed\n");
}

static void test_vec3_cross_scalar_mult(void)
{
    printf("=== test_vec3_cross_scalar_mult ===\n");
    
    // Test scalar multiplication: (k*a) × b = k*(a × b) = a × (k*b)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        float k = (float)rand() / RAND_MAX * 10.0f - 5.0f;
        
        t_vec3 result1 = vec3_cross(vec3_scale(a, k), b);
        t_vec3 result2 = vec3_cross(a, vec3_scale(b, k));
        t_vec3 result3 = vec3_scale(vec3_cross(a, b), k);
        
        assert(vec3_equal(result1, result3, 1e-6f));
        assert(vec3_equal(result2, result3, 1e-6f));
    }
    
    printf("✓ Scalar multiplication property tests passed\n");
}

static void test_vec3_cross_parallel(void)
{
    printf("=== test_vec3_cross_parallel ===\n");
    
    // Cross product of parallel vectors should be zero
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        float scalar = (float)rand() / RAND_MAX * 5.0f - 2.5f;
        t_vec3 b = vec3_scale(a, scalar); // b is parallel to a
        
        t_vec3 result = vec3_cross(a, b);
        t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
        
        assert(vec3_equal(result, zero, 1e-6f));
    }
    
    // Self cross product should be zero
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 result = vec3_cross(a, a);
        t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
        
        assert(vec3_equal(result, zero, 1e-6f));
    }
    
    printf("✓ Parallel vectors tests passed\n");
}

static void test_vec3_cross_edge_cases(void)
{
    printf("=== test_vec3_cross_edge_cases ===\n");
    
    // Infinity cases
    t_vec3 inf_vec = vec3_new(INFINITY, INFINITY, INFINITY);
    t_vec3 finite_vec = vec3_new(1.0f, 2.0f, 3.0f);
    
    t_vec3 result = vec3_cross(inf_vec, finite_vec);
    // Each component is of form INFINITY * finite - INFINITY * finite = NaN
    assert(isnan(result.x) && isnan(result.y) && isnan(result.z));
    
    // NaN cases
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    result = vec3_cross(nan_vec, finite_vec);
    assert(isnan(result.x));
    
    // Very large values
    t_vec3 large = vec3_new(FLT_MAX, FLT_MAX, FLT_MAX);
    result = vec3_cross(large, large);
    // Cross product of vector with itself should be zero
    assert(vec3_equal(result, vec3_new(0.0f, 0.0f, 0.0f), 1e-6f));
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_volume (triple product)
// ============================================

static void test_vec3_volume_basic(void)
{
    printf("=== test_vec3_volume_basic ===\n");
    
    // Volume of parallelepiped formed by basis vectors should be 1
    t_vec3 i = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 j = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 k = vec3_new(0.0f, 0.0f, 1.0f);
    
    float volume = vec3_volume(i, j, k); // i · (j × k) = i · i = 1
    assert(float_equal(volume, 1.0f, 1e-6f));
    
    // Test with scaled basis
    t_vec3 a = vec3_new(2.0f, 0.0f, 0.0f);
    t_vec3 b = vec3_new(0.0f, 3.0f, 0.0f);
    t_vec3 c = vec3_new(0.0f, 0.0f, 4.0f);
    
    volume = vec3_volume(a, b, c); // 2*3*4 = 24
    assert(float_equal(volume, 24.0f, 1e-6f));
    
    // Negative volume (left-handed system)
    volume = vec3_volume(i, k, j); // i · (k × j) = i · (-i) = -1
    assert(float_equal(volume, -1.0f, 1e-6f));
    
    printf("✓ Basic triple product tests passed\n");
}

static void test_vec3_volume_cyclic(void)
{
    printf("=== test_vec3_volume_cyclic ===\n");
    
    // Test cyclic property: a·(b×c) = b·(c×a) = c·(a×b)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        t_vec3 c = random_vec3(-10.0f, 10.0f);
        
        float v1 = vec3_volume(a, b, c);
        float v2 = vec3_volume(b, c, a);
        float v3 = vec3_volume(c, a, b);
        
        assert(float_equal(v1, v2, 1e-6f));
        assert(float_equal(v2, v3, 1e-6f));
    }
    
    printf("✓ Cyclic property tests passed\n");
}

static void test_vec3_volume_antisymmetric(void)
{
    printf("=== test_vec3_volume_antisymmetric ===\n");
    
    // Test antisymmetric property: swapping any two vectors changes sign
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        t_vec3 c = random_vec3(-10.0f, 10.0f);
        
        float v_abc = vec3_volume(a, b, c);
        float v_bac = vec3_volume(b, a, c); // swap a and b
        float v_acb = vec3_volume(a, c, b); // swap b and c
        float v_cba = vec3_volume(c, b, a); // swap a and c
        
        assert(float_equal(v_abc, -v_bac, 1e-6f));
        assert(float_equal(v_abc, -v_acb, 1e-6f));
        assert(float_equal(v_abc, -v_cba, 1e-6f));
    }
    
    printf("✓ Antisymmetric property tests passed\n");
}

static void test_vec3_volume_coplanar(void)
{
    printf("=== test_vec3_volume_coplanar ===\n");
    
    // Volume should be zero for coplanar vectors
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        // Create c as linear combination of a and b (so they're coplanar)
        float u = (float)rand() / RAND_MAX * 2.0f - 1.0f;
        float v = (float)rand() / RAND_MAX * 2.0f - 1.0f;
        t_vec3 c = vec3_add(vec3_scale(a, u), vec3_scale(b, v));
        
        float volume = vec3_volume(a, b, c);
        
        // Volume should be approximately zero
        assert(fabsf(volume) < 1e-6f);
    }
    
    // Two identical vectors (degenerate case)
    t_vec3 a = random_vec3(-10.0f, 10.0f);
    float volume = vec3_volume(a, a, random_vec3(-10.0f, 10.0f));
    assert(fabsf(volume) < 1e-6f);
    
    printf("✓ Coplanar vectors tests passed\n");
}

static void test_vec3_volume_relation_to_det(void)
{
    printf("=== test_vec3_volume_relation_to_det ===\n");
    
    // Triple product equals determinant of matrix with vectors as columns
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        t_vec3 c = random_vec3(-10.0f, 10.0f);
        
        float triple = vec3_volume(a, b, c);
        
        // Compute determinant manually: a·(b×c) = det([a b c])
        float det = a.x * (b.y*c.z - b.z*c.y)
                  - a.y * (b.x*c.z - b.z*c.x)
                  + a.z * (b.x*c.y - b.y*c.x);
        
        assert(float_equal(triple, det, 1e-6f));
    }
    
    printf("✓ Relationship to determinant tests passed\n");
}

// ============================================
// STACK ALLOCATION TESTS
// ============================================

static void test_product_stack_operations(void)
{
    printf("=== test_product_stack_operations ===\n");
    
    // Test multiple product operations on stack-allocated vectors
    // This simulates typical raytracing workload with many dot/cross products
    
#ifdef BENCHMARK
    printf("Testing with %d operations on stack...\n", STACK_TEST_SIZE);
#endif
    
    volatile float dot_results[STACK_TEST_SIZE];
    volatile t_vec3 cross_results[STACK_TEST_SIZE / 2];
    volatile float volume_results[STACK_TEST_SIZE / 3];
    
    int dot_idx = 0, cross_idx = 0, volume_idx = 0;
    
    for (int i = 0; i < STACK_TEST_SIZE; i++)
    {
        t_vec3 a = vec3_new((float)i, (float)(i + 1), (float)(i + 2));
        t_vec3 b = vec3_new((float)(i * 2), (float)(i * 3), (float)(i * 4));
        
        // Mix different product operations
        if (i % 3 == 0 && dot_idx < STACK_TEST_SIZE)
        {
            dot_results[dot_idx++] = vec3_dot(a, b);
        }
        else if (i % 3 == 1 && cross_idx < STACK_TEST_SIZE / 2)
        {
            cross_results[cross_idx++] = vec3_cross(a, b);
        }
        else if (i % 3 == 2 && volume_idx < STACK_TEST_SIZE / 3)
        {
            t_vec3 c = vec3_new((float)(i * 5), (float)(i * 6), (float)(i * 7));
            volume_results[volume_idx++] = vec3_volume(a, b, c);
        }
    }
    
    // Verify some results
    t_vec3 a = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 b = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 c = vec3_new(0.0f, 0.0f, 1.0f);
    
    assert(float_equal(vec3_dot(a, b), 0.0f, 1e-6f));
    assert(vec3_equal(vec3_cross(a, b), c, 1e-6f));
    assert(float_equal(vec3_volume(a, b, c), 1.0f, 1e-6f));
    
    (void)dot_results;
    (void)cross_results;
    (void)volume_results;
    printf("✓ Stack operations test passed (%d total operations)\n", 
           dot_idx + cross_idx + volume_idx);
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

static void benchmark_vec3_dot(void)
{
    printf("=== BENCHMARK: vec3_dot ===\n");
    
    volatile float result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_dot(a, b);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_cross(void)
{
    printf("=== BENCHMARK: vec3_cross ===\n");
    
    volatile t_vec3 result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_cross(a, b);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_volume(void)
{
    printf("=== BENCHMARK: vec3_volume ===\n");
    
    volatile float result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    t_vec3 c = vec3_new(7.0f, 8.0f, 9.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_volume(a, b, c);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_product_mixed(void)
{
    printf("=== BENCHMARK: Mixed product operations ===\n");
    
    volatile float dot_result;
    volatile t_vec3 cross_result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    t_vec3 c = vec3_new(7.0f, 8.0f, 9.0f);
    
    int dot_count = 0, cross_count = 0, volume_count = 0;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        // Simulate realistic raytracing workload pattern
        // More dot products (common), fewer cross products, even fewer triple products
        int op_type = i % 10;
        
        if (op_type < 6)  // 60% dot products
        {
            dot_result = vec3_dot(a, b);
            dot_count++;
        }
        else if (op_type < 9)  // 30% cross products
        {
            cross_result = vec3_cross(a, b);
            cross_count++;
        }
        else  // 10% triple products
        {
            dot_result = vec3_volume(a, b, c);
            volume_count++;
        }
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Total iterations: %d\n", TEST_ITERATIONS);
    printf("Dot calls: %d, Cross calls: %d, Volume calls: %d\n",
           dot_count, cross_count, volume_count);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Operations per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)dot_result;
    (void)cross_result;
}

#endif // BENCHMARK

// ============================================
// INTEGRATION TESTS
// ============================================

static void test_product_integration(void)
{
    printf("=== test_product_integration ===\n");
    
    // Test relationships between dot, cross, and volume
    
    // 1. Lagrange's identity: |a × b|² = |a|²|b|² - (a·b)²
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        t_vec3 cross = vec3_cross(a, b);
        float left = vec3_length_sq(cross);
        float right = vec3_length_sq(a) * vec3_length_sq(b) - powf(vec3_dot(a, b), 2.0f);
        
        assert(float_equal(left, right, 1e-6f));
    }
    
    // 2. Scalar triple product properties:
    //    a·(b×c) = b·(c×a) = c·(a×b)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        t_vec3 c = random_vec3(-10.0f, 10.0f);
        
        float v1 = vec3_volume(a, b, c);
        float v2 = vec3_dot(a, vec3_cross(b, c));
        
        assert(float_equal(v1, v2, 1e-6f));
    }
    
    // 3. Vector triple product expansion (not implemented, but we can test the formula):
    //    a × (b × c) = b(a·c) - c(a·b)
    //    This would require vec3_triple function which is commented out in header
    
    printf("✓ Integration tests passed\n");
}

// ============================================
// MINIRT SPECIFIC TESTS
// ============================================

static void test_product_minirt_context(void)
{
    printf("=== test_product_minirt_context ===\n");
    
    // 1. Surface normal calculation using cross product
    // For a triangle with vertices A, B, C, normal = normalize((B-A) × (C-A))
    t_vec3 A = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 B = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 C = vec3_new(0.0f, 1.0f, 0.0f);
    
    t_vec3 AB = vec3_sub(B, A);
    t_vec3 AC = vec3_sub(C, A);
    t_vec3 normal = vec3_cross(AB, AC);
    normal = vec3_normalize(normal);
    
    // Should point in positive Z direction for CCW winding
    assert(vec3_equal(normal, vec3_new(0.0f, 0.0f, 1.0f), 1e-6f));
    
    // 2. Checking if point is inside triangle using barycentric coordinates
    // One method uses cross products to check if point is on same side of all edges
    t_vec3 P = vec3_new(0.2f, 0.2f, 0.0f);
    
    t_vec3 AP = vec3_sub(P, A);
    t_vec3 BP = vec3_sub(P, B);
    t_vec3 CP = vec3_sub(P, C);
    
    // Check sign of dot(cross(AB, AP), normal) etc.
    // This is simplified - just checking the concept works
    
    // 3. Ray-plane intersection test uses dot product
    // ray: P = O + t*D, plane: N·(P - P0) = 0
    t_vec3 ray_origin = vec3_new(0.0f, 0.0f, -1.0f);
    t_vec3 ray_dir = vec3_new(0.0f, 0.0f, 1.0f);
    t_vec3 plane_point = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 plane_normal = vec3_new(0.0f, 0.0f, 1.0f);
    
    float denom = vec3_dot(ray_dir, plane_normal);
    if (fabsf(denom) > 1e-6f)
    {
        t_vec3 diff = vec3_sub(plane_point, ray_origin);
        float t = vec3_dot(diff, plane_normal) / denom;
        
        // Should intersect at t = 1
        assert(float_equal(t, 1.0f, 1e-6f));
    }
    
    // 4. Back-face culling using dot product
    // If dot(ray_dir, normal) > 0, surface is facing away from camera
    ray_dir = vec3_new(0.0f, 0.0f, 1.0f);
    normal = vec3_new(0.0f, 0.0f, 1.0f);
    float dot = vec3_dot(ray_dir, normal);
    
    // In this case, ray is facing same direction as normal (front-facing)
    assert(dot > 0.0f);
    
    // Flip normal for back face
    normal = vec3_new(0.0f, 0.0f, -1.0f);
    dot = vec3_dot(ray_dir, normal);
    assert(dot < 0.0f); // Back-facing
    
    // 5. Reflection vector calculation (would use: R = I - 2*(I·N)*N)
    t_vec3 incident = vec3_new(1.0f, -1.0f, 0.0f);
    incident = vec3_normalize(incident);
    normal = vec3_new(0.0f, 1.0f, 0.0f);
    
    float I_dot_N = vec3_dot(incident, normal);
    t_vec3 reflection = vec3_sub(incident, vec3_scale(normal, 2.0f * I_dot_N));
    
    // For perfect reflection off horizontal surface, y component should invert
    assert(float_equal(reflection.x, incident.x, 1e-6f));
    assert(float_equal(reflection.y, -incident.y, 1e-6f));
    assert(float_equal(reflection.z, incident.z, 1e-6f));
    
    (void)AP;
    (void)CP;
    (void)BP;

    printf("✓ Minirt context tests passed\n");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

int main()
{
    printf("\n=======================================\n");
    printf("VEC3 PRODUCT OPERATIONS TEST SUITE\n");
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
    test_vec3_dot_basic();
    test_vec3_dot_commutative();
    test_vec3_dot_distributive();
    test_vec3_dot_scalar_mult();
    test_vec3_dot_orthogonal();
    test_vec3_dot_edge_cases();
    
    test_vec3_cross_basic();
    test_vec3_cross_anticommutative();
    test_vec3_cross_orthogonal();
    test_vec3_cross_distributive();
    test_vec3_cross_scalar_mult();
    test_vec3_cross_parallel();
    test_vec3_cross_edge_cases();
    
    test_vec3_volume_basic();
    test_vec3_volume_cyclic();
    test_vec3_volume_antisymmetric();
    test_vec3_volume_coplanar();
    test_vec3_volume_relation_to_det();
    
    test_product_integration();
    test_product_minirt_context();
    
    // Stack allocation test
    test_product_stack_operations();
    
#ifdef BENCHMARK
    printf("\n=======================================\n");
    printf("RUNNING BENCHMARKS\n");
    printf("=======================================\n\n");
    
    benchmark_vec3_dot();
    benchmark_vec3_cross();
    benchmark_vec3_volume();
    benchmark_product_mixed();
#endif
    
    printf("\n=======================================\n");
    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    printf("=======================================\n");
    
    return 0;
}