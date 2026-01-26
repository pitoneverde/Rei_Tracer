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
// UNIT TESTS - vec3_coordinate_system
// ============================================

static void test_vec3_coordinate_system_basic(void)
{
    printf("=== test_vec3_coordinate_system_basic ===\n");
    
    // Test with standard basis vectors
    
    // X-axis
    t_vec3 a1 = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 b1, c1;
    vec3_coordinate_system(a1, &b1, &c1);
    
    // Check orthogonality
    assert(float_equal(vec3_dot(a1, b1), 0.0f, 1e-6f));
    assert(float_equal(vec3_dot(a1, c1), 0.0f, 1e-6f));
    assert(float_equal(vec3_dot(b1, c1), 0.0f, 1e-6f));
    
    // Check unit length
    assert(float_equal(vec3_length(b1), 1.0f, 1e-6f));
    assert(float_equal(vec3_length(c1), 1.0f, 1e-6f));
    
    // Check right-handedness: a = b × c
    t_vec3 cross_bc = vec3_cross(b1, c1);
    assert(vec3_equal(cross_bc, a1, 1e-6f));
    
    // Y-axis
    t_vec3 a2 = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 b2, c2;
    vec3_coordinate_system(a2, &b2, &c2);
    
    assert(float_equal(vec3_dot(a2, b2), 0.0f, 1e-6f));
    assert(float_equal(vec3_dot(a2, c2), 0.0f, 1e-6f));
    assert(float_equal(vec3_dot(b2, c2), 0.0f, 1e-6f));
    assert(float_equal(vec3_length(b2), 1.0f, 1e-6f));
    assert(float_equal(vec3_length(c2), 1.0f, 1e-6f));
    
    cross_bc = vec3_cross(b2, c2);
    assert(vec3_equal(cross_bc, a2, 1e-6f));
    
    // Z-axis
    t_vec3 a3 = vec3_new(0.0f, 0.0f, 1.0f);
    t_vec3 b3, c3;
    vec3_coordinate_system(a3, &b3, &c3);
    
    assert(float_equal(vec3_dot(a3, b3), 0.0f, 1e-6f));
    assert(float_equal(vec3_dot(a3, c3), 0.0f, 1e-6f));
    assert(float_equal(vec3_dot(b3, c3), 0.0f, 1e-6f));
    assert(float_equal(vec3_length(b3), 1.0f, 1e-6f));
    assert(float_equal(vec3_length(c3), 1.0f, 1e-6f));
    
    cross_bc = vec3_cross(b3, c3);
    assert(vec3_equal(cross_bc, a3, 1e-6f));
    
    printf("✓ Basic coordinate system tests passed\n");
}

static void test_vec3_coordinate_system_random_directions(void)
{
    printf("=== test_vec3_coordinate_system_random_directions ===\n");
    
    // Test with random unit vectors
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_unit_vec3();
        t_vec3 b, c;
        vec3_coordinate_system(a, &b, &c);
        
        // 1. Orthogonality
        float dot_ab = vec3_dot(a, b);
        float dot_ac = vec3_dot(a, c);
        float dot_bc = vec3_dot(b, c);
        
        assert(fabsf(dot_ab) < 1e-6f);
        assert(fabsf(dot_ac) < 1e-6f);
        assert(fabsf(dot_bc) < 1e-6f);
        
        // 2. Unit length (b and c should be normalized)
        float len_b = vec3_length(b);
        float len_c = vec3_length(c);
        
        assert(float_equal(len_b, 1.0f, 1e-6f));
        assert(float_equal(len_c, 1.0f, 1e-6f));
        
        // 3. Right-handed coordinate system: a = b × c
        t_vec3 cross_bc = vec3_cross(b, c);
        assert(vec3_equal(cross_bc, a, 1e-6f));
        
        // 4. Also check other cross products for consistency
        t_vec3 cross_ca = vec3_cross(c, a);
        assert(vec3_equal(cross_ca, b, 1e-6f));
        
        t_vec3 cross_ab = vec3_cross(a, b);
        assert(vec3_equal(cross_ab, c, 1e-6f));
    }
    
    printf("✓ Random direction tests passed\n");
}

