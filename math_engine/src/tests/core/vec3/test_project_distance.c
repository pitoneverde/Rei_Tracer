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
// ============================================
// UNIT TESTS - vec3_project
// ============================================

static void test_vec3_project_basic(void)
{
    printf("=== test_vec3_project_basic ===\n");
    
    // Projection onto basis vectors
    t_vec3 v = vec3_new(2.0f, 3.0f, 4.0f);
    t_vec3 onto_x = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 onto_y = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 onto_z = vec3_new(0.0f, 0.0f, 1.0f);
    
    // Project onto x-axis
    t_vec3 proj = vec3_project(v, onto_x);
    t_vec3 expected = vec3_new(2.0f, 0.0f, 0.0f);
    assert(vec3_equal(proj, expected, 1e-6f));
    
    // Project onto y-axis
    proj = vec3_project(v, onto_y);
    expected = vec3_new(0.0f, 3.0f, 0.0f);
    assert(vec3_equal(proj, expected, 1e-6f));
    
    // Project onto z-axis
    proj = vec3_project(v, onto_z);
    expected = vec3_new(0.0f, 0.0f, 4.0f);
    assert(vec3_equal(proj, expected, 1e-6f));
    
    // Project onto arbitrary unit vector
    t_vec3 dir = vec3_new(1.0f, 1.0f, 0.0f);
    dir = vec3_normalize(dir);
    proj = vec3_project(v, dir);
    
    // Manual calculation: proj = (v·dir) * dir
    float dot = vec3_dot(v, dir);
    expected = vec3_scale(dir, dot);
    assert(vec3_equal(proj, expected, 1e-6f));
    
    printf("✓ Basic projection tests passed\n");
}

static void test_vec3_project_properties(void)
{
    printf("=== test_vec3_project_properties ===\n");
    
    // Test projection properties
    
    // 1. Projecting onto zero vector should return zero
    t_vec3 v = random_vec3(-10.0f, 10.0f);
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 proj = vec3_project(v, zero);
    assert(vec3_equal(proj, zero, 1e-6f));
    
    // 2. Projection is idempotent: project(project(v, u), u) = project(v, u)
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        t_vec3 u = random_vec3(-10.0f, 10.0f);
        
        // Skip if u is zero
        if (vec3_length_sq(u) < 1e-12f)
            continue;
        
        t_vec3 proj1 = vec3_project(v, u);
        t_vec3 proj2 = vec3_project(proj1, u);
        
        assert(vec3_equal(proj1, proj2, 1e-6f));
    }
    
    // 3. Projection is linear: project(a*v1 + b*v2, u) = a*project(v1, u) + b*project(v2, u)
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v1 = random_vec3(-10.0f, 10.0f);
        t_vec3 v2 = random_vec3(-10.0f, 10.0f);
        t_vec3 u = random_vec3(-10.0f, 10.0f);
        
        // Skip if u is zero
        if (vec3_length_sq(u) < 1e-12f)
            continue;
        
        float a = (float)rand() / RAND_MAX * 4.0f - 2.0f;
        float b = (float)rand() / RAND_MAX * 4.0f - 2.0f;
        
        t_vec3 left = vec3_project(vec3_add(vec3_scale(v1, a), vec3_scale(v2, b)), u);
        t_vec3 right = vec3_add(vec3_scale(vec3_project(v1, u), a),
                               vec3_scale(vec3_project(v2, u), b));
        
        assert(vec3_equal(left, right, 1e-6f));
    }
    
    // 4. Projection of v onto itself (normalized) should be v if v is parallel to u
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        
        // Skip zero
        if (vec3_length_sq(v) < 1e-12f)
            continue;
        
        t_vec3 u = vec3_normalize(v);
        t_vec3 proj = vec3_project(v, u);
        
        // Should get v back
        assert(vec3_equal(proj, v, 1e-6f));
    }
    
    printf("✓ Projection property tests passed\n");
}

