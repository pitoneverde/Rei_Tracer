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

// static bool float_equal(float a, float b, float epsilon)
// {
//     return fabsf(a - b) <= epsilon;
// }

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
// UNIT TESTS - vec3_mul_comp
// ============================================

static void test_vec3_mul_comp_basic(void)
{
    printf("=== test_vec3_mul_comp_basic ===\n");
    
    // Basic component-wise multiplication
    t_vec3 a = vec3_new(2.0f, 3.0f, 4.0f);
    t_vec3 b = vec3_new(5.0f, 6.0f, 7.0f);
    t_vec3 result = vec3_mul_comp(a, b);
    t_vec3 expected = vec3_new(10.0f, 18.0f, 28.0f);
    
    assert(vec3_equal(result, expected, 1e-6f));
    
    // Multiplication by one (identity)
    t_vec3 ones = vec3_new(1.0f, 1.0f, 1.0f);
    result = vec3_mul_comp(a, ones);
    assert(vec3_equal(result, a, 1e-6f));
    
    // Multiplication by zero
    t_vec3 zeros = vec3_new(0.0f, 0.0f, 0.0f);
    result = vec3_mul_comp(a, zeros);
    assert(vec3_equal(result, zeros, 1e-6f));
    
    // Negative numbers
    a = vec3_new(2.0f, -3.0f, 4.0f);
    b = vec3_new(-5.0f, 6.0f, -7.0f);
    result = vec3_mul_comp(a, b);
    expected = vec3_new(-10.0f, -18.0f, -28.0f);
    assert(vec3_equal(result, expected, 1e-6f));
    
    printf("✓ Basic component-wise multiplication tests passed\n");
}

static void test_vec3_mul_comp_commutative(void)
{
    printf("=== test_vec3_mul_comp_commutative ===\n");
    
    // Component-wise multiplication is commutative: a*b = b*a
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        t_vec3 result1 = vec3_mul_comp(a, b);
        t_vec3 result2 = vec3_mul_comp(b, a);
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    printf("✓ Commutative property tests passed\n");
}

static void test_vec3_mul_comp_associative(void)
{
    printf("=== test_vec3_mul_comp_associative ===\n");
    
    // Component-wise multiplication is associative: (a*b)*c = a*(b*c)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        t_vec3 c = random_vec3(-10.0f, 10.0f);
        
        t_vec3 result1 = vec3_mul_comp(vec3_mul_comp(a, b), c);
        t_vec3 result2 = vec3_mul_comp(a, vec3_mul_comp(b, c));
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    printf("✓ Associative property tests passed\n");
}

static void test_vec3_mul_comp_distributive(void)
{
    printf("=== test_vec3_mul_comp_distributive ===\n");
    
    // Component-wise multiplication distributes over addition (scalar-wise, not vector dot)
    // Actually, for component-wise multiplication, we have:
    // mul_comp(a, b+c) = mul_comp(a, b) + mul_comp(a, c) (component-wise)
    // But this is NOT true for standard vector multiplication!
    // Let's verify the component-wise property:
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        t_vec3 c = random_vec3(-10.0f, 10.0f);
        
        t_vec3 left = vec3_mul_comp(a, vec3_add(b, c));
        t_vec3 right = vec3_add(vec3_mul_comp(a, b), vec3_mul_comp(a, c));
        
        assert(vec3_equal(left, right, 1e-6f));
    }
    
    printf("✓ Distributive property tests passed\n");
}

static void test_vec3_mul_comp_identity(void)
{
    printf("=== test_vec3_mul_comp_identity ===\n");
    
    // Identity element is (1, 1, 1)
    t_vec3 ones = vec3_new(1.0f, 1.0f, 1.0f);
    
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 result = vec3_mul_comp(a, ones);
        
        assert(vec3_equal(result, a, 1e-6f));
    }
    
    printf("✓ Identity element tests passed\n");
}