static void test_vec3_coordinate_system_non_unit_input(void)
{
    printf("=== test_vec3_coordinate_system_non_unit_input ===\n");
    
    // The function should handle non-unit vectors (it will normalize internally or not?)
    // Let's test with vectors of various lengths
    
    for (int i = 0; i < 50; i++)
    {
        // Random vector with random length
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        
        // Skip zero vector
        if (vec3_length_sq(a) < 1e-12f)
            continue;
        
        t_vec3 b, c;
        vec3_coordinate_system(a, &b, &c);
        
        // Even if a is not unit, b and c should be orthogonal to a
        float dot_ab = vec3_dot(a, b);
        float dot_ac = vec3_dot(a, c);
        
        assert(fabsf(dot_ab) < 1e-6f);
        assert(fabsf(dot_ac) < 1e-6f);
        
        // b and c should be unit vectors
        assert(float_equal(vec3_length(b), 1.0f, 1e-6f));
        assert(float_equal(vec3_length(c), 1.0f, 1e-6f));
        
        // They should form a right-handed system with a (normalized)
        t_vec3 a_norm = vec3_normalize(a);
        t_vec3 cross_bc = vec3_cross(b, c);
        
        // cross(b,c) should be parallel to a (might be opposite direction)
        // Check if they're parallel (cross product should be zero)
        t_vec3 cross_check = vec3_cross(cross_bc, a_norm);
        assert(vec3_equal(cross_check, vec3_new(0.0f, 0.0f, 0.0f), 1e-6f));
        
        // And they should point in the same direction (dot product positive)
        float direction_dot = vec3_dot(cross_bc, a_norm);
        assert(direction_dot > 0.0f);
    }
    
    printf("✓ Non-unit input tests passed\n");
}

static void test_vec3_coordinate_system_consistency(void)
{
    printf("=== test_vec3_coordinate_system_consistency ===\n");
    
    // Test that multiple calls with same input produce consistent results
    // (not necessarily identical, but should have same properties)
    
    t_vec3 a = random_unit_vec3();
    
    t_vec3 b1, c1, b2, c2;
    vec3_coordinate_system(a, &b1, &c1);
    vec3_coordinate_system(a, &b2, &c2);
    
    // Both should be orthonormal bases
    // Check that both are valid
    
    // First set
    assert(fabsf(vec3_dot(a, b1)) < 1e-6f);
    assert(fabsf(vec3_dot(a, c1)) < 1e-6f);
    assert(fabsf(vec3_dot(b1, c1)) < 1e-6f);
    assert(float_equal(vec3_length(b1), 1.0f, 1e-6f));
    assert(float_equal(vec3_length(c1), 1.0f, 1e-6f));
    
    // Second set
    assert(fabsf(vec3_dot(a, b2)) < 1e-6f);
    assert(fabsf(vec3_dot(a, c2)) < 1e-6f);
    assert(fabsf(vec3_dot(b2, c2)) < 1e-6f);
    assert(float_equal(vec3_length(b2), 1.0f, 1e-6f));
    assert(float_equal(vec3_length(c2), 1.0f, 1e-6f));
    
    // They might not be identical due to different arbitrary choices
    // but they should both be valid orthonormal bases
    
    // Test multiple random vectors
    for (int i = 0; i < 20; i++)
    {
        a = random_unit_vec3();
        
        t_vec3 b[5], c[5];
        for (int j = 0; j < 5; j++)
        {
            vec3_coordinate_system(a, &b[j], &c[j]);
            
            // Verify each is valid
            assert(fabsf(vec3_dot(a, b[j])) < 1e-6f);
            assert(fabsf(vec3_dot(a, c[j])) < 1e-6f);
            assert(fabsf(vec3_dot(b[j], c[j])) < 1e-6f);
            assert(float_equal(vec3_length(b[j]), 1.0f, 1e-6f));
            assert(float_equal(vec3_length(c[j]), 1.0f, 1e-6f));
        }
    }
    
    printf("✓ Consistency tests passed\n");
}

