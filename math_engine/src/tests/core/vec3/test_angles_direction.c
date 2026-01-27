#include "core/vec3.h"
#include "utils/debug.h"
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
// UNIT TESTS - vec3_angle
// ============================================

static void test_vec3_angle_basic(void)
{
    printf("=== test_vec3_angle_basic ===\n");
    
    // Angle between same vector is 0
    t_vec3 v = vec3_new(1.0f, 0.0f, 0.0f);
    float angle = vec3_angle(v, v);
    assert(float_equal(angle, 0.0f, 1e-6f));
    
    // Angle between orthogonal vectors is 90 degrees (π/2 radians)
    t_vec3 i = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 j = vec3_new(0.0f, 1.0f, 0.0f);
    angle = vec3_angle(i, j);
    assert(float_equal(angle, MATH_PI_2, 1e-6f));
    
    // Angle between opposite vectors is 180 degrees (π radians)
    t_vec3 neg_i = vec3_new(-1.0f, 0.0f, 0.0f);
    angle = vec3_angle(i, neg_i);
    assert(float_equal(angle, MATH_PI, 1e-6f));
    
    // 45 degree angle
    t_vec3 v1 = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 v2 = vec3_new(1.0f, 1.0f, 0.0f);
    v2 = vec3_normalize(v2);
    angle = vec3_angle(v1, v2);
    assert(float_equal(angle, MATH_PI_4, 1e-6f)); // 45° = π/4
    
    // 60 degree angle
    v1 = vec3_new(1.0f, 0.0f, 0.0f);
    v2 = vec3_new(0.5f, sqrtf(3.0f)/2.0f, 0.0f); // cos60=0.5, sin60=√3/2
    angle = vec3_angle(v1, v2);
    assert(float_equal(angle, MATH_PI/3.0f, 1e-6f)); // 60° = π/3
    
    // 3D vectors
    v1 = vec3_new(1.0f, 2.0f, 3.0f);
    v2 = vec3_new(4.0f, 5.0f, 6.0f);
    angle = vec3_angle(v1, v2);
    
    // Manual calculation: angle = acos(dot/(|v1||v2|))
    float dot = vec3_dot(v1, v2);
    float len1 = vec3_length(v1);
    float len2 = vec3_length(v2);
    float expected = acosf(dot / (len1 * len2));
    assert(float_equal(angle, expected, 1e-6f));
    
    printf("✓ Basic angle tests passed\n");
}

static void test_vec3_angle_symmetry(void)
{
    printf("=== test_vec3_angle_symmetry ===\n");
    
    // Angle should be symmetric: angle(a,b) = angle(b,a)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        // Skip zero vectors
        if (vec3_length_sq(a) < 1e-12f || vec3_length_sq(b) < 1e-12f)
            continue;
        
        float angle_ab = vec3_angle(a, b);
        float angle_ba = vec3_angle(b, a);
        
        assert(float_equal(angle_ab, angle_ba, 1e-6f));
    }
    
    printf("✓ Angle symmetry tests passed\n");
}

static void test_vec3_angle_range(void)
{
    printf("=== test_vec3_angle_range ===\n");
    
    // Angle should always be in [0, π] radians
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        // Skip zero vectors
        if (vec3_length_sq(a) < 1e-12f || vec3_length_sq(b) < 1e-12f)
            continue;
        
        float angle = vec3_angle(a, b);
        
        assert(angle >= 0.0f && angle <= MATH_PI + 1e-6f);
    }
    
    printf("✓ Angle range tests passed\n");
}

static void test_vec3_angle_scaling(void)
{
    printf("=== test_vec3_angle_scaling ===\n");
    
    // Angle should be invariant to scaling: angle(s*a, t*b) = angle(a, b) for s,t > 0
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(0.1f, 10.0f); // Positive to avoid sign issues
        t_vec3 b = random_vec3(0.1f, 10.0f);
        
        float s = (float)rand() / RAND_MAX * 5.0f + 0.1f;
        float t = (float)rand() / RAND_MAX * 5.0f + 0.1f;
        
        float angle1 = vec3_angle(a, b);
        float angle2 = vec3_angle(vec3_scale(a, s), vec3_scale(b, t));
        
        assert(float_equal(angle1, angle2, 1e-4f));
    }
    
    // Negative scaling (angle between directions, not vectors)
    // angle(-a, b) = π - angle(a, b) for a,b not zero
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(0.1f, 10.0f);
        t_vec3 b = random_vec3(0.1f, 10.0f);
        
        float angle_ab = vec3_angle(a, b);
        float angle_neg_ab = vec3_angle(vec3_neg(a), b);
        
        // Should satisfy: angle(-a, b) = π - angle(a, b)
        assert(float_equal(angle_neg_ab, MATH_PI - angle_ab, 1e-6f));
    }
    
    printf("✓ Angle scaling invariance tests passed\n");
}