static void test_vec3_mul_comp_edge_cases(void)
{
    printf("=== test_vec3_mul_comp_edge_cases ===\n");
    
    // Infinity
    t_vec3 inf_vec = vec3_new(INFINITY, 0.0f, -INFINITY);
    t_vec3 finite_vec = vec3_new(2.0f, 3.0f, 4.0f);
    
    t_vec3 result = vec3_mul_comp(inf_vec, finite_vec);
    assert(isinf(result.x) && !isinf(result.y) && isinf(result.z));
    
    // NaN
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    result = vec3_mul_comp(nan_vec, finite_vec);
    assert(isnan(result.x));
    
    // Very large values
    t_vec3 large = vec3_new(FLT_MAX, FLT_MAX, FLT_MAX);
    result = vec3_mul_comp(large, vec3_new(2.0f, 2.0f, 2.0f));
    assert(isinf(result.x) && isinf(result.y) && isinf(result.z));
    
    // Very small values
    t_vec3 small = vec3_new(FLT_MIN, FLT_MIN, FLT_MIN);
    result = vec3_mul_comp(small, vec3_new(0.5f, 0.5f, 0.5f));
    // Should be half of FLT_MIN (might be denormalized)
    
    // Zero with infinity (0 * ∞ is NaN in IEEE 754)
    t_vec3 zero_inf = vec3_new(0.0f, INFINITY, 0.0f);
    t_vec3 inf_zero = vec3_new(INFINITY, 0.0f, 0.0f);
    result = vec3_mul_comp(zero_inf, inf_zero);
    assert(isnan(result.x) && isnan(result.y) && result.z == 0.0f);
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_div_comp
// ============================================

static void test_vec3_div_comp_basic(void)
{
    printf("=== test_vec3_div_comp_basic ===\n");
    
    // Basic component-wise division
    t_vec3 a = vec3_new(10.0f, 18.0f, 28.0f);
    t_vec3 b = vec3_new(2.0f, 3.0f, 4.0f);
    t_vec3 result = vec3_div_comp(a, b);
    t_vec3 expected = vec3_new(5.0f, 6.0f, 7.0f);
    
    assert(vec3_equal(result, expected, 1e-6f));
    
    // Division by one (identity)
    t_vec3 ones = vec3_new(1.0f, 1.0f, 1.0f);
    result = vec3_div_comp(a, ones);
    assert(vec3_equal(result, a, 1e-6f));
    
    // Division of same vector (should give ones)
    result = vec3_div_comp(a, a);
    assert(vec3_equal(result, ones, 1e-6f));
    
    // Negative numbers
    a = vec3_new(-10.0f, 18.0f, -28.0f);
    b = vec3_new(2.0f, -3.0f, -4.0f);
    result = vec3_div_comp(a, b);
    expected = vec3_new(-5.0f, -6.0f, 7.0f);
    assert(vec3_equal(result, expected, 1e-6f));
    
    printf("✓ Basic component-wise division tests passed\n");
}

static void test_vec3_div_comp_zero_division(void)
{
    printf("=== test_vec3_div_comp_zero_division ===\n");
    
    // Division by zero - check how implementation handles it
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(0.0f, 1.0f, 2.0f);
    
    t_vec3 result = vec3_div_comp(a, b);
    
    // x component is 1/0 which is infinity or a very large number
    printf("  Note: division by zero result: (%.6f, %.6f, %.6f)\n",
           result.x, result.y, result.z);
    
    // Division of zero by non-zero
    a = vec3_new(0.0f, 0.0f, 0.0f);
    b = vec3_new(1.0f, 2.0f, 3.0f);
    result = vec3_div_comp(a, b);
    
    assert(vec3_equal(result, vec3_new(0.0f, 0.0f, 0.0f), 1e-6f));
    
    // Division of zero by zero
    a = vec3_new(0.0f, 0.0f, 0.0f);
    b = vec3_new(0.0f, 0.0f, 0.0f);
    result = vec3_div_comp(a, b);
    
    // 0/0 is NaN in IEEE 754
    assert(isnan(result.x) && isnan(result.y) && isnan(result.z));
    
    printf("✓ Zero division tests passed\n");
}

static void test_vec3_div_comp_inverse(void)
{
    printf("=== test_vec3_div_comp_inverse ===\n");
    
    // Test that a / b = a * (1/b) component-wise
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        // Avoid division by zero
        if (fabsf(b.x) < 1e-6f || fabsf(b.y) < 1e-6f || fabsf(b.z) < 1e-6f)
            continue;
        
        t_vec3 result1 = vec3_div_comp(a, b);
        t_vec3 inv_b = vec3_new(1.0f/b.x, 1.0f/b.y, 1.0f/b.z);
        t_vec3 result2 = vec3_mul_comp(a, inv_b);
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    printf("✓ Inverse relationship tests passed\n");
}

static void test_vec3_div_comp_edge_cases(void)
{
    printf("=== test_vec3_div_comp_edge_cases ===\n");
    
    // Infinity divided by finite
    t_vec3 inf_vec = vec3_new(INFINITY, -INFINITY, INFINITY);
    t_vec3 finite = vec3_new(2.0f, 3.0f, 4.0f);
    
    t_vec3 result = vec3_div_comp(inf_vec, finite);
    assert(isinf(result.x) && isinf(result.y) && isinf(result.z));
    
    // Finite divided by infinity
    result = vec3_div_comp(finite, inf_vec);
    assert(result.x == 0.0f && result.y == 0.0f && result.z == 0.0f);
    
    // NaN
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    result = vec3_div_comp(nan_vec, finite);
    assert(isnan(result.x));
    
    // Very large numbers
    t_vec3 large = vec3_new(FLT_MAX, FLT_MAX, FLT_MAX);
    result = vec3_div_comp(large, vec3_new(2.0f, 2.0f, 2.0f));
    // Should be FLT_MAX/2 (still finite)
    assert(!isinf(result.x) && !isinf(result.y) && !isinf(result.z));
    
    // Very small numbers
    t_vec3 small = vec3_new(FLT_MIN, FLT_MIN, FLT_MIN);
    result = vec3_div_comp(small, vec3_new(2.0f, 2.0f, 2.0f));
    // Should be FLT_MIN/2 (might be denormalized)
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_min_comp
// ============================================

static void test_vec3_min_comp_basic(void)
{
    printf("=== test_vec3_min_comp_basic ===\n");
    
    // Basic component-wise minimum
    t_vec3 a = vec3_new(1.0f, 5.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 2.0f, 6.0f);
    t_vec3 result = vec3_min_comp(a, b);
    t_vec3 expected = vec3_new(1.0f, 2.0f, 3.0f);
    
    assert(vec3_equal(result, expected, 1e-6f));
    
    // Equal vectors
    result = vec3_min_comp(a, a);
    assert(vec3_equal(result, a, 1e-6f));
    
    // Negative numbers
    a = vec3_new(-1.0f, -5.0f, -3.0f);
    b = vec3_new(-4.0f, -2.0f, -6.0f);
    result = vec3_min_comp(a, b);
    expected = vec3_new(-4.0f, -5.0f, -6.0f); // More negative is smaller
    assert(vec3_equal(result, expected, 1e-6f));
    
    // Mixed positive and negative
    a = vec3_new(-1.0f, 5.0f, 0.0f);
    b = vec3_new(2.0f, -3.0f, 1.0f);
    result = vec3_min_comp(a, b);
    expected = vec3_new(-1.0f, -3.0f, 0.0f);
    assert(vec3_equal(result, expected, 1e-6f));
    
    printf("✓ Basic component-wise minimum tests passed\n");
}

static void test_vec3_min_comp_properties(void)
{
    printf("=== test_vec3_min_comp_properties ===\n");
    
    // min_comp is commutative: min_comp(a,b) = min_comp(b,a)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        t_vec3 result1 = vec3_min_comp(a, b);
        t_vec3 result2 = vec3_min_comp(b, a);
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    // min_comp is associative: min_comp(min_comp(a,b), c) = min_comp(a, min_comp(b,c))
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        t_vec3 c = random_vec3(-10.0f, 10.0f);
        
        t_vec3 result1 = vec3_min_comp(vec3_min_comp(a, b), c);
        t_vec3 result2 = vec3_min_comp(a, vec3_min_comp(b, c));
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    // min_comp is idempotent: min_comp(a,a) = a
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 result = vec3_min_comp(a, a);
        
        assert(vec3_equal(result, a, 1e-6f));
    }
    
    printf("✓ Mathematical property tests passed\n");
}

static void test_vec3_min_comp_relationship_with_max(void)
{
    printf("=== test_vec3_min_comp_relationship_with_max ===\n");
    
    // Relationship: min_comp(a,b) + max_comp(a,b) = a + b (component-wise)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        t_vec3 min_result = vec3_min_comp(a, b);
        t_vec3 max_result = vec3_max_comp(a, b);
        t_vec3 sum_min_max = vec3_add(min_result, max_result);
        t_vec3 sum_ab = vec3_add(a, b);
        
        assert(vec3_equal(sum_min_max, sum_ab, 1e-6f));
    }
    
    // Also: min_comp(a,b) ≤ a and min_comp(a,b) ≤ b (component-wise)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        t_vec3 min_result = vec3_min_comp(a, b);
        
        assert(min_result.x <= a.x + 1e-6f && min_result.x <= b.x + 1e-6f);
        assert(min_result.y <= a.y + 1e-6f && min_result.y <= b.y + 1e-6f);
        assert(min_result.z <= a.z + 1e-6f && min_result.z <= b.z + 1e-6f);
    }
    
    printf("✓ Relationship with max tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_max_comp
// ============================================

static void test_vec3_max_comp_basic(void)
{
    printf("=== test_vec3_max_comp_basic ===\n");
    
    // Basic component-wise maximum
    t_vec3 a = vec3_new(1.0f, 5.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 2.0f, 6.0f);
    t_vec3 result = vec3_max_comp(a, b);
    t_vec3 expected = vec3_new(4.0f, 5.0f, 6.0f);
    
    assert(vec3_equal(result, expected, 1e-6f));
    
    // Equal vectors
    result = vec3_max_comp(a, a);
    assert(vec3_equal(result, a, 1e-6f));
    
    // Negative numbers
    a = vec3_new(-1.0f, -5.0f, -3.0f);
    b = vec3_new(-4.0f, -2.0f, -6.0f);
    result = vec3_max_comp(a, b);
    expected = vec3_new(-1.0f, -2.0f, -3.0f); // Less negative is larger
    assert(vec3_equal(result, expected, 1e-6f));
    
    // Mixed positive and negative
    a = vec3_new(-1.0f, 5.0f, 0.0f);
    b = vec3_new(2.0f, -3.0f, 1.0f);
    result = vec3_max_comp(a, b);
    expected = vec3_new(2.0f, 5.0f, 1.0f);
    assert(vec3_equal(result, expected, 1e-6f));
    
    printf("✓ Basic component-wise maximum tests passed\n");
}

static void test_vec3_max_comp_properties(void)
{
    printf("=== test_vec3_max_comp_properties ===\n");
    
    // max_comp is commutative: max_comp(a,b) = max_comp(b,a)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        t_vec3 result1 = vec3_max_comp(a, b);
        t_vec3 result2 = vec3_max_comp(b, a);
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    // max_comp is associative: max_comp(max_comp(a,b), c) = max_comp(a, max_comp(b,c))
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        t_vec3 c = random_vec3(-10.0f, 10.0f);
        
        t_vec3 result1 = vec3_max_comp(vec3_max_comp(a, b), c);
        t_vec3 result2 = vec3_max_comp(a, vec3_max_comp(b, c));
        
        assert(vec3_equal(result1, result2, 1e-6f));
    }
    
    // max_comp is idempotent: max_comp(a,a) = a
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 result = vec3_max_comp(a, a);
        
        assert(vec3_equal(result, a, 1e-6f));
    }
    
    printf("✓ Mathematical property tests passed\n");
}