static void test_vec3_coordinate_system_edge_cases(void)
{
    printf("=== test_vec3_coordinate_system_edge_cases ===\n");
    
    // Test edge cases
    
    // Near-zero vector (should handle gracefully or crash)
    t_vec3 tiny = vec3_new(1e-20f, 1e-20f, 1e-20f);
    t_vec3 b, c;
    
    // This might produce NaN or zero vectors, or might normalize
    vec3_coordinate_system(tiny, &b, &c);
    printf("  Note: tiny vector result - b: (%.6f, %.6f, %.6f), c: (%.6f, %.6f, %.6f)\n",
           b.x, b.y, b.z, c.x, c.y, c.z);
    
    // Vector with one component zero
    // t_vec3 a1 = vec3_new(0.0f, 0.0f, 1.0f); // Already tested
    t_vec3 a2 = vec3_new(1.0f, 1.0f, 0.0f);
    a2 = vec3_normalize(a2);
    
    vec3_coordinate_system(a2, &b, &c);
    assert(fabsf(vec3_dot(a2, b)) < 1e-6f);
    assert(fabsf(vec3_dot(a2, c)) < 1e-6f);
    assert(fabsf(vec3_dot(b, c)) < 1e-6f);
    
    // Vector aligned with canonical axes but with negative sign
    t_vec3 neg_z = vec3_new(0.0f, 0.0f, -1.0f);
    vec3_coordinate_system(neg_z, &b, &c);
    
    // Should still be orthonormal and right-handed
    assert(fabsf(vec3_dot(neg_z, b)) < 1e-6f);
    assert(fabsf(vec3_dot(neg_z, c)) < 1e-6f);
    assert(fabsf(vec3_dot(b, c)) < 1e-6f);
    assert(float_equal(vec3_length(b), 1.0f, 1e-6f));
    assert(float_equal(vec3_length(c), 1.0f, 1e-6f));
    
    // Check right-handedness: a = b × c
    t_vec3 cross_bc = vec3_cross(b, c);
    assert(vec3_equal(cross_bc, neg_z, 1e-6f));
    
    printf("✓ Edge cases tests passed\n");
}

static void test_vec3_coordinate_system_degenerate_cases(void)
{
    printf("=== test_vec3_coordinate_system_degenerate_cases ===\n");
    
    // Test potentially problematic cases
    
    // Vector with two components zero
    t_vec3 cases[] = {
        vec3_new(1.0f, 0.0f, 0.0f),
        vec3_new(0.0f, 1.0f, 0.0f),
        vec3_new(0.0f, 0.0f, 1.0f),
        vec3_new(-1.0f, 0.0f, 0.0f),
        vec3_new(0.0f, -1.0f, 0.0f),
        vec3_new(0.0f, 0.0f, -1.0f),
    };
    
    for (int i = 0; i < 6; i++)
    {
        t_vec3 b, c;
        vec3_coordinate_system(cases[i], &b, &c);
        
        // Verify orthonormal
        assert(fabsf(vec3_dot(cases[i], b)) < 1e-6f);
        assert(fabsf(vec3_dot(cases[i], c)) < 1e-6f);
        assert(fabsf(vec3_dot(b, c)) < 1e-6f);
        assert(float_equal(vec3_length(b), 1.0f, 1e-6f));
        assert(float_equal(vec3_length(c), 1.0f, 1e-6f));
        
        // Right-handed
        t_vec3 cross_bc = vec3_cross(b, c);
        assert(vec3_equal(cross_bc, cases[i], 1e-6f));
    }
    
    // Vector with repeated components
    t_vec3 repeated = vec3_new(1.0f, 1.0f, 1.0f);
    repeated = vec3_normalize(repeated);
    
    t_vec3 b, c;
    vec3_coordinate_system(repeated, &b, &c);
    
    assert(fabsf(vec3_dot(repeated, b)) < 1e-6f);
    assert(fabsf(vec3_dot(repeated, c)) < 1e-6f);
    assert(fabsf(vec3_dot(b, c)) < 1e-6f);
    assert(float_equal(vec3_length(b), 1.0f, 1e-6f));
    assert(float_equal(vec3_length(c), 1.0f, 1e-6f));
    
    t_vec3 cross_bc = vec3_cross(b, c);
    assert(vec3_equal(cross_bc, repeated, 1e-6f));
    
    printf("✓ Degenerate cases tests passed\n");
}

// ============================================
// STACK ALLOCATION TESTS
// ============================================