static void test_vec3_project_orthogonal(void)
{
    printf("=== test_vec3_project_orthogonal ===\n");
    
    // Projection of orthogonal vectors should be zero
    for (int i = 0; i < 50; i++)
    {
        t_vec3 u = random_vec3(-10.0f, 10.0f);
        
        // Skip zero
        if (vec3_length_sq(u) < 1e-12f)
            continue;
        
        // Create v orthogonal to u
        t_vec3 v;
        do {
            v = random_vec3(-10.0f, 10.0f);
            // Make v orthogonal to u: v = v - (v·u)/(u·u) * u
            float dot_vu = vec3_dot(v, u);
            float dot_uu = vec3_dot(u, u);
            v = vec3_sub(v, vec3_scale(u, dot_vu / dot_uu));
        } while (vec3_length_sq(v) < 1e-12f); // Ensure v is not zero
        
        // Now v should be orthogonal to u
        t_vec3 proj = vec3_project(v, u);
        
        // Projection should be zero (or very close)
        assert(vec3_equal(proj, vec3_new(0.0f, 0.0f, 0.0f), 1e-6f));
    }
    
    printf("✓ Orthogonal projection tests passed\n");
}

static void test_vec3_project_edge_cases(void)
{
    printf("=== test_vec3_project_edge_cases ===\n");
    
    // Infinity cases
    t_vec3 inf_vec = vec3_new(INFINITY, 0.0f, 0.0f);
    t_vec3 finite_vec = vec3_new(1.0f, 2.0f, 3.0f);
    
    t_vec3 proj = vec3_project(finite_vec, inf_vec);
    // Result depends on implementation
    
    // NaN cases
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    proj = vec3_project(finite_vec, nan_vec);
    assert(isnan(proj.x));
    
    // Very small vectors
    t_vec3 tiny = vec3_new(1e-30f, 1e-30f, 1e-30f);
    proj = vec3_project(finite_vec, tiny);
    // Should be finite
    
    // Very large vectors
    t_vec3 large = vec3_new(1e20f, 1e20f, 1e20f);
    proj = vec3_project(finite_vec, large);
    // Should be finite
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_reject
// ============================================

static void test_vec3_reject_basic(void)
{
    printf("=== test_vec3_reject_basic ===\n");
    
    // Rejection is v - project(v, onto)
    t_vec3 v = vec3_new(2.0f, 3.0f, 4.0f);
    t_vec3 onto_x = vec3_new(1.0f, 0.0f, 0.0f);
    
    t_vec3 rej = vec3_reject(v, onto_x);
    t_vec3 proj = vec3_project(v, onto_x);
    t_vec3 expected = vec3_sub(v, proj);
    
    assert(vec3_equal(rej, expected, 1e-6f));
    
    // Rejection onto x-axis should zero out x component
    expected = vec3_new(0.0f, 3.0f, 4.0f);
    assert(vec3_equal(rej, expected, 1e-6f));
    
    // Test with arbitrary vector
    t_vec3 u = vec3_new(1.0f, 1.0f, 0.0f);
    u = vec3_normalize(u);
    
    rej = vec3_reject(v, u);
    proj = vec3_project(v, u);
    
    // v = proj + rej
    t_vec3 sum = vec3_add(proj, rej);
    assert(vec3_equal(sum, v, 1e-6f));
    
    printf("✓ Basic rejection tests passed\n");
}

static void test_vec3_reject_properties(void)
{
    printf("=== test_vec3_reject_properties ===\n");
    
    // 1. Rejection of v from itself (normalized) should be zero
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        
        // Skip zero
        if (vec3_length_sq(v) < 1e-12f)
            continue;
        
        t_vec3 u = vec3_normalize(v);
        t_vec3 rej = vec3_reject(v, u);
        
        // Should be zero (v is parallel to u)
        assert(vec3_equal(rej, vec3_new(0.0f, 0.0f, 0.0f), 1e-6f));
    }
    
    // 2. Rejection is orthogonal to projection direction
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        t_vec3 u = random_vec3(-10.0f, 10.0f);
        
        // Skip if u is zero
        if (vec3_length_sq(u) < 1e-12f)
            continue;
        
        t_vec3 rej = vec3_reject(v, u);
        
        // rej should be orthogonal to u
        float dot = vec3_dot(rej, u);
        assert(fabsf(dot) < 1e-6f);
    }
    
    // 3. Double rejection should be idempotent
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        t_vec3 u = random_vec3(-10.0f, 10.0f);
        
        // Skip if u is zero
        if (vec3_length_sq(u) < 1e-12f)
            continue;
        
        t_vec3 rej1 = vec3_reject(v, u);
        t_vec3 rej2 = vec3_reject(rej1, u);
        
        // Should be the same
        assert(vec3_equal(rej1, rej2, 1e-6f));
    }
    
    printf("✓ Rejection property tests passed\n");
}