static void test_vec3_max_comp_edge_cases(void)
{
    printf("=== test_vec3_max_comp_edge_cases ===\n");
    
    // Infinity
    t_vec3 inf_vec = vec3_new(INFINITY, -INFINITY, 0.0f);
    t_vec3 finite = vec3_new(1.0f, 2.0f, 3.0f);
    
    t_vec3 result = vec3_max_comp(inf_vec, finite);
    assert(isinf(result.x) && result.x > 0);
    assert(result.y == 2.0f); // -∞ < 2
    assert(result.z == 3.0f); // 0 < 3
    
    // NaN - max with NaN should return NaN
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    result = vec3_max_comp(nan_vec, finite);
    assert(isnan(result.x));
    
    // Very large values
    t_vec3 large = vec3_new(FLT_MAX, FLT_MAX, FLT_MAX);
    result = vec3_max_comp(large, vec3_new(0.0f, 0.0f, 0.0f));
    assert(vec3_equal(result, large, 1e-6f));
    
    // Very small values
    t_vec3 small = vec3_new(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    result = vec3_max_comp(small, vec3_new(0.0f, 0.0f, 0.0f));
    assert(vec3_equal(result, vec3_new(0.0f, 0.0f, 0.0f), 1e-6f));
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// STACK ALLOCATION TESTS
// ============================================

static void test_comp_stack_operations(void)
{
    printf("=== test_comp_stack_operations ===\n");
    
    // Test multiple component-wise operations on stack
    
#ifdef BENCHMARK
    printf("Testing with %d operations on stack...\n", STACK_TEST_SIZE);
#endif
    
    volatile t_vec3 mul_results[STACK_TEST_SIZE];
    volatile t_vec3 div_results[STACK_TEST_SIZE];
    volatile t_vec3 min_results[STACK_TEST_SIZE];
    volatile t_vec3 max_results[STACK_TEST_SIZE];
    
    for (int i = 0; i < STACK_TEST_SIZE; i++)
    {
        t_vec3 a = vec3_new(
            sinf((float)i * 0.01f) * 10.0f,
            cosf((float)i * 0.02f) * 10.0f,
            sinf((float)i * 0.03f) * 10.0f
        );
        
        t_vec3 b = vec3_new(
            cosf((float)i * 0.04f) * 10.0f,
            sinf((float)i * 0.05f) * 10.0f,
            cosf((float)i * 0.06f) * 10.0f
        );
        
        // Avoid division by zero
        t_vec3 b_safe = b;
        if (fabsf(b_safe.x) < 1e-6f) b_safe.x = 1.0f;
        if (fabsf(b_safe.y) < 1e-6f) b_safe.y = 1.0f;
        if (fabsf(b_safe.z) < 1e-6f) b_safe.z = 1.0f;
        
        // Test all functions
        mul_results[i] = vec3_mul_comp(a, b);
        div_results[i] = vec3_div_comp(a, b_safe);
        min_results[i] = vec3_min_comp(a, b);
        max_results[i] = vec3_max_comp(a, b);
    }
    
    // Verify some specific cases
    t_vec3 a = vec3_new(2.0f, 3.0f, 4.0f);
    t_vec3 b = vec3_new(5.0f, 6.0f, 7.0f);
    
    assert(vec3_equal(vec3_mul_comp(a, b), vec3_new(10.0f, 18.0f, 28.0f), 1e-6f));
    assert(vec3_equal(vec3_div_comp(a, b), vec3_new(0.4f, 0.5f, 4.0f/7.0f), 1e-6f));
    assert(vec3_equal(vec3_min_comp(a, b), vec3_new(2.0f, 3.0f, 4.0f), 1e-6f));
    assert(vec3_equal(vec3_max_comp(a, b), vec3_new(5.0f, 6.0f, 7.0f), 1e-6f));
    
    (void)mul_results;
    (void)max_results;
    (void)min_results;
    (void)div_results;

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

static void benchmark_vec3_mul_comp(void)
{
    printf("=== BENCHMARK: vec3_mul_comp ===\n");
    
    volatile t_vec3 result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_mul_comp(a, b);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_div_comp(void)
{
    printf("=== BENCHMARK: vec3_div_comp ===\n");
    
    volatile t_vec3 result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_div_comp(a, b);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_min_comp(void)
{
    printf("=== BENCHMARK: vec3_min_comp ===\n");
    
    volatile t_vec3 result;
    t_vec3 a = vec3_new(1.0f, 5.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 2.0f, 6.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_min_comp(a, b);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_max_comp(void)
{
    printf("=== BENCHMARK: vec3_max_comp ===\n");
    
    volatile t_vec3 result;
    t_vec3 a = vec3_new(1.0f, 5.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 2.0f, 6.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_max_comp(a, b);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_comp_mixed(void)
{
    printf("=== BENCHMARK: Mixed component-wise operations ===\n");
    
    volatile t_vec3 result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    
    int mul_count = 0, div_count = 0, min_count = 0, max_count = 0;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        // Simulate realistic workload (common in color manipulation and bounding boxes)
        switch (i % 8)
        {
            case 0: case 1:  // 25% multiplication (color mixing)
                result = vec3_mul_comp(a, b);
                mul_count++;
                break;
            case 2:          // 12.5% division (color adjustment)
                result = vec3_div_comp(a, b);
                div_count++;
                break;
            case 3: case 4: case 5:  // 37.5% min (bounding box updates)
                result = vec3_min_comp(a, b);
                min_count++;
                break;
            case 6: case 7:  // 25% max (bounding box updates)
                result = vec3_max_comp(a, b);
                max_count++;
                break;
        }
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Total iterations: %d\n", TEST_ITERATIONS);
    printf("Mul_comp calls: %d, Div_comp calls: %d, Min_comp calls: %d, Max_comp calls: %d\n",
           mul_count, div_count, min_count, max_count);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Operations per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

#endif // BENCHMARK

// ============================================
// INTEGRATION TESTS
// ============================================

static void test_comp_integration(void)
{
    printf("=== test_comp_integration ===\n");
    
    // 1. Relationship between mul_comp and div_comp: (a * b) / b = a (when b != 0)
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(0.1f, 10.0f); // Avoid zero
        
        t_vec3 product = vec3_mul_comp(a, b);
        t_vec3 quotient = vec3_div_comp(product, b);
        
        assert(vec3_equal(quotient, a, 1e-6f));
    }
    
    // 2. Relationship between min_comp and max_comp
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        t_vec3 min_ab = vec3_min_comp(a, b);
        t_vec3 max_ab = vec3_max_comp(a, b);
        
        // min(a,b) ≤ max(a,b) component-wise
        assert(min_ab.x <= max_ab.x + 1e-6f);
        assert(min_ab.y <= max_ab.y + 1e-6f);
        assert(min_ab.z <= max_ab.z + 1e-6f);
    }
    
    // 3. mul_comp with scaling: scale(a, s) = mul_comp(a, vec3_from_scalar(s))
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        float s = (float)rand() / RAND_MAX * 10.0f - 5.0f;
        
        t_vec3 scaled = vec3_scale(a, s);
        t_vec3 mul_scalar = vec3_mul_comp(a, vec3_from_scalar(s));
        
        assert(vec3_equal(scaled, mul_scalar, 1e-6f));
    }
    
    // 4. Interaction with abs: mul_comp(abs(a), abs(b)) = abs(mul_comp(a, b)) for real numbers
    for (int i = 0; i < 50; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        t_vec3 abs_a = vec3_abs(a);
        t_vec3 abs_b = vec3_abs(b);
        t_vec3 left = vec3_mul_comp(abs_a, abs_b);
        
        t_vec3 product = vec3_mul_comp(a, b);
        t_vec3 right = vec3_abs(product);
        
        assert(vec3_equal(left, right, 1e-6f));
    }
    
    printf("✓ Integration tests passed\n");
}

// ============================================
// MINIRT SPECIFIC TESTS
// ============================================

static void test_comp_minirt_context(void)
{
    printf("=== test_comp_minirt_context ===\n");
    
    // 1. Color operations (RGB colors as vec3)
    t_vec3 color1 = vec3_new(0.5f, 0.2f, 0.8f);  // RGB color
    t_vec3 color2 = vec3_new(0.3f, 0.7f, 0.4f);  // Another color
    
    // Color mixing (multiply)
    t_vec3 mixed_color = vec3_mul_comp(color1, color2);
    // Result: (0.15, 0.14, 0.32)
    
    // Color scaling (brightness adjustment)
    float brightness = 1.5f;
    t_vec3 bright_color = vec3_mul_comp(color1, vec3_from_scalar(brightness));
    // Should clamp or handle >1.0 in actual color pipeline
    
    // Color division (darkening)
    float darken = 2.0f;
    t_vec3 dark_color = vec3_div_comp(color1, vec3_from_scalar(darken));
    
    // 2. Bounding box operations
    t_vec3 point1 = vec3_new(-1.0f, 2.0f, 3.0f);
    t_vec3 point2 = vec3_new(2.0f, -1.0f, 5.0f);
    t_vec3 point3 = vec3_new(0.0f, 3.0f, 1.0f);
    
    // Compute bounding box min and max
    t_vec3 bbox_min = point1;
    bbox_min = vec3_min_comp(bbox_min, point2);
    bbox_min = vec3_min_comp(bbox_min, point3);
    
    t_vec3 bbox_max = point1;
    bbox_max = vec3_max_comp(bbox_max, point2);
    bbox_max = vec3_max_comp(bbox_max, point3);
    
    // Verify
    t_vec3 expected_min = vec3_new(-1.0f, -1.0f, 1.0f);
    t_vec3 expected_max = vec3_new(2.0f, 3.0f, 5.0f);
    
    assert(vec3_equal(bbox_min, expected_min, 1e-6f));
    assert(vec3_equal(bbox_max, expected_max, 1e-6f));
    
    // 3. Texture coordinate manipulation
    t_vec3 tex_coord = vec3_new(0.3f, 0.7f, 0.0f); // Usually vec2, but using vec3
    t_vec3 tex_scale = vec3_new(2.0f, 3.0f, 1.0f);
    t_vec3 scaled_tex = vec3_mul_comp(tex_coord, tex_scale);
    // For tiling textures
    
    // 4. Per-component operations for material properties
    t_vec3 diffuse_color = vec3_new(0.8f, 0.6f, 0.4f);
    t_vec3 light_color = vec3_new(1.0f, 0.9f, 0.8f);
    
    // Component-wise multiplication for colored lighting
    t_vec3 lit_color = vec3_mul_comp(diffuse_color, light_color);
    
    // Component-wise min/max for clamping
    t_vec3 clamped_color = vec3_min_comp(lit_color, vec3_from_scalar(1.0f));
    clamped_color = vec3_max_comp(clamped_color, vec3_from_scalar(0.0f));
    
    // 5. Random point in box using component-wise operations
    t_vec3 box_min = vec3_new(-1.0f, -1.0f, -1.0f);
    t_vec3 box_max = vec3_new(1.0f, 1.0f, 1.0f);
    t_vec3 box_size = vec3_sub(box_max, box_min);
    
    // In practice: random_point = min + random * size (component-wise)
    
    // 6. Transformations with non-uniform scaling
    t_vec3 point = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 scale = vec3_new(2.0f, 0.5f, 3.0f);
    t_vec3 scaled_point = vec3_mul_comp(point, scale);
    
    // 7. Per-channel operations for special effects
    // e.g., swapping color channels
    t_vec3 color = vec3_new(0.2f, 0.5f, 0.8f);
    t_vec3 channel_weights = vec3_new(0.0f, 1.0f, 0.0f); // Extract green channel
    t_vec3 green_only = vec3_mul_comp(color, channel_weights);
    
    // 8. Component-wise comparisons for ray-box intersection
    // In ray-box test, we compute min and max for each axis separately
    (void)mixed_color;
    (void)bright_color;
    (void)dark_color;
    (void)box_size;
    (void)scaled_tex;
    (void)scaled_point;
    (void)green_only;
    printf("✓ Minirt context tests passed\n");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

int main()
{
    printf("\n=======================================\n");
    printf("VEC3 COMPONENT-WISE OPERATIONS TEST SUITE\n");
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
    test_vec3_mul_comp_basic();
    test_vec3_mul_comp_commutative();
    test_vec3_mul_comp_associative();
    test_vec3_mul_comp_distributive();
    test_vec3_mul_comp_identity();
    test_vec3_mul_comp_edge_cases();
    
    test_vec3_div_comp_basic();
    test_vec3_div_comp_zero_division();
    test_vec3_div_comp_inverse();
    test_vec3_div_comp_edge_cases();
    
    test_vec3_min_comp_basic();
    test_vec3_min_comp_properties();
    test_vec3_min_comp_relationship_with_max();
    
    test_vec3_max_comp_basic();
    test_vec3_max_comp_properties();
    test_vec3_max_comp_edge_cases();
    
    test_comp_integration();
    test_comp_minirt_context();
    
    // Stack allocation test
    test_comp_stack_operations();
    
#ifdef BENCHMARK
    printf("\n=======================================\n");
    printf("RUNNING BENCHMARKS\n");
    printf("=======================================\n\n");
    
    benchmark_vec3_mul_comp();
    benchmark_vec3_div_comp();
    benchmark_vec3_min_comp();
    benchmark_vec3_max_comp();
    benchmark_comp_mixed();
#endif
    
    printf("\n=======================================\n");
    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    printf("=======================================\n");
    
    return 0;
}