static void test_coordinates_stack_operations(void)
{
    printf("=== test_coordinates_stack_operations ===\n");
    
    // Test multiple coordinate system constructions on stack
    
#ifdef BENCHMARK
    printf("Testing with %d operations on stack...\n", STACK_TEST_SIZE);
#endif
    
    volatile t_vec3 b_results[STACK_TEST_SIZE];
    volatile t_vec3 c_results[STACK_TEST_SIZE];
    
    for (int i = 0; i < STACK_TEST_SIZE; i++)
    {
        t_vec3 a = vec3_new(
            sinf((float)i * 0.01f),
            cosf((float)i * 0.02f),
            sinf((float)i * 0.03f)
        );
        
        // Normalize to ensure it's a valid direction
        if (vec3_length_sq(a) > 1e-12f)
        {
            a = vec3_normalize(a);
        }
        else
        {
            a = vec3_new(0.0f, 0.0f, 1.0f); // Fallback
        }
        
        t_vec3 b, c;
        vec3_coordinate_system(a, &b, &c);
        
        // Store results
        b_results[i] = b;
        c_results[i] = c;
        
        // Verify occasionally
        if (i % 1000 == 0)
        {
            assert(fabsf(vec3_dot(a, b)) < 1e-6f);
            assert(fabsf(vec3_dot(a, c)) < 1e-6f);
            assert(fabsf(vec3_dot(b, c)) < 1e-6f);
        }
    }
    
    // Verify a few specific cases
    t_vec3 a = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 b, c;
    vec3_coordinate_system(a, &b, &c);
    
    assert(fabsf(vec3_dot(a, b)) < 1e-6f);
    assert(fabsf(vec3_dot(a, c)) < 1e-6f);
    assert(fabsf(vec3_dot(b, c)) < 1e-6f);
    
    (void)b_results;
    (void)c_results;
    printf("✓ Stack operations test passed (%d coordinate systems)\n", STACK_TEST_SIZE);
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

static void benchmark_vec3_coordinate_system(void)
{
    printf("=== BENCHMARK: vec3_coordinate_system ===\n");
    
    volatile t_vec3 b_result, c_result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    a = vec3_normalize(a);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        // Slightly modify direction each time to avoid cache effects
        float angle = (float)i * 0.0001f;
        t_vec3 a_mod = vec3_new(
            a.x * cosf(angle) - a.y * sinf(angle),
            a.x * sinf(angle) + a.y * cosf(angle),
            a.z
        );
        a_mod = vec3_normalize(a_mod);
        
        vec3_coordinate_system(a_mod, &b_result, &c_result);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)b_result;
    (void)c_result;
}

#endif // BENCHMARK

// ============================================
// INTEGRATION TESTS
// ============================================