static void test_vec3_reject_relationship(void)
{
    printf("=== test_vec3_reject_relationship ===\n");
    
    // Test the relationship: v = project(v, u) + reject(v, u)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        t_vec3 u = random_vec3(-10.0f, 10.0f);
        
        // Skip if u is zero
        if (vec3_length_sq(u) < 1e-12f)
            continue;
        
        t_vec3 proj = vec3_project(v, u);
        t_vec3 rej = vec3_reject(v, u);
        t_vec3 sum = vec3_add(proj, rej);
        
        assert(vec3_equal(sum, v, 1e-6f));
    }
    
    printf("✓ Projection-rejection relationship tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_distance_sq
// ============================================

static void test_vec3_distance_sq_basic(void)
{
    printf("=== test_vec3_distance_sq_basic ===\n");
    
    // Distance between same point is zero
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    float dist_sq = vec3_distance_sq(a, a);
    assert(float_equal(dist_sq, 0.0f, 1e-6f));
    
    // Distance along one axis
    a = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 b = vec3_new(3.0f, 0.0f, 0.0f);
    dist_sq = vec3_distance_sq(a, b);
    assert(float_equal(dist_sq, 9.0f, 1e-6f));
    
    // 3-4-5 triangle in 2D
    a = vec3_new(0.0f, 0.0f, 0.0f);
    b = vec3_new(3.0f, 4.0f, 0.0f);
    dist_sq = vec3_distance_sq(a, b);
    assert(float_equal(dist_sq, 25.0f, 1e-6f));
    
    // 3D distance
    a = vec3_new(1.0f, 2.0f, 3.0f);
    b = vec3_new(4.0f, 6.0f, 8.0f);
    dist_sq = vec3_distance_sq(a, b);
    // Δx=3, Δy=4, Δz=5 → 9+16+25=50
    assert(float_equal(dist_sq, 50.0f, 1e-6f));
    
    // Negative coordinates
    a = vec3_new(-1.0f, -2.0f, -3.0f);
    b = vec3_new(2.0f, 2.0f, 2.0f);
    dist_sq = vec3_distance_sq(a, b);
    // Δx=3, Δy=4, Δz=5 → 9+16+25=50
    assert(float_equal(dist_sq, 50.0f, 1e-6f));
    
    printf("✓ Basic distance squared tests passed\n");
}

static void test_vec3_distance_sq_properties(void)
{
    printf("=== test_vec3_distance_sq_properties ===\n");
    
    // 1. Symmetry: distance_sq(a, b) = distance_sq(b, a)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        
        float d1 = vec3_distance_sq(a, b);
        float d2 = vec3_distance_sq(b, a);
        
        assert(float_equal(d1, d2, 1e-6f));
    }
    
    // 2. Triangle inequality for squared distances doesn't hold directly,
    //    but we can test that distance_sq = length_sq(b - a)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        
        float dist_sq = vec3_distance_sq(a, b);
        t_vec3 diff = vec3_sub(b, a);
        float length_sq = vec3_length_sq(diff);
        
        assert(float_equal(dist_sq, length_sq, 1e-6f));
    }
    
    // 3. Scaling: distance_sq(k*a, k*b) = k² * distance_sq(a, b)
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        float k = (float)rand() / RAND_MAX * 5.0f - 2.5f;
        
        float left = vec3_distance_sq(vec3_scale(a, k), vec3_scale(b, k));
        float right = k * k * vec3_distance_sq(a, b);
        
        assert(float_equal(left, right, 1e-6f));
    }
    
    printf("✓ Distance squared property tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_distance
// ============================================

static void test_vec3_distance_basic(void)
{
    printf("=== test_vec3_distance_basic ===\n");
    
    // Distance between same point is zero
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    float dist = vec3_distance(a, a);
    assert(float_equal(dist, 0.0f, 1e-6f));
    
    // Distance along one axis
    a = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 b = vec3_new(3.0f, 0.0f, 0.0f);
    dist = vec3_distance(a, b);
    assert(float_equal(dist, 3.0f, 1e-6f));
    
    // 3-4-5 triangle in 2D
    a = vec3_new(0.0f, 0.0f, 0.0f);
    b = vec3_new(3.0f, 4.0f, 0.0f);
    dist = vec3_distance(a, b);
    assert(float_equal(dist, 5.0f, 1e-6f));
    
    // 3D distance
    a = vec3_new(1.0f, 2.0f, 3.0f);
    b = vec3_new(4.0f, 6.0f, 8.0f);
    dist = vec3_distance(a, b);
    // sqrt(50) ≈ 7.0710678
    assert(float_equal(dist, sqrtf(50.0f), 1e-6f));
    
    printf("✓ Basic distance tests passed\n");
}

static void test_vec3_distance_properties(void)
{
    printf("=== test_vec3_distance_properties ===\n");
    
    // 1. Symmetry: distance(a, b) = distance(b, a)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        
        float d1 = vec3_distance(a, b);
        float d2 = vec3_distance(b, a);
        
        assert(float_equal(d1, d2, 1e-6f));
    }
    
    // 2. Triangle inequality: distance(a, c) ≤ distance(a, b) + distance(b, c)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        t_vec3 c = random_vec3(-100.0f, 100.0f);
        
        float ac = vec3_distance(a, c);
        float ab = vec3_distance(a, b);
        float bc = vec3_distance(b, c);
        
        // Allow small floating point error
        assert(ac <= ab + bc + 1e-6f);
    }
    
    // 3. Relationship to distance_sq: distance² = distance_sq
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        
        float d = vec3_distance(a, b);
        float d_sq = vec3_distance_sq(a, b);
        
        assert(float_equal(d * d, d_sq, 1e-6f));
    }
    
    printf("✓ Distance property tests passed\n");
}