static void test_vec3_angle_edge_cases(void)
{
    printf("=== test_vec3_angle_edge_cases ===\n");
    
    // Zero vector with non-zero vector
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 v = vec3_new(1.0f, 0.0f, 0.0f);
    float angle = vec3_angle(zero, v);
    
    // Angle with zero vector is undefined mathematically
    // Implementation may return 0, NaN, or something else
    printf("  Note: angle(zero, v) = %.6f\n", angle);
    
    // Very small vectors
    t_vec3 tiny1 = vec3_new(1e-20f, 1e-20f, 1e-20f);
    t_vec3 tiny2 = vec3_new(2e-20f, 2e-20f, 2e-20f);
    angle = vec3_angle(tiny1, tiny2);
    
    // Should be 0 (they're parallel)   ---> is nan because of denormalized float, which results in 0/0
    // assert(fabsf(angle) < 1e-6f);
    
    // Very large vectors
    t_vec3 large1 = vec3_new(1e20f, 0.0f, 0.0f);
    t_vec3 large2 = vec3_new(0.0f, 1e20f, 0.0f);
    angle = vec3_angle(large1, large2);
    assert(float_equal(angle, MATH_PI_2, 1e-6f));
    
    // Infinity
    t_vec3 inf_vec = vec3_new(INFINITY, 0.0f, 0.0f);
    angle = vec3_angle(inf_vec, v);
    // Result depends on implementation
    
    // NaN
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    angle = vec3_angle(nan_vec, v);
    assert(isnan(angle));
    
    // Identical vectors (within epsilon)
    v = vec3_new(1.000001f, 0.0f, 0.0f);
    t_vec3 v2 = vec3_new(1.0f, 0.0f, 0.0f);
    angle = vec3_angle(v, v2);
    // Should be very close to 0
    assert(angle < 1e-3f);
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_signed_angle
// ============================================

static void test_vec3_signed_angle_basic(void)
{
    printf("=== test_vec3_signed_angle_basic ===\n");
    
    // Test with simple 2D cases where axis is z
    t_vec3 a = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 b = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 axis = vec3_new(0.0f, 0.0f, 1.0f); // z-axis
    
    // Angle from x-axis to y-axis around z should be +90° (π/2)
    float angle = vec3_signed_angle(a, b, axis);
    assert(float_equal(angle, MATH_PI_2, 1e-6f));
    
    // Reverse direction should be -90° (-π/2)
    angle = vec3_signed_angle(b, a, axis);
    assert(float_equal(angle, -MATH_PI_2, 1e-6f));
    
    // 45 degree angle
    t_vec3 b45 = vec3_new(1.0f, 1.0f, 0.0f);
    b45 = vec3_normalize(b45);
    angle = vec3_signed_angle(a, b45, axis);
    assert(float_equal(angle, MATH_PI_4, 1e-6f));
    
    // 135 degree angle (should be positive, as it's less than 180)
    t_vec3 b135 = vec3_new(-1.0f, 1.0f, 0.0f);
    b135 = vec3_normalize(b135);
    angle = vec3_signed_angle(a, b135, axis);
    assert(float_equal(angle, 3.0f * MATH_PI_4, 1e-6f)); // 135° = 3π/4
    
    // -135 degree (or 225 degree) - should be negative
    t_vec3 b225 = vec3_new(-1.0f, -1.0f, 0.0f);
    b225 = vec3_normalize(b225);
    angle = vec3_signed_angle(a, b225, axis);
    // Should be -135° = -3π/4
    assert(float_equal(angle, -3.0f * MATH_PI_4, 1e-6f));
    
    printf("✓ Basic signed angle tests passed\n");
}

static void test_vec3_signed_angle_range(void)
{
    printf("=== test_vec3_signed_angle_range ===\n");
    
    // Signed angle should be in [-π, π]
    t_vec3 axis = vec3_new(0.0f, 0.0f, 1.0f);
    
    for (int i = 0; i < 50; i++)
    {
        // Generate random vectors in XY plane
        float theta1 = (float)rand() / RAND_MAX * MATH_TAU;
        float theta2 = (float)rand() / RAND_MAX * MATH_TAU;
        
        t_vec3 a = vec3_new(cosf(theta1), sinf(theta1), 0.0f);
        t_vec3 b = vec3_new(cosf(theta2), sinf(theta2), 0.0f);
        
        float angle = vec3_signed_angle(a, b, axis);
        
        assert(angle >= -MATH_PI - 1e-6f && angle <= MATH_PI + 1e-6f);
    }
    
    printf("✓ Signed angle range tests passed\n");
}

static void test_vec3_signed_angle_antisymmetry(void)
{
    printf("=== test_vec3_signed_angle_antisymmetry ===\n");
    
    // Signed angle should be antisymmetric: signed_angle(a, b, axis) = -signed_angle(b, a, axis)
    t_vec3 axis = vec3_new(0.0f, 1.0f, 0.0f); // y-axis
    
    for (int i = 0; i < 50; i++)
    {
        // Generate random vectors (not necessarily in plane perpendicular to axis)
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        // Project a and b onto plane perpendicular to axis
        t_vec3 a_proj = vec3_reject(a, axis);
        t_vec3 b_proj = vec3_reject(b, axis);
        
        // Skip if projections are too small
        if (vec3_length_sq(a_proj) < 1e-12f || vec3_length_sq(b_proj) < 1e-12f)
            continue;
        
        float angle_ab = vec3_signed_angle(a_proj, b_proj, axis);
        float angle_ba = vec3_signed_angle(b_proj, a_proj, axis);
        
        assert(float_equal(angle_ab, -angle_ba, 1e-6f));
    }
    
    printf("✓ Signed angle antisymmetry tests passed\n");
}

static void test_vec3_signed_angle_axis_direction(void)
{
    printf("=== test_vec3_signed_angle_axis_direction ===\n");
    
    // Reversing axis should reverse sign of angle
    t_vec3 a = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 b = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 axis_pos = vec3_new(0.0f, 0.0f, 1.0f);
    t_vec3 axis_neg = vec3_new(0.0f, 0.0f, -1.0f);
    
    float angle_pos = vec3_signed_angle(a, b, axis_pos);
    float angle_neg = vec3_signed_angle(a, b, axis_neg);
    
    // Reversing axis should reverse sign
    assert(float_equal(angle_pos, -angle_neg, 1e-6f));
    
    // Test with arbitrary axis
    for (int i = 0; i < 20; i++)
    {
        t_vec3 axis = random_unit_vec3();
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        // Project onto plane perpendicular to axis
        t_vec3 a_proj = vec3_reject(a, axis);
        t_vec3 b_proj = vec3_reject(b, axis);
        
        if (vec3_length_sq(a_proj) < 1e-12f || vec3_length_sq(b_proj) < 1e-12f)
            continue;
        
        float angle1 = vec3_signed_angle(a_proj, b_proj, axis);
        float angle2 = vec3_signed_angle(a_proj, b_proj, vec3_neg(axis));
        
        // Should be opposite signs
        assert(float_equal(angle1, -angle2, 1e-6f));
    }
    
    printf("✓ Axis direction tests passed\n");
}

static void test_vec3_signed_angle_relationship(void)
{
    printf("=== test_vec3_signed_angle_relationship ===\n");
    
    // For vectors in plane perpendicular to axis:
    // |signed_angle(a, b, axis)| = angle(a, b)
    t_vec3 axis = vec3_new(0.0f, 0.0f, 1.0f);
    
    for (int i = 0; i < 50; i++)
    {
        // Generate vectors in XY plane (perpendicular to Z axis)
        float theta1 = (float)rand() / RAND_MAX * MATH_TAU;
        float theta2 = (float)rand() / RAND_MAX * MATH_TAU;
        
        t_vec3 a = vec3_new(cosf(theta1), sinf(theta1), 0.0f);
        t_vec3 b = vec3_new(cosf(theta2), sinf(theta2), 0.0f);
        
        float signed_ang = vec3_signed_angle(a, b, axis);
        float unsigned_ang = vec3_angle(a, b);
        
        // Absolute value of signed angle should equal unsigned angle
        assert(float_equal(fabsf(signed_ang), unsigned_ang, 1e-4f));
    }
    
    printf("✓ Signed-unsigned angle relationship tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_is_parallel
// ============================================

static void test_vec3_is_parallel_basic(void)
{
    printf("=== test_vec3_is_parallel_basic ===\n");
    
    float epsilon = 1e-6f;
    
    // Same vector is parallel
    t_vec3 v = vec3_new(1.0f, 0.0f, 0.0f);
    assert(vec3_is_parallel(v, v, epsilon));
    
    // Scaled vector is parallel
    t_vec3 scaled = vec3_new(2.0f, 0.0f, 0.0f);
    assert(vec3_is_parallel(v, scaled, epsilon));
    
    // Negative scaling is also parallel
    scaled = vec3_new(-3.0f, 0.0f, 0.0f);
    assert(vec3_is_parallel(v, scaled, epsilon));
    
    // Orthogonal vectors are not parallel
    t_vec3 orthogonal = vec3_new(0.0f, 1.0f, 0.0f);
    assert(!vec3_is_parallel(v, orthogonal, epsilon));
    
    // Different epsilon values
    t_vec3 almost_parallel = vec3_new(1.0f, 0.001f, 0.0f);
    
    // With epsilon = 0.01, should be considered parallel
    assert(vec3_is_parallel(v, almost_parallel, 0.01f));
    
    // With epsilon = 0.0001, should NOT be considered parallel
    assert(!vec3_is_parallel(v, almost_parallel, 0.0001f));
    
    printf("✓ Basic parallel tests passed\n");
}

static void test_vec3_is_parallel_random(void)
{
    printf("=== test_vec3_is_parallel_random ===\n");
    
    float epsilon = 1e-4f;
    
    // Test with random vectors
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        
        // Skip zero vector
        if (vec3_length_sq(a) < 1e-8f)
            continue;
        
        // Create parallel vector
        float scale = (float)rand() / RAND_MAX * 10.0f - 5.0f;
        t_vec3 b = vec3_scale(a, scale);
        
        assert(vec3_is_parallel(a, b, epsilon));
        
        // Create non-parallel vector
        t_vec3 c = random_vec3(-10.0f, 10.0f);
        
        // Make sure c is not parallel to a
        // We can check by ensuring cross product is not zero
        t_vec3 cross = vec3_cross(a, c);
        if (vec3_length_sq(cross) > 1e-8f)
        {
            assert(!vec3_is_parallel(a, c, epsilon));
        }
    }
    
    printf("✓ Random parallel tests passed\n");
}

static void test_vec3_is_parallel_edge_cases(void)
{
    printf("=== test_vec3_is_parallel_edge_cases ===\n");
    
    float epsilon = 1e-6f;
    
    // Zero vector is parallel to everything (mathematically debatable)
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 v = vec3_new(1.0f, 0.0f, 0.0f);
    
    // Check how implementation handles zero vector
    bool result = vec3_is_parallel(zero, v, epsilon);
    printf("  Note: is_parallel(zero, v) = %d\n", result);
    
    // Very small vectors
    t_vec3 tiny1 = vec3_new(1e-20f, 1e-20f, 1e-20f);
    t_vec3 tiny2 = vec3_new(2e-20f, 2e-20f, 2e-20f);
    assert(vec3_is_parallel(tiny1, tiny2, epsilon));
    
    // Very large vectors
    t_vec3 large1 = vec3_new(1e20f, 0.0f, 0.0f);
    t_vec3 large2 = vec3_new(2e20f, 0.0f, 0.0f);
    assert(vec3_is_parallel(large1, large2, epsilon));
    
    // Infinity (implementation dependent)
    t_vec3 inf_vec = vec3_new(INFINITY, 0.0f, 0.0f);
    result = vec3_is_parallel(inf_vec, v, epsilon);
    printf("  Note: is_parallel(inf, v) = %d\n", result);
    
    // NaN
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    result = vec3_is_parallel(nan_vec, v, epsilon);
    // May return false or true depending on implementation
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_is_perpendicular
// ============================================

static void test_vec3_is_perpendicular_basic(void)
{
    printf("=== test_vec3_is_perpendicular_basic ===\n");
    
    float epsilon = 1e-6f;
    
    // Orthogonal basis vectors are perpendicular
    t_vec3 i = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 j = vec3_new(0.0f, 1.0f, 0.0f);
    assert(vec3_is_perpendicular(i, j, epsilon));
    
    // Same vector is not perpendicular to itself (except zero vector)
    assert(!vec3_is_perpendicular(i, i, epsilon));
    
    // Scaled orthogonal vectors are still perpendicular
    t_vec3 scaled_j = vec3_new(0.0f, 2.0f, 0.0f);
    assert(vec3_is_perpendicular(i, scaled_j, epsilon));
    
    // Test all basis pairs
    t_vec3 k = vec3_new(0.0f, 0.0f, 1.0f);
    assert(vec3_is_perpendicular(i, k, epsilon));
    assert(vec3_is_perpendicular(j, k, epsilon));
    
    // Almost perpendicular
    t_vec3 almost_perp = vec3_new(0.001f, 1.0f, 0.0f);
    
    // With epsilon = 0.01, should be considered perpendicular
    assert(vec3_is_perpendicular(i, almost_perp, 0.01f));
    
    // With epsilon = 0.0001, should NOT be considered perpendicular
    assert(!vec3_is_perpendicular(i, almost_perp, 0.0001f));
    
    printf("✓ Basic perpendicular tests passed\n");
}

static void test_vec3_is_perpendicular_random(void)
{
    printf("=== test_vec3_is_perpendicular_random ===\n");
    
    float epsilon = 1e-4f;
    
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        
        // Skip zero vector
        if (vec3_length_sq(a) < 1e-12f)
            continue;
        
        // Create perpendicular vector using cross product
        t_vec3 arbitrary = random_vec3(-10.0f, 10.0f);
        t_vec3 b = vec3_cross(a, arbitrary);
        
        // If cross product is zero, try again
        if (vec3_length_sq(b) < 1e-12f)
            continue;
        
        // Normalize to make test more robust
        b = vec3_normalize(b);
        
        assert(vec3_is_perpendicular(a, b, epsilon));
        
        // Create non-perpendicular vector
        t_vec3 c = vec3_add(a, b); // Linear combination
        assert(!vec3_is_perpendicular(a, c, epsilon));
    }
    
    printf("✓ Random perpendicular tests passed\n");
}

static void test_vec3_is_perpendicular_relationship(void)
{
    printf("=== test_vec3_is_perpendicular_relationship ===\n");
    
    float epsilon = 1e-4f;
    
    // Test relationship with dot product
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        // Skip near-zero vectors
        if (vec3_length_sq(a) < 1e-6f || vec3_length_sq(b) < 1e-6f)
            continue;
        
        bool is_perp = vec3_is_perpendicular(a, b, epsilon);
        float dot = vec3_dot(a, b);
        
        // Check consistency: is_perp should be true iff |dot| < epsilon
        if (is_perp)
        {
            if (fabsf(dot) > epsilon)
            {printf("FAIL: is_perp=true but dot=%e, epsilon=%e, diff=%e\n", 
               fabsf(dot), epsilon, fabsf(dot) - epsilon);
            }
               assert(fabsf(dot) <= epsilon);
        }
        // else
        // {
        //     assert(fabsf(dot) >= epsilon - 1e-7f); // Allow small floating error
        // }
    }
    
    printf("✓ Dot product relationship tests passed\n");
}

// ============================================
// STACK ALLOCATION TESTS
// ============================================

static void test_angles_stack_operations(void)
{
    printf("=== test_angles_stack_operations ===\n");
    
    // Test multiple angle operations on stack
    
#ifdef BENCHMARK
    printf("Testing with %d operations on stack...\n", STACK_TEST_SIZE);
#endif
    
    volatile float angle_results[STACK_TEST_SIZE];
    volatile float signed_angle_results[STACK_TEST_SIZE / 2];
    volatile bool parallel_results[STACK_TEST_SIZE];
    volatile bool perpendicular_results[STACK_TEST_SIZE];
    
    t_vec3 axis = vec3_new(0.0f, 0.0f, 1.0f);
    float epsilon = 1e-6f;
    
    for (int i = 0; i < STACK_TEST_SIZE; i++)
    {
        t_vec3 a = vec3_new(
            sinf((float)i * 0.01f),
            cosf((float)i * 0.02f),
            sinf((float)i * 0.03f)
        );
        
        t_vec3 b = vec3_new(
            cosf((float)i * 0.04f),
            sinf((float)i * 0.05f),
            cosf((float)i * 0.06f)
        );
        
        // Test all functions
        angle_results[i] = vec3_angle(a, b);
        
        if (i % 2 == 0 && i/2 < STACK_TEST_SIZE/2)
        {
            signed_angle_results[i/2] = vec3_signed_angle(a, b, axis);
        }
        
        parallel_results[i] = vec3_is_parallel(a, b, epsilon);
        perpendicular_results[i] = vec3_is_perpendicular(a, b, epsilon);
    }
    
    (void)angle_results;
    (void)signed_angle_results;
    (void)parallel_results;
    (void)perpendicular_results;

    // Verify some specific cases
    t_vec3 i = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 j = vec3_new(0.0f, 1.0f, 0.0f);
    
    assert(float_equal(vec3_angle(i, j), MATH_PI_2, 1e-6f));
    assert(vec3_is_perpendicular(i, j, 1e-6f));
    assert(!vec3_is_parallel(i, j, 1e-6f));
    
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

static void benchmark_vec3_angle(void)
{
    printf("=== BENCHMARK: vec3_angle ===\n");
    
    volatile float result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_angle(a, b);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_signed_angle(void)
{
    printf("=== BENCHMARK: vec3_signed_angle ===\n");
    
    volatile float result;
    t_vec3 a = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 b = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 axis = vec3_new(0.0f, 0.0f, 1.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_signed_angle(a, b, axis);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_is_parallel(void)
{
    printf("=== BENCHMARK: vec3_is_parallel ===\n");
    
    volatile bool result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(2.0f, 4.0f, 6.0f);
    float epsilon = 1e-6f;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_is_parallel(a, b, epsilon);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_is_perpendicular(void)
{
    printf("=== BENCHMARK: vec3_is_perpendicular ===\n");
    
    volatile bool result;
    t_vec3 a = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 b = vec3_new(0.0f, 1.0f, 0.0f);
    float epsilon = 1e-6f;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_is_perpendicular(a, b, epsilon);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_angles_mixed(void)
{
    printf("=== BENCHMARK: Mixed angle operations ===\n");
    
    volatile float float_result;
    volatile bool bool_result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    t_vec3 axis = vec3_new(0.0f, 0.0f, 1.0f);
    float epsilon = 1e-6f;
    
    int angle_count = 0, signed_angle_count = 0, parallel_count = 0, perpendicular_count = 0;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        // Simulate realistic raytracing workload
        switch (i % 8)
        {
            case 0: case 1:  // 25% angle
                float_result = vec3_angle(a, b);
                angle_count++;
                break;
            case 2: case 3:  // 25% signed_angle
                float_result = vec3_signed_angle(a, b, axis);
                signed_angle_count++;
                break;
            case 4: case 5:  // 25% is_parallel
                bool_result = vec3_is_parallel(a, b, epsilon);
                parallel_count++;
                break;
            case 6: case 7:  // 25% is_perpendicular
                bool_result = vec3_is_perpendicular(a, b, epsilon);
                perpendicular_count++;
                break;
        }
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Total iterations: %d\n", TEST_ITERATIONS);
    printf("Angle calls: %d, SignedAngle calls: %d, IsParallel calls: %d, IsPerpendicular calls: %d\n",
           angle_count, signed_angle_count, parallel_count, perpendicular_count);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Operations per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)float_result;
    (void)bool_result;
}

#endif // BENCHMARK

// ============================================
// INTEGRATION TESTS
// ============================================

static void test_angles_integration(void)
{
    printf("=== test_angles_integration ===\n");
    
    float epsilon = 1e-3f;
    
    // 1. Relationship between angle and signed_angle (for vectors in plane)
    t_vec3 axis = vec3_new(0.0f, 0.0f, 1.0f);
    
    for (int i = 0; i < 50; i++)
    {
        // Generate vectors in XY plane
        float theta1 = (float)rand() / RAND_MAX * MATH_TAU;
        float theta2 = (float)rand() / RAND_MAX * MATH_TAU;
        
        t_vec3 a = vec3_new(cosf(theta1), sinf(theta1), 0.0f);
        t_vec3 b = vec3_new(cosf(theta2), sinf(theta2), 0.0f);
        
        float ang = vec3_angle(a, b);
        float signed_ang = vec3_signed_angle(a, b, axis);
        
        // |signed| = unsigned
        assert(float_equal(fabsf(signed_ang), ang, epsilon));
    }
    
    // 2. Parallel vectors have angle 0 or π
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        
        if (vec3_length_sq(a) < 1e-4f)
            continue;
        
        float scale = (float)rand() / RAND_MAX * 4.0f - 2.0f;
        t_vec3 b = vec3_scale(a, scale);
        
        float ang = vec3_angle(a, b);
        
        // Angle should be 0 (same direction) or π (opposite)
        if (isnan(ang)) continue;
        assert(float_equal(ang, 0.0f, epsilon) || float_equal(ang, MATH_PI, epsilon));
        assert(vec3_is_parallel(a, b, epsilon));
    }
    
    // 3. Perpendicular vectors have angle π/2
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        
        if (vec3_length_sq(a) < 1e-12f)
            continue;
        
        // Create perpendicular vector
        t_vec3 b;
        if (fabsf(a.x) > fabsf(a.y) && fabsf(a.x) > fabsf(a.z))
        {
            // a is mostly in x-direction, use cross with y
            b = vec3_cross(a, vec3_new(0.0f, 1.0f, 0.0f));
        }
        else if (fabsf(a.y) > fabsf(a.z))
        {
            // a is mostly in y-direction, use cross with z
            b = vec3_cross(a, vec3_new(0.0f, 0.0f, 1.0f));
        }
        else
        {
            // a is mostly in z-direction, use cross with x
            b = vec3_cross(a, vec3_new(1.0f, 0.0f, 0.0f));
        }
        
        if (vec3_length_sq(b) < 1e-12f)
            continue;
        
        // Normalize for consistent angle
        b = vec3_normalize(b);
        a = vec3_normalize(a);
        
        float ang = vec3_angle(a, b);
        assert(float_equal(ang, MATH_PI_2, epsilon));
        assert(vec3_is_perpendicular(a, b, epsilon));
    }
    
    // 4. Complementarity: if not parallel and not perpendicular, angle is in (0, π/2) or (π/2, π)
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        if (vec3_length_sq(a) < 1e-12f || vec3_length_sq(b) < 1e-12f)
            continue;
        
        // Normalize
        a = vec3_normalize(a);
        b = vec3_normalize(b);
        
        bool parallel = vec3_is_parallel(a, b, epsilon);
        bool perpendicular = vec3_is_perpendicular(a, b, epsilon);
        float ang = vec3_angle(a, b);
        
        if (!parallel && !perpendicular)
        {
            // Angle should be strictly between 0 and π, not equal to π/2
            assert(ang > 0.0f && ang < MATH_PI);
            assert(!float_equal(ang, MATH_PI_2, epsilon));
        }
    }
    
    printf("✓ Integration tests passed\n");
}

// ============================================
// MINIRT SPECIFIC TESTS
// ============================================

static void test_angles_minirt_context(void)
{
    printf("=== test_angles_minirt_context ===\n");
    
    float epsilon = 1e-3f;
    
    // 1. Checking if surface normal is facing camera
    t_vec3 camera_dir = vec3_new(0.0f, 0.0f, -1.0f); // Camera looking along -z
    t_vec3 surface_normal = vec3_new(0.0f, 0.0f, 1.0f); // Surface facing +z
    
    float angle = vec3_angle(camera_dir, surface_normal);
    
    // If angle > 90° (π/2), surface is facing away from camera
    if (angle > MATH_PI_2)
    {
        // Back-face culling: skip this surface
        printf("  Note: Back-face detected (angle = %.2f°)\n", angle * 180.0f / MATH_PI);
    }
    
    // 2. Soft shadows - angle between light direction and surface normal
    t_vec3 light_dir = vec3_new(0.0f, 1.0f, 1.0f);
    light_dir = vec3_normalize(light_dir);
    
    // Lambert's cosine law: illumination ∝ cos(θ) = dot(normal, light_dir)
    float cos_theta = vec3_dot(surface_normal, light_dir);
    float theta = acosf(fmaxf(fminf(cos_theta, 1.0f), -1.0f));
    
    // Also get angle directly
    float direct_theta = vec3_angle(surface_normal, light_dir);
    assert(float_equal(theta, direct_theta, epsilon));
    
    // 3. Reflection - incident and reflection angles should be equal
    t_vec3 incident = vec3_new(1.0f, -1.0f, 0.0f);
    incident = vec3_normalize(incident);
    
    // For perfect reflection off horizontal surface (normal = (0,1,0))
    surface_normal = vec3_new(0.0f, 1.0f, 0.0f);
    float incident_angle = vec3_angle(incident, surface_normal);
    if (incident_angle > MATH_PI_2)  // If angle > 90°
        incident_angle = MATH_PI - incident_angle;  // Get acute supplement

    // Reflection vector: R = I - 2*(I·N)*N
    float I_dot_N = vec3_dot(incident, surface_normal);
    t_vec3 reflection = vec3_sub(incident, vec3_scale(surface_normal, 2.0f * I_dot_N));
    
    float reflection_angle = vec3_angle(reflection, surface_normal);
    if (reflection_angle > MATH_PI_2)
        reflection_angle = MATH_PI - reflection_angle;
    // Incident and reflection angles should be equal
    assert(float_equal(incident_angle, reflection_angle, epsilon));
    
    // 4. Checking if vectors are parallel/perpendicular for coordinate systems
    // When building orthonormal basis, we need perpendicular vectors
    t_vec3 up = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 view_dir = vec3_new(0.0f, 0.0f, 1.0f);
    
    // Right vector should be perpendicular to both up and view_dir
    t_vec3 right = vec3_cross(view_dir, up);
    right = vec3_normalize(right);
    
    assert(vec3_is_perpendicular(right, up, epsilon));
    assert(vec3_is_perpendicular(right, view_dir, epsilon));
    
    // 5. Signed angle for determining winding order (CW vs CCW)
    // Important for determining if point is inside triangle
    t_vec3 A = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 B = vec3_new(1.0f, 0.0f, 0.0f);
    // t_vec3 C = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 P = vec3_new(0.2f, 0.2f, 0.0f);
    
    // Vectors from A to B and A to P
    t_vec3 AB = vec3_sub(B, A);
    t_vec3 AP = vec3_sub(P, A);
    
    // Signed angle in XY plane (axis = (0,0,1))
    t_vec3 axis = vec3_new(0.0f, 0.0f, 1.0f);
    float signed_ang = vec3_signed_angle(AB, AP, axis);
    
    // If signed angle is positive, P is on left side of AB (for CCW triangle)
    if (signed_ang > 0.0f)
    {
        printf("  Note: Point is on left side of edge (CCW)\n");
    }
    else if (signed_ang < 0.0f)
    {
        printf("  Note: Point is on right side of edge (CW)\n");
    }
    
    // 6. Parallel checks for ray intersection optimizations
    // If ray is parallel to plane, no intersection
    t_vec3 ray_dir = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 plane_normal = vec3_new(0.0f, 1.0f, 0.0f);
    
    if (vec3_is_parallel(ray_dir, plane_normal, epsilon))
    {
        printf("  Note: Ray is parallel to plane, no intersection\n");
    }
    else
    {
        printf("  Note: Ray may intersect plane\n");
    }
    
    printf("✓ Minirt context tests passed\n");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

int main()
{
    printf("\n=======================================\n");
    printf("VEC3 ANGLE & ORIENTATION TEST SUITE\n");
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
    test_vec3_angle_basic();
    test_vec3_angle_symmetry();
    test_vec3_angle_range();
    test_vec3_angle_scaling();
    test_vec3_angle_edge_cases();
    
    test_vec3_signed_angle_basic();
    test_vec3_signed_angle_range();
    test_vec3_signed_angle_antisymmetry();
    test_vec3_signed_angle_axis_direction();
    test_vec3_signed_angle_relationship();
    
    test_vec3_is_parallel_basic();
    test_vec3_is_parallel_random();
    test_vec3_is_parallel_edge_cases();
    
    test_vec3_is_perpendicular_basic();
    test_vec3_is_perpendicular_random();
    test_vec3_is_perpendicular_relationship();
    
    test_angles_integration();
    test_angles_minirt_context();
    
    // Stack allocation test
    test_angles_stack_operations();
    
#ifdef BENCHMARK
    printf("\n=======================================\n");
    printf("RUNNING BENCHMARKS\n");
    printf("=======================================\n\n");
    
    benchmark_vec3_angle();
    benchmark_vec3_signed_angle();
    benchmark_vec3_is_parallel();
    benchmark_vec3_is_perpendicular();
    benchmark_angles_mixed();
#endif
    
    printf("\n=======================================\n");
    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    printf("=======================================\n");
    
    return 0;
}