static void test_coordinates_integration(void)
{
    printf("=== test_coordinates_integration ===\n");
    
    // Test integration with other vector operations
    
    // 1. Transform vector from local to world coordinates
    // Given orthonormal basis (a, b, c), any vector v can be expressed as:
    // v = (v·a)*a + (v·b)*b + (v·c)*c
    
    for (int i = 0; i < 50; i++)
    {
        // Create random orthonormal basis
        t_vec3 a = random_unit_vec3();
        t_vec3 b, c;
        vec3_coordinate_system(a, &b, &c);
        
        // Random vector in world space
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        
        // Express v in the basis (a, b, c)
        float va = vec3_dot(v, a);
        float vb = vec3_dot(v, b);
        float vc = vec3_dot(v, c);
        
        // Reconstruct v from its components
        t_vec3 v_reconstructed = vec3_add(
            vec3_scale(a, va),
            vec3_add(
                vec3_scale(b, vb),
                vec3_scale(c, vc)
            )
        );
        
        // Should be equal
        assert(vec3_equal(v, v_reconstructed, 1e-6f));
    }
    
    // 2. Change of basis: transform vector from one basis to another
    for (int i = 0; i < 20; i++)
    {
        // Create two random orthonormal bases
        t_vec3 a1 = random_unit_vec3();
        t_vec3 b1, c1;
        vec3_coordinate_system(a1, &b1, &c1);
        
        t_vec3 a2 = random_unit_vec3();
        t_vec3 b2, c2;
        vec3_coordinate_system(a2, &b2, &c2);
        
        // Random vector
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        
        // Express v in basis1
        float v1_a = vec3_dot(v, a1);
        float v1_b = vec3_dot(v, b1);
        float v1_c = vec3_dot(v, c1);
        
        // Express v in basis2
        float v2_a = vec3_dot(v, a2);
        float v2_b = vec3_dot(v, b2);
        float v2_c = vec3_dot(v, c2);
        
        // Reconstruct from both bases - should give same vector
        t_vec3 v_from_basis1 = vec3_add(
            vec3_scale(a1, v1_a),
            vec3_add(
                vec3_scale(b1, v1_b),
                vec3_scale(c1, v1_c)
            )
        );
        
        t_vec3 v_from_basis2 = vec3_add(
            vec3_scale(a2, v2_a),
            vec3_add(
                vec3_scale(b2, v2_b),
                vec3_scale(c2, v2_c)
            )
        );
        
        // Both should equal original v
        assert(vec3_equal(v, v_from_basis1, 1e-6f));
        assert(vec3_equal(v, v_from_basis2, 1e-6f));
    }
    
    // 3. Test that basis vectors can be used for rotation
    // The matrix [a b c] is a rotation matrix (orthonormal, determinant +1)
    for (int i = 0; i < 20; i++)
    {
        t_vec3 a = random_unit_vec3();
        t_vec3 b, c;
        vec3_coordinate_system(a, &b, &c);
        
        // Check determinant of rotation matrix [a b c] should be +1
        float det = vec3_volume(a, b, c); // a · (b × c)
        assert(float_equal(det, 1.0f, 1e-6f));
    }
    
    printf("✓ Integration tests passed\n");
}

// ============================================
// MINIRT SPECIFIC TESTS
// ============================================

static void test_coordinates_minirt_context(void)
{
    printf("=== test_coordinates_minirt_context ===\n");
    
    // 1. Building camera coordinate system
    // In raytracing, we often build a coordinate system from view direction
    t_vec3 view_dir = vec3_new(0.0f, 0.0f, -1.0f); // Looking along -Z
    t_vec3 up = vec3_new(0.0f, 1.0f, 0.0f);       // World up

    // Usually we compute: right = cross(view_dir, up), then up = cross(right, view_dir)
    // But vec3_coordinate_system gives us an orthonormal basis from view_dir
    
    t_vec3 right, camera_up;
    vec3_coordinate_system(view_dir, &right, &camera_up);
    
    // Verify it's orthonormal
    assert(fabsf(vec3_dot(view_dir, right)) < 1e-6f);
    assert(fabsf(vec3_dot(view_dir, camera_up)) < 1e-6f);
    assert(fabsf(vec3_dot(right, camera_up)) < 1e-6f);
    
    // Right should point in positive X for right-handed system with view_dir = -Z, up = Y
    // Actually: view_dir = -Z, right = X, up = Y
    t_vec3 expected_right = vec3_new(1.0f, 0.0f, 0.0f);
    t_vec3 expected_up = vec3_new(0.0f, 1.0f, 0.0f);
    
    // Check if they match (might be opposite signs)
    float right_dot = vec3_dot(right, expected_right);
    float up_dot = vec3_dot(camera_up, expected_up);
    
    // Should be approximately ±1
    assert(fabsf(fabsf(right_dot) - 1.0f) < 1e-6f);
    assert(fabsf(fabsf(up_dot) - 1.0f) < 1e-6f);
    
    // 2. Tangent space for normal mapping
    // For a surface point, we need tangent (T), bitangent (B), and normal (N)
    t_vec3 normal = vec3_new(0.0f, 1.0f, 0.0f); // Surface normal (up)
    
    // Use coordinate_system to get tangent and bitangent
    t_vec3 tangent, bitangent;
    vec3_coordinate_system(normal, &tangent, &bitangent);
    
    // For normal mapping, TBN matrix should be orthonormal
    assert(fabsf(vec3_dot(normal, tangent)) < 1e-6f);
    assert(fabsf(vec3_dot(normal, bitangent)) < 1e-6f);
    assert(fabsf(vec3_dot(tangent, bitangent)) < 1e-6f);
    
    // Check right-handed: N = T × B
    t_vec3 cross_tb = vec3_cross(tangent, bitangent);
    assert(vec3_equal(cross_tb, normal, 1e-6f));
    
    // 3. Sampling directions in local hemisphere
    // When sampling directions around a normal, we often use a local coordinate system
    
    // 4. Building orthonormal basis for BRDF sampling
    // Many BRDFs sample directions in a local frame aligned with the surface normal
    
    // 5. Coordinate system for anisotropic materials
    // Anisotropic BRDFs need tangent and bitangent directions
    
    // 6. Transforming rays into local object space
    // For instancing or object transformations
    
    // 7. Building basis from reflection direction
    t_vec3 reflect_dir = vec3_new(0.0f, 1.0f, 0.0f); // Reflected ray
    t_vec3 u, v;
    vec3_coordinate_system(reflect_dir, &u, &v);
    
    // Useful for sampling around reflection direction
    
    // 8. Coordinate system for area lights
    // To sample points on area lights, we need a coordinate system on the light surface
    
    (void)up;

    printf("✓ Minirt context tests passed\n");
}