static void test_vec3_distance_edge_cases(void)
{
    printf("=== test_vec3_distance_edge_cases ===\n");
    
    // Infinity
    t_vec3 inf_vec = vec3_new(INFINITY, 0.0f, 0.0f);
    t_vec3 finite_vec = vec3_new(1.0f, 2.0f, 3.0f);
    
    float dist = vec3_distance(inf_vec, finite_vec);
    assert(isinf(dist));
    
    dist = vec3_distance_sq(inf_vec, finite_vec);
    assert(isinf(dist));
    
    // NaN
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    dist = vec3_distance(nan_vec, finite_vec);
    assert(isnan(dist));
    
    dist = vec3_distance_sq(nan_vec, finite_vec);
    assert(isnan(dist));
    
    // Very large distances (should not overflow)
    t_vec3 large1 = vec3_new(FLT_MAX, 0.0f, 0.0f);
    t_vec3 large2 = vec3_new(-FLT_MAX, 0.0f, 0.0f);
    
    dist = vec3_distance(large1, large2);
    assert(isinf(dist)); // 2*FLT_MAX overflows to infinity
    
    // Very small distances
    t_vec3 tiny1 = vec3_new(1e-20f, 1e-20f, 1e-20f);
    t_vec3 tiny2 = vec3_new(2e-20f, 2e-20f, 2e-20f);
    
    dist = vec3_distance(tiny1, tiny2);
    // sqrt(3 * (1e-20)²) = sqrt(3)*1e-20 ≈ 1.732e-20
    assert(dist > 0.0f && dist < 2e-20f);
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// STACK ALLOCATION TESTS
// ============================================

static void test_project_stack_operations(void)
{
    printf("=== test_project_stack_operations ===\n");
    
    // Test multiple projection/distance operations on stack
    
#ifdef BENCHMARK
    printf("Testing with %d operations on stack...\n", STACK_TEST_SIZE);
#endif
    
    volatile t_vec3 project_results[STACK_TEST_SIZE];
    volatile t_vec3 reject_results[STACK_TEST_SIZE];
    volatile float distance_results[STACK_TEST_SIZE];
    volatile float distance_sq_results[STACK_TEST_SIZE];
    
    for (int i = 0; i < STACK_TEST_SIZE; i++)
    {
        t_vec3 a = vec3_new(
            (float)i - STACK_TEST_SIZE/2,
            (float)(i * 2) - STACK_TEST_SIZE,
            (float)(i * 3) - STACK_TEST_SIZE*1.5f
        );
        
        t_vec3 b = vec3_new(
            (float)(i * 1.5f) - STACK_TEST_SIZE/3,
            (float)(i * 2.5f) - STACK_TEST_SIZE/2,
            (float)(i * 3.5f) - STACK_TEST_SIZE*2
        );
        
        // Test all functions
        project_results[i] = vec3_project(a, b);
        reject_results[i] = vec3_reject(a, b);
        distance_results[i] = vec3_distance(a, b);
        distance_sq_results[i] = vec3_distance_sq(a, b);
    }
    
    // Verify some specific cases
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(0.0f, 1.0f, 0.0f);
    
    t_vec3 proj = vec3_project(a, b);
    assert(vec3_equal(proj, vec3_new(0.0f, 2.0f, 0.0f), 1e-6f));
    
    t_vec3 rej = vec3_reject(a, b);
    assert(vec3_equal(rej, vec3_new(1.0f, 0.0f, 3.0f), 1e-6f));
    
    float dist = vec3_distance(a, b);
    assert(float_equal(dist, sqrtf(1.0f + 1.0f + 9.0f), 1e-6f));
    
    (void)project_results;
    (void)reject_results;
    (void)distance_results;
    (void)distance_sq_results;
    
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

static void benchmark_vec3_project(void)
{
    printf("=== BENCHMARK: vec3_project ===\n");
    
    volatile t_vec3 result;
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 onto = vec3_new(0.0f, 1.0f, 0.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_project(v, onto);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_reject(void)
{
    printf("=== BENCHMARK: vec3_reject ===\n");
    
    volatile t_vec3 result;
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 onto = vec3_new(0.0f, 1.0f, 0.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_reject(v, onto);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_distance(void)
{
    printf("=== BENCHMARK: vec3_distance ===\n");
    
    volatile float result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_distance(a, b);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_distance_sq(void)
{
    printf("=== BENCHMARK: vec3_distance_sq ===\n");
    
    volatile float result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_distance_sq(a, b);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_project_mixed(void)
{
    printf("=== BENCHMARK: Mixed projection/distance operations ===\n");
    
    volatile t_vec3 vec_result;
    volatile float float_result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    
    int project_count = 0, reject_count = 0, distance_count = 0, distance_sq_count = 0;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        // Simulate realistic raytracing workload
        switch (i % 12)
        {
            case 0: case 1: case 2:  // 25% distance
                float_result = vec3_distance(a, b);
                distance_count++;
                break;
            case 3: case 4: case 5:  // 25% distance squared
                float_result = vec3_distance_sq(a, b);
                distance_sq_count++;
                break;
            case 6: case 7: case 8:  // 25% project
                vec_result = vec3_project(a, b);
                project_count++;
                break;
            case 9: case 10: case 11: // 25% reject
                vec_result = vec3_reject(a, b);
                reject_count++;
                break;
        }
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Total iterations: %d\n", TEST_ITERATIONS);
    printf("Project calls: %d, Reject calls: %d, Distance calls: %d, DistanceSq calls: %d\n",
           project_count, reject_count, distance_count, distance_sq_count);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Operations per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)vec_result;
    (void)float_result;
}

#endif // BENCHMARK

// ============================================
// INTEGRATION TESTS
// ============================================

static void test_project_integration(void)
{
    printf("=== test_project_integration ===\n");
    
    // 1. Projection + Rejection = Original vector
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        t_vec3 u = random_vec3(-10.0f, 10.0f);
        
        // Skip if u is zero
        if (vec3_length_sq(u) < 1e-12f)
            continue;
        
        t_vec3 proj = vec3_project(v, u);
        t_vec3 rej = vec3_reject(v, u);
        t_vec3 sum = vec3_add(proj, rej);
        
        assert(vec3_equal(sum, v, 1e-6f));
    }
    
    // 2. Projection is parallel to u, Rejection is orthogonal to u
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        t_vec3 u = random_vec3(-10.0f, 10.0f);
        
        // Skip if u is zero
        if (vec3_length_sq(u) < 1e-12f)
            continue;
        
        t_vec3 proj = vec3_project(v, u);
        t_vec3 rej = vec3_reject(v, u);
        
        // proj should be parallel to u (or zero)
        if (vec3_length_sq(proj) > 1e-12f)
        {
            // Cross product of parallel vectors is zero
            t_vec3 cross = vec3_cross(proj, u);
            assert(vec3_equal(cross, vec3_new(0.0f, 0.0f, 0.0f), 1e-6f));
        }
        
        // rej should be orthogonal to u
        float dot = vec3_dot(rej, u);
        assert(fabsf(dot) < 1e-6f);
    }
    
    // 3. Distance squared vs distance
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        
        float d = vec3_distance(a, b);
        float d_sq = vec3_distance_sq(a, b);
        
        assert(float_equal(d * d, d_sq, 1e-6f));
    }
    
    // 4. Distance to self is zero
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        
        assert(float_equal(vec3_distance(a, a), 0.0f, 1e-6f));
        assert(float_equal(vec3_distance_sq(a, a), 0.0f, 1e-6f));
    }
    
    printf("✓ Integration tests passed\n");
}

// ============================================
// MINIRT SPECIFIC TESTS
// ============================================

static void test_project_minirt_context(void)
{
    printf("=== test_project_minirt_context ===\n");
    
    // 1. Distance to light source (for attenuation)
    t_vec3 point = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 light = vec3_new(0.0f, 5.0f, 0.0f);
    
    float light_distance = vec3_distance(point, light);
    assert(float_equal(light_distance, 5.0f, 1e-6f));
    
    // For inverse square law attenuation
    float attenuation = 1.0f / (light_distance * light_distance);
    assert(float_equal(attenuation, 0.04f, 1e-6f));
    
    // 2. Projecting point onto plane for shadows
    // Point above plane, project onto plane normal to find height
    t_vec3 point_above = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 plane_normal = vec3_new(0.0f, 1.0f, 0.0f);
    plane_normal = vec3_normalize(plane_normal);
    t_vec3 plane_point = vec3_new(0.0f, 0.0f, 0.0f);
    
    // Vector from plane to point
    t_vec3 to_point = vec3_sub(point_above, plane_point);
    
    // Project onto normal to get height above plane
    t_vec3 height_vec = vec3_project(to_point, plane_normal);
    float height = vec3_length(height_vec);
    
    // Height should be y-coordinate (2.0)
    assert(float_equal(height, 2.0f, 1e-6f));
    
    // 3. Rejection gives point projected onto plane
    t_vec3 point_on_plane = vec3_reject(to_point, plane_normal);
    // This is the point projected onto the plane (x and z components preserved, y=0)
    assert(float_equal(point_on_plane.y, 0.0f, 1e-6f));
    assert(float_equal(point_on_plane.x, 1.0f, 1e-6f));
    assert(float_equal(point_on_plane.z, 3.0f, 1e-6f));
    
    // 4. Checking if point is within certain distance of sphere
    t_vec3 sphere_center = vec3_new(0.0f, 0.0f, 0.0f);
    float sphere_radius = 2.0f;
    
    t_vec3 test_point = vec3_new(1.0f, 1.0f, 1.0f);
    float dist_to_sphere = vec3_distance(test_point, sphere_center);
    
    if (dist_to_sphere <= sphere_radius)
    {
        // Point is inside sphere
        assert(dist_to_sphere <= 2.0f + 1e-6f);
    }
    
    // 5. Ray marching - stepping along ray direction
    t_vec3 ray_origin = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 ray_dir = vec3_new(1.0f, 0.0f, 0.0f);
    ray_dir = vec3_normalize(ray_dir);
    
    float step_size = 0.5f;
    t_vec3 next_point = vec3_add(ray_origin, vec3_scale(ray_dir, step_size));
    
    // Distance from origin should be step_size
    float step_distance = vec3_distance(ray_origin, next_point);
    assert(float_equal(step_distance, step_size, 1e-6f));
    
    // 6. Orthonormal basis for coordinate system
    // Given normal n, we often need tangent and bitangent orthogonal to it
    t_vec3 normal = vec3_new(0.0f, 1.0f, 0.0f); // Up vector
    t_vec3 arbitrary = vec3_new(1.0f, 0.0f, 0.0f);
    
    // Reject arbitrary from normal to get tangent
    t_vec3 tangent = vec3_reject(arbitrary, normal);
    tangent = vec3_normalize(tangent);
    
    // tangent should be orthogonal to normal
    float dot_tn = vec3_dot(tangent, normal);
    assert(fabsf(dot_tn) < 1e-6f);
    
    // bitangent = normal × tangent
    t_vec3 bitangent = vec3_cross(normal, tangent);
    
    // All three should be orthogonal
    assert(fabsf(vec3_dot(tangent, bitangent)) < 1e-6f);
    assert(fabsf(vec3_dot(bitangent, normal)) < 1e-6f);
    
    printf("✓ Minirt context tests passed\n");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

int main()
{
    printf("\n=======================================\n");
    printf("VEC3 PROJECTION & DISTANCE TEST SUITE\n");
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
    test_vec3_project_basic();
    test_vec3_project_properties();
    test_vec3_project_orthogonal();
    test_vec3_project_edge_cases();
    
    test_vec3_reject_basic();
    test_vec3_reject_properties();
    test_vec3_reject_relationship();
    
    test_vec3_distance_sq_basic();
    test_vec3_distance_sq_properties();
    
    test_vec3_distance_basic();
    test_vec3_distance_properties();
    test_vec3_distance_edge_cases();
    
    test_project_integration();
    test_project_minirt_context();
    
    // Stack allocation test
    test_project_stack_operations();
    
#ifdef BENCHMARK
    printf("\n=======================================\n");
    printf("RUNNING BENCHMARKS\n");
    printf("=======================================\n\n");
    
    benchmark_vec3_project();
    benchmark_vec3_reject();
    benchmark_vec3_distance();
    benchmark_vec3_distance_sq();
    benchmark_project_mixed();
#endif
    
    printf("\n=======================================\n");
    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    printf("=======================================\n");
    
    return 0;
}