// ============================================
// ALTERNATIVE IMPLEMENTATION COMPARISON
// ============================================

static void test_coordinate_system_alternatives(void)
{
    printf("=== test_coordinate_system_alternatives ===\n");
    
    // Common method: Frisvad's method (robust and fast)
    // We can compare our implementation's properties
    
    for (int i = 0; i < 20; i++)
    {
        t_vec3 a = random_unit_vec3();
        t_vec3 b, c;
        vec3_coordinate_system(a, &b, &c);
        
        // Check that b and c are not zero
        assert(vec3_length_sq(b) > 0.1f);
        assert(vec3_length_sq(c) > 0.1f);
        
        // Check that basis is not left-handed (determinant should be +1, not -1)
        float det = vec3_volume(a, b, c); // a · (b × c)
        assert(det > 0.0f); // Should be +1, but allow small error
        assert(fabsf(det - 1.0f) < 1e-6f);
        
        // Alternative: check that a, b, c are linearly independent
        // The triple product (volume) should not be zero
        assert(fabsf(det) > 0.5f); // Should be close to 1
    }
    
    // Test stability for vectors near canonical axes
    float small = 1e-6f;
    t_vec3 near_axes[] = {
        vec3_new(1.0f, small, small),
        vec3_new(small, 1.0f, small),
        vec3_new(small, small, 1.0f),
        vec3_new(-1.0f, small, small),
        vec3_new(small, -1.0f, small),
        vec3_new(small, small, -1.0f),
    };
    
    for (int i = 0; i < 6; i++)
    {
        t_vec3 a = near_axes[i];
        a = vec3_normalize(a); // Normalize for consistency
        
        t_vec3 b, c;
        vec3_coordinate_system(a, &b, &c);
        
        // Should still be orthonormal
        assert(fabsf(vec3_dot(a, b)) < 1e-5f); // Slightly larger tolerance
        assert(fabsf(vec3_dot(a, c)) < 1e-5f);
        assert(fabsf(vec3_dot(b, c)) < 1e-5f);
        
        // b and c should be reasonable (not NaN or huge)
        assert(!isnan(b.x) && !isnan(b.y) && !isnan(b.z));
        assert(!isnan(c.x) && !isnan(c.y) && !isnan(c.z));
    }
    
    printf("✓ Alternative implementation comparison passed\n");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

int main()
{
    printf("\n=======================================\n");
    printf("VEC3 COORDINATE SYSTEM TEST SUITE\n");
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
    test_vec3_coordinate_system_basic();
    test_vec3_coordinate_system_random_directions();
    test_vec3_coordinate_system_non_unit_input();
    test_vec3_coordinate_system_consistency();
    test_vec3_coordinate_system_edge_cases();
    test_vec3_coordinate_system_degenerate_cases();
    
    test_coordinates_integration();
    test_coordinates_minirt_context();
    test_coordinate_system_alternatives();
    
    // Stack allocation test
    test_coordinates_stack_operations();
    
#ifdef BENCHMARK
    printf("\n=======================================\n");
    printf("RUNNING BENCHMARKS\n");
    printf("=======================================\n\n");
    
    benchmark_vec3_coordinate_system();
#endif
    
    printf("\n=======================================\n");
    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    printf("=======================================\n");
    
    return 0;
}