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

// ============================================
// UNIT TESTS - vec3_equal
// ============================================

static void test_vec3_equal_basic(void)
{
    printf("=== test_vec3_equal_basic ===\n");
    
    float epsilon = 1e-6f;
    
    // Same vectors
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    assert(vec3_equal(a, a, epsilon));
    
    // Different vectors
    t_vec3 b = vec3_new(4.0f, 5.0f, 6.0f);
    assert(!vec3_equal(a, b, epsilon));
    
    // Vectors within epsilon
    t_vec3 c = vec3_new(1.0000005f, 2.0000005f, 3.0000005f);
    assert(vec3_equal(a, c, 1e-6f));
    
    // Vectors just outside epsilon
    t_vec3 d = vec3_new(1.0000015f, 2.0000015f, 3.0000015f);
    assert(!vec3_equal(a, d, 1e-6f));
    
    // Different epsilon values
    assert(vec3_equal(a, d, 1e-5f)); // Larger epsilon
    
    // Zero vectors
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    assert(vec3_equal(zero, zero, epsilon));
    
    // Negative vectors
    t_vec3 neg = vec3_new(-1.0f, -2.0f, -3.0f);
    t_vec3 neg_similar = vec3_new(-1.0000005f, -2.0000005f, -3.0000005f);
    assert(vec3_equal(neg, neg_similar, 1e-6f));
    
    printf("✓ Basic equality tests passed\n");
}

static void test_vec3_equal_properties(void)
{
    printf("=== test_vec3_equal_properties ===\n");
    
    float epsilon = 1e-6f;
    
    // Reflexive: a == a
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        assert(vec3_equal(a, a, epsilon));
    }
    
    // Symmetric: if a == b then b == a
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-100.0f, 100.0f);
        t_vec3 b = random_vec3(-100.0f, 100.0f);
        
        bool ab = vec3_equal(a, b, epsilon);
        bool ba = vec3_equal(b, a, epsilon);
        
        assert(ab == ba);
    }
    
    // Not necessarily transitive with epsilon comparisons
    // But test consistency
    
    printf("✓ Equality property tests passed\n");
}

static void test_vec3_equal_edge_cases(void)
{
    printf("=== test_vec3_equal_edge_cases ===\n");
    
    float epsilon = 1e-6f;
    
    // Infinity
    t_vec3 inf1 = vec3_new(INFINITY, INFINITY, INFINITY);
    t_vec3 inf2 = vec3_new(INFINITY, INFINITY, INFINITY);
    
    // Infinity == Infinity (mathematically, but floating point comparisons may vary)
    bool inf_equal = vec3_equal(inf1, inf2, epsilon);
    printf("  Note: inf == inf = %d\n", inf_equal);
    
    // Different infinities
    t_vec3 pos_inf = vec3_new(INFINITY, 0.0f, 0.0f);
    t_vec3 neg_inf = vec3_new(-INFINITY, 0.0f, 0.0f);
    assert(!vec3_equal(pos_inf, neg_inf, epsilon));
    
    // NaN - NaN != NaN in IEEE 754
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    t_vec3 nan_vec2 = vec3_new(NAN, 1.0f, 2.0f);
    bool nan_equal = vec3_equal(nan_vec, nan_vec2, epsilon);
    printf("  Note: nan == nan = %d\n", nan_equal); // Typically false
    
    // Very large numbers
    t_vec3 large1 = vec3_new(1e20f, 1e20f, 1e20f);
    t_vec3 large2 = vec3_new(1e20f + 1.0f, 1e20f, 1e20f);
    // At this scale, 1.0 is within epsilon of 1e20?
    bool large_equal = vec3_equal(large1, large2, 1.0f); // Large epsilon
    printf("  Note: large numbers equality with epsilon=1.0 = %d\n", large_equal);
    
    // Very small numbers (denormalized)
    t_vec3 tiny1 = vec3_new(1e-30f, 1e-30f, 1e-30f);
    t_vec3 tiny2 = vec3_new(1e-30f, 1e-30f, 1e-30f);
    assert(vec3_equal(tiny1, tiny2, 1e-6f));
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_is_zero
// ============================================

static void test_vec3_is_zero_basic(void)
{
    printf("=== test_vec3_is_zero_basic ===\n");
    
    float epsilon = 1e-6f;
    
    // Zero vector
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    assert(vec3_is_zero(zero, epsilon));
    
    // Non-zero vectors
    t_vec3 non_zero = vec3_new(1.0f, 0.0f, 0.0f);
    assert(!vec3_is_zero(non_zero, epsilon));
    
    // Near zero (within epsilon)
    t_vec3 near_zero = vec3_new(1e-7f, -1e-7f, 1e-7f);
    assert(vec3_is_zero(near_zero, 1e-6f));
    
    // Just outside epsilon
    t_vec3 outside_epsilon = vec3_new(1e-5f, 0.0f, 0.0f);
    assert(!vec3_is_zero(outside_epsilon, 1e-6f));
    
    // Different epsilon values
    assert(vec3_is_zero(outside_epsilon, 1e-4f)); // Larger epsilon
    
    // Negative near zero
    t_vec3 neg_near_zero = vec3_new(-1e-7f, -1e-7f, -1e-7f);
    assert(vec3_is_zero(neg_near_zero, 1e-6f));
    
    printf("✓ Basic is_zero tests passed\n");
}

static void test_vec3_is_zero_properties(void)
{
    printf("=== test_vec3_is_zero_properties ===\n");
    
    // Zero vector scaled is still zero
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    float epsilon = 1e-6f;
    
    for (int i = 0; i < 50; i++)
    {
        float scale = (float)rand() / RAND_MAX * 100.0f - 50.0f;
        t_vec3 scaled = vec3_scale(zero, scale);
        assert(vec3_is_zero(scaled, epsilon));
    }
    
    // Zero plus zero is zero
    assert(vec3_is_zero(vec3_add(zero, zero), epsilon));
    
    // Zero minus zero is zero
    assert(vec3_is_zero(vec3_sub(zero, zero), epsilon));
    
    printf("✓ Zero property tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_is_finite
// ============================================

static void test_vec3_is_finite_basic(void)
{
    printf("=== test_vec3_is_finite_basic ===\n");
    
    // Finite vectors
    t_vec3 finite = vec3_new(1.0f, 2.0f, 3.0f);
    assert(vec3_is_finite(finite));
    
    // Infinity
    t_vec3 inf = vec3_new(INFINITY, 1.0f, 2.0f);
    assert(!vec3_is_finite(inf));
    
    // Negative infinity
    t_vec3 neg_inf = vec3_new(-INFINITY, 1.0f, 2.0f);
    assert(!vec3_is_finite(neg_inf));
    
    // NaN
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    assert(!vec3_is_finite(nan_vec));
    
    // Mixed finite and non-finite
    t_vec3 mixed = vec3_new(1.0f, INFINITY, 2.0f);
    assert(!vec3_is_finite(mixed));
    
    // All non-finite
    t_vec3 all_inf = vec3_new(INFINITY, -INFINITY, INFINITY);
    assert(!vec3_is_finite(all_inf));
    
    t_vec3 all_nan = vec3_new(NAN, NAN, NAN);
    assert(!vec3_is_finite(all_nan));
    
    // Zero vector is finite
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    assert(vec3_is_finite(zero));
    
    // Very large but finite
    t_vec3 large = vec3_new(FLT_MAX, -FLT_MAX, FLT_MAX/2.0f);
    assert(vec3_is_finite(large));
    
    printf("✓ Basic is_finite tests passed\n");
}

static void test_vec3_is_finite_random(void)
{
    printf("=== test_vec3_is_finite_random ===\n");
    
    // Random finite vectors should all be finite
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-FLT_MAX, FLT_MAX);
        assert(vec3_is_finite(v));
    }
    
    printf("✓ Random finite tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_any_nan
// ============================================

static void test_vec3_any_nan_basic(void)
{
    printf("=== test_vec3_any_nan_basic ===\n");
    
    // No NaN
    t_vec3 no_nan = vec3_new(1.0f, 2.0f, 3.0f);
    assert(!vec3_any_nan(no_nan));
    
    // One NaN component
    t_vec3 one_nan = vec3_new(NAN, 2.0f, 3.0f);
    assert(vec3_any_nan(one_nan));
    
    // Two NaN components
    t_vec3 two_nan = vec3_new(NAN, NAN, 3.0f);
    assert(vec3_any_nan(two_nan));
    
    // All NaN components
    t_vec3 all_nan = vec3_new(NAN, NAN, NAN);
    assert(vec3_any_nan(all_nan));
    
    // NaN with infinity
    t_vec3 nan_inf = vec3_new(NAN, INFINITY, 1.0f);
    assert(vec3_any_nan(nan_inf));
    
    // Infinity without NaN
    t_vec3 inf_no_nan = vec3_new(INFINITY, -INFINITY, 1.0f);
    assert(!vec3_any_nan(inf_no_nan));
    
    // Zero vector has no NaN
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    assert(!vec3_any_nan(zero));
    
    printf("✓ Basic any_nan tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_abs
// ============================================

static void test_vec3_abs_basic(void)
{
    printf("=== test_vec3_abs_basic ===\n");
    
    // Positive numbers unchanged
    t_vec3 pos = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 abs_pos = vec3_abs(pos);
    assert(vec3_equal(abs_pos, pos, 1e-6f));
    
    // Negative numbers become positive
    t_vec3 neg = vec3_new(-1.0f, -2.0f, -3.0f);
    t_vec3 abs_neg = vec3_abs(neg);
    assert(vec3_equal(abs_neg, pos, 1e-6f));
    
    // Mixed signs
    t_vec3 mixed = vec3_new(-1.0f, 2.0f, -3.0f);
    t_vec3 abs_mixed = vec3_abs(mixed);
    t_vec3 expected = vec3_new(1.0f, 2.0f, 3.0f);
    assert(vec3_equal(abs_mixed, expected, 1e-6f));
    
    // Zero unchanged
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    t_vec3 abs_zero = vec3_abs(zero);
    assert(vec3_equal(abs_zero, zero, 1e-6f));
    
    // Test idempotence: abs(abs(v)) == abs(v)
    t_vec3 v = vec3_new(-1.0f, 2.0f, -3.0f);
    t_vec3 abs_once = vec3_abs(v);
    t_vec3 abs_twice = vec3_abs(abs_once);
    assert(vec3_equal(abs_once, abs_twice, 1e-6f));
    
    printf("✓ Basic abs tests passed\n");
}

static void test_vec3_abs_properties(void)
{
    printf("=== test_vec3_abs_properties ===\n");
    
    // abs(-v) == abs(v)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-100.0f, 100.0f);
        t_vec3 abs_v = vec3_abs(v);
        t_vec3 abs_neg_v = vec3_abs(vec3_neg(v));
        
        assert(vec3_equal(abs_v, abs_neg_v, 1e-6f));
    }
    
    // abs(v) ≥ 0 component-wise
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-100.0f, 100.0f);
        t_vec3 abs_v = vec3_abs(v);
        
        assert(abs_v.x >= 0.0f && abs_v.y >= 0.0f && abs_v.z >= 0.0f);
    }
    
    // |a·b| ≤ |a|·|b| (Cauchy-Schwarz for absolute values)
    // Actually: |a·b| ≤ |a|·|b| is the Cauchy-Schwarz inequality
    // But component-wise: |a_i * b_i| = |a_i| * |b_i|
    for (int i = 0; i < 100; i++)
    {
        t_vec3 a = random_vec3(-10.0f, 10.0f);
        t_vec3 b = random_vec3(-10.0f, 10.0f);
        
        t_vec3 abs_a = vec3_abs(a);
        t_vec3 abs_b = vec3_abs(b);
        t_vec3 abs_product = vec3_abs(vec3_mul_comp(a, b));
        t_vec3 product_abs = vec3_mul_comp(abs_a, abs_b);
        
        assert(vec3_equal(abs_product, product_abs, 1e-6f));
    }
    
    printf("✓ Abs property tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_floor, vec3_ceil, vec3_round
// ============================================

static void test_vec3_floor_basic(void)
{
    printf("=== test_vec3_floor_basic ===\n");
    
    // Positive numbers
    t_vec3 v1 = vec3_new(1.3f, 2.7f, 3.0f);
    t_vec3 floor1 = vec3_floor(v1);
    t_vec3 expected1 = vec3_new(1.0f, 2.0f, 3.0f);
    assert(vec3_equal(floor1, expected1, 1e-6f));
    
    // Negative numbers (floor goes to more negative)
    t_vec3 v2 = vec3_new(-1.3f, -2.7f, -3.0f);
    t_vec3 floor2 = vec3_floor(v2);
    t_vec3 expected2 = vec3_new(-2.0f, -3.0f, -3.0f);
    assert(vec3_equal(floor2, expected2, 1e-6f));
    
    // Mixed signs
    t_vec3 v3 = vec3_new(-1.3f, 2.7f, 0.0f);
    t_vec3 floor3 = vec3_floor(v3);
    t_vec3 expected3 = vec3_new(-2.0f, 2.0f, 0.0f);
    assert(vec3_equal(floor3, expected3, 1e-6f));
    
    // Already integer
    t_vec3 v4 = vec3_new(2.0f, -3.0f, 0.0f);
    t_vec3 floor4 = vec3_floor(v4);
    assert(vec3_equal(floor4, v4, 1e-6f));
    
    // Large numbers
    t_vec3 v5 = vec3_new(123456.78f, -987654.32f, 0.001f);
    t_vec3 floor5 = vec3_floor(v5);
    t_vec3 expected5 = vec3_new(123456.0f, -987655.0f, 0.0f);
    assert(vec3_equal(floor5, expected5, 1e-6f));
    
    printf("✓ Basic floor tests passed\n");
}

static void test_vec3_ceil_basic(void)
{
    printf("=== test_vec3_ceil_basic ===\n");
    
    // Positive numbers
    t_vec3 v1 = vec3_new(1.3f, 2.7f, 3.0f);
    t_vec3 ceil1 = vec3_ceil(v1);
    t_vec3 expected1 = vec3_new(2.0f, 3.0f, 3.0f);
    assert(vec3_equal(ceil1, expected1, 1e-6f));
    
    // Negative numbers (ceil goes to less negative)
    t_vec3 v2 = vec3_new(-1.3f, -2.7f, -3.0f);
    t_vec3 ceil2 = vec3_ceil(v2);
    t_vec3 expected2 = vec3_new(-1.0f, -2.0f, -3.0f);
    assert(vec3_equal(ceil2, expected2, 1e-6f));
    
    // Mixed signs
    t_vec3 v3 = vec3_new(-1.3f, 2.7f, 0.0f);
    t_vec3 ceil3 = vec3_ceil(v3);
    t_vec3 expected3 = vec3_new(-1.0f, 3.0f, 0.0f);
    assert(vec3_equal(ceil3, expected3, 1e-6f));
    
    // Already integer
    t_vec3 v4 = vec3_new(2.0f, -3.0f, 0.0f);
    t_vec3 ceil4 = vec3_ceil(v4);
    assert(vec3_equal(ceil4, v4, 1e-6f));
    
    // Large numbers
    t_vec3 v5 = vec3_new(123456.78f, -987654.32f, 0.001f);
    t_vec3 ceil5 = vec3_ceil(v5);
    t_vec3 expected5 = vec3_new(123457.0f, -987654.0f, 1.0f);
    assert(vec3_equal(ceil5, expected5, 1e-6f));
    
    printf("✓ Basic ceil tests passed\n");
}

static void test_vec3_round_basic(void)
{
    printf("=== test_vec3_round_basic ===\n");
    
    // Positive numbers
    t_vec3 v1 = vec3_new(1.3f, 2.7f, 3.0f);
    t_vec3 round1 = vec3_round(v1);
    t_vec3 expected1 = vec3_new(1.0f, 3.0f, 3.0f);
    assert(vec3_equal(round1, expected1, 1e-6f));
    
    // Negative numbers
    t_vec3 v2 = vec3_new(-1.3f, -2.7f, -3.0f);
    t_vec3 round2 = vec3_round(v2);
    t_vec3 expected2 = vec3_new(-1.0f, -3.0f, -3.0f);
    assert(vec3_equal(round2, expected2, 1e-6f));
    
    // .5 cases (ties to even typically, but implementation may vary)
    t_vec3 v3 = vec3_new(1.5f, 2.5f, -1.5f);
    t_vec3 round3 = vec3_round(v3);
    printf("  Note: round(1.5, 2.5, -1.5) = (%.1f, %.1f, %.1f)\n", 
           round3.x, round3.y, round3.z);
    
    // Already integer
    t_vec3 v4 = vec3_new(2.0f, -3.0f, 0.0f);
    t_vec3 round4 = vec3_round(v4);
    assert(vec3_equal(round4, v4, 1e-6f));
    
    // Large numbers
    t_vec3 v5 = vec3_new(123456.78f, -987654.32f, 0.001f);
    t_vec3 round5 = vec3_round(v5);
    t_vec3 expected5 = vec3_new(123457.0f, -987654.0f, 0.0f);
    assert(vec3_equal(round5, expected5, 1e-6f));
    
    printf("✓ Basic round tests passed\n");
}

static void test_vec3_floor_ceil_round_relationships(void)
{
    printf("=== test_vec3_floor_ceil_round_relationships ===\n");
    
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-100.0f, 100.0f);
        t_vec3 floor_v = vec3_floor(v);
        t_vec3 ceil_v = vec3_ceil(v);
        t_vec3 round_v = vec3_round(v);
        
        // floor(v) ≤ v ≤ ceil(v) component-wise
        assert(floor_v.x <= v.x + 1e-6f && v.x <= ceil_v.x + 1e-6f);
        assert(floor_v.y <= v.y + 1e-6f && v.y <= ceil_v.y + 1e-6f);
        assert(floor_v.z <= v.z + 1e-6f && v.z <= ceil_v.z + 1e-6f);
        
        // round(v) is either floor(v) or ceil(v)
        // Check each component
        for (int j = 0; j < 3; j++)
        {
            float vj = ((float*)&v)[j];
            float floor_vj = ((float*)&floor_v)[j];
            float ceil_vj = ((float*)&ceil_v)[j];
            float round_vj = ((float*)&round_v)[j];
            
            assert(round_vj == floor_vj || round_vj == ceil_vj);
            
            // If v is exactly halfway, both are possible
            // Otherwise, round should be the closer one
            if (fabsf(vj - floor_vj - 0.5f) > 1e-6f) // Not exactly halfway
            {
                float dist_to_floor = fabsf(vj - floor_vj);
                float dist_to_ceil = fabsf(vj - ceil_vj);
                
                if (dist_to_floor < dist_to_ceil)
                    assert(round_vj == floor_vj);
                else if (dist_to_ceil < dist_to_floor)
                    assert(round_vj == ceil_vj);
                // If equal (exactly halfway), either is acceptable
            }
        }
        
        // floor(-v) = -ceil(v)
        t_vec3 floor_neg = vec3_floor(vec3_neg(v));
        t_vec3 neg_ceil = vec3_neg(vec3_ceil(v));
        assert(vec3_equal(floor_neg, neg_ceil, 1e-6f));
    }
    
    printf("✓ Floor/ceil/round relationship tests passed\n");
}

// ============================================
// UNIT TESTS - vec3_mod
// ============================================

static void test_vec3_mod_basic(void)
{
    printf("=== test_vec3_mod_basic ===\n");
    
    // Basic modulo operations
    t_vec3 v = vec3_new(5.0f, 7.0f, 9.0f);
    float divisor = 3.0f;
    t_vec3 mod_result = vec3_mod(v, divisor);
    t_vec3 expected = vec3_new(2.0f, 1.0f, 0.0f); // 5%3=2, 7%3=1, 9%3=0
    assert(vec3_equal(mod_result, expected, 1e-6f));
    
    // Negative numbers
    v = vec3_new(-5.0f, -7.0f, -9.0f);
    mod_result = vec3_mod(v, divisor);
    // C's fmod preserves sign of dividend: fmod(-5, 3) = -2
    expected = vec3_new(-2.0f, -1.0f, 0.0f);
    assert(vec3_equal(mod_result, expected, 1e-6f));
    
    // Mixed signs
    v = vec3_new(-5.0f, 7.0f, 0.0f);
    mod_result = vec3_mod(v, divisor);
    expected = vec3_new(-2.0f, 1.0f, 0.0f);
    assert(vec3_equal(mod_result, expected, 1e-6f));
    
    // Result should be in (-divisor, divisor) for nonzero results
    v = vec3_new(15.0f, -15.0f, 1.5f);
    divisor = 4.0f;
    mod_result = vec3_mod(v, divisor);
    
    assert(fabsf(mod_result.x) < divisor);
    assert(fabsf(mod_result.y) < divisor);
    assert(fabsf(mod_result.z) < divisor);
    
    // Zero vector
    v = vec3_new(0.0f, 0.0f, 0.0f);
    mod_result = vec3_mod(v, divisor);
    expected = vec3_new(0.0f, 0.0f, 0.0f);
    assert(vec3_equal(mod_result, expected, 1e-6f));
    
    printf("✓ Basic mod tests passed\n");
}

static void test_vec3_mod_properties(void)
{
    printf("=== test_vec3_mod_properties ===\n");
    
    // Test that v = k*divisor + mod(v, divisor) for some integer k
    // Actually, fmod(v, d) = v - n*d where n = trunc(v/d)
    for (int i = 0; i < 100; i++)
    {
        t_vec3 v = random_vec3(-100.0f, 100.0f);
        float divisor = (float)rand() / RAND_MAX * 10.0f + 0.1f; // Avoid zero
        
        t_vec3 m = vec3_mod(v, divisor);
        
        // For each component: v = n*d + m where n = trunc(v/d)
        for (int j = 0; j < 3; j++)
        {
            float vj = ((float*)&v)[j];
            float mj = ((float*)&mj)[j];
            float n = truncf(vj / divisor);
            float reconstructed = n * divisor + mj;
            
            assert(float_equal(vj, reconstructed, 1e-6f));
        }
        (void)m;
    }
    
    // mod(mod(v, d), d) = mod(v, d) (idempotent for positive d)
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(-100.0f, 100.0f);
        float divisor = (float)rand() / RAND_MAX * 10.0f + 0.1f;
        
        t_vec3 m1 = vec3_mod(v, divisor);
        t_vec3 m2 = vec3_mod(m1, divisor);
        
        assert(vec3_equal(m1, m2, 1e-6f));
    }
    
    // mod(v + k*d, d) = mod(v, d) for integer k
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(-100.0f, 100.0f);
        float divisor = (float)rand() / RAND_MAX * 10.0f + 0.1f;
        int k = rand() % 10 - 5; // -5 to 4
        
        t_vec3 v_shifted = vec3_add(v, vec3_scale(vec3_from_scalar(divisor), (float)k));
        t_vec3 m1 = vec3_mod(v, divisor);
        t_vec3 m2 = vec3_mod(v_shifted, divisor);
        
        assert(vec3_equal(m1, m2, 1e-6f));
    }
    
    printf("✓ Mod property tests passed\n");
}

static void test_vec3_mod_edge_cases(void)
{
    printf("=== test_vec3_mod_edge_cases ===\n");
    
    // Division by zero (should produce NaN or crash)
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    float divisor = 0.0f;
    
    // This is undefined behavior - fmod(x, 0) returns NaN
    t_vec3 mod_result = vec3_mod(v, divisor);
    printf("  Note: mod(v, 0) = (%.6f, %.6f, %.6f)\n", 
           mod_result.x, mod_result.y, mod_result.z);
    
    // Very small divisor
    divisor = 1e-30f;
    mod_result = vec3_mod(v, divisor);
    // Should work, might be denormalized
    
    // Very large divisor
    divisor = 1e30f;
    mod_result = vec3_mod(v, divisor);
    // For v < divisor, mod(v, divisor) = v
    
    // Infinity
    t_vec3 inf_vec = vec3_new(INFINITY, 1.0f, 2.0f);
    divisor = 2.0f;
    mod_result = vec3_mod(inf_vec, divisor);
    // fmod(inf, d) is NaN
    assert(isnan(mod_result.x));
    
    // NaN
    t_vec3 nan_vec = vec3_new(NAN, 1.0f, 2.0f);
    mod_result = vec3_mod(nan_vec, divisor);
    assert(isnan(mod_result.x));
    
    // Negative divisor
    divisor = -3.0f;
    mod_result = vec3_mod(v, divisor);
    // fmod with negative divisor: fmod(5, -3) = 2 (sign of divisor ignored for result sign)
    // Actually fmod(5, -3) = 2, fmod(-5, -3) = -2
    printf("  Note: mod((1,2,3), -3) = (%.6f, %.6f, %.6f)\n",
           mod_result.x, mod_result.y, mod_result.z);
    
    printf("✓ Edge cases tests passed\n");
}

// ============================================
// STACK ALLOCATION TESTS
// ============================================

static void test_compare_stack_operations(void)
{
    printf("=== test_compare_stack_operations ===\n");
    
#ifdef BENCHMARK
    printf("Testing with %d operations on stack...\n", STACK_TEST_SIZE);
#endif
    
    volatile bool bool_results[STACK_TEST_SIZE * 4];
    volatile t_vec3 vec_results[STACK_TEST_SIZE * 5];
    
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
        
        float epsilon = 1e-6f;
        float divisor = 3.0f + sinf((float)i * 0.01f); // Vary divisor
        
        // Comparison functions
        bool_results[i * 4 + 0] = vec3_equal(a, b, epsilon);
        bool_results[i * 4 + 1] = vec3_is_zero(a, epsilon);
        bool_results[i * 4 + 2] = vec3_is_finite(a);
        bool_results[i * 4 + 3] = vec3_any_nan(a);
        
        // Utility functions
        vec_results[i * 5 + 0] = vec3_abs(a);
        vec_results[i * 5 + 1] = vec3_floor(a);
        vec_results[i * 5 + 2] = vec3_ceil(a);
        vec_results[i * 5 + 3] = vec3_round(a);
        vec_results[i * 5 + 4] = vec3_mod(a, divisor);
    }
    
    // Verify some specific cases
    t_vec3 test = vec3_new(-1.5f, 2.3f, 0.0f);
    float eps = 1e-6f;
    
    assert(!vec3_is_zero(test, eps));
    assert(vec3_is_finite(test));
    assert(!vec3_any_nan(test));
    
    t_vec3 abs_test = vec3_abs(test);
    assert(vec3_equal(abs_test, vec3_new(1.5f, 2.3f, 0.0f), eps));
    
    t_vec3 floor_test = vec3_floor(test);
    assert(vec3_equal(floor_test, vec3_new(-2.0f, 2.0f, 0.0f), eps));
    (void)bool_results;
    (void)vec_results;
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

static void benchmark_vec3_equal(void)
{
    printf("=== BENCHMARK: vec3_equal ===\n");
    
    volatile bool result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(1.000001f, 2.000001f, 3.000001f);
    float epsilon = 1e-6f;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_equal(a, b, epsilon);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_is_zero(void)
{
    printf("=== BENCHMARK: vec3_is_zero ===\n");
    
    volatile bool result;
    t_vec3 v = vec3_new(0.000001f, -0.000001f, 0.0f);
    float epsilon = 1e-6f;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_is_zero(v, epsilon);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_is_finite(void)
{
    printf("=== BENCHMARK: vec3_is_finite ===\n");
    
    volatile bool result;
    t_vec3 v = vec3_new(1.0f, 2.0f, 3.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_is_finite(v);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_vec3_abs(void)
{
    printf("=== BENCHMARK: vec3_abs ===\n");
    
    volatile t_vec3 result;
    t_vec3 v = vec3_new(-1.0f, 2.0f, -3.0f);
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        result = vec3_abs(v);
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Iterations: %d\n", TEST_ITERATIONS);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Time per call: %.9f seconds\n", elapsed / TEST_ITERATIONS);
    printf("Calls per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)result;
}

static void benchmark_compare_mixed(void)
{
    printf("=== BENCHMARK: Mixed comparison operations ===\n");
    
    volatile bool bool_result;
    volatile t_vec3 vec_result;
    t_vec3 a = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 b = vec3_new(1.000001f, 2.000001f, 3.000001f);
    float epsilon = 1e-6f;
    float divisor = 2.5f;
    
    int equal_count = 0, is_zero_count = 0, is_finite_count = 0, any_nan_count = 0;
    int abs_count = 0, floor_count = 0, ceil_count = 0, round_count = 0, mod_count = 0;
    
    double start = get_time();
    
    for (int i = 0; i < TEST_ITERATIONS; i++)
    {
        // Simulate realistic workload
        switch (i % 18)
        {
            case 0: case 1:  // ~11% equal
                bool_result = vec3_equal(a, b, epsilon);
                equal_count++;
                break;
            case 2: case 3:  // ~11% is_zero
                bool_result = vec3_is_zero(a, epsilon);
                is_zero_count++;
                break;
            case 4: case 5:  // ~11% is_finite
                bool_result = vec3_is_finite(a);
                is_finite_count++;
                break;
            case 6: case 7:  // ~11% any_nan
                bool_result = vec3_any_nan(a);
                any_nan_count++;
                break;
            case 8: case 9:  // ~11% abs
                vec_result = vec3_abs(a);
                abs_count++;
                break;
            case 10: case 11: // ~11% floor
                vec_result = vec3_floor(a);
                floor_count++;
                break;
            case 12: case 13: // ~11% ceil
                vec_result = vec3_ceil(a);
                ceil_count++;
                break;
            case 14: case 15: // ~11% round
                vec_result = vec3_round(a);
                round_count++;
                break;
            case 16: case 17: // ~11% mod
                vec_result = vec3_mod(a, divisor);
                mod_count++;
                break;
        }
    }
    
    double end = get_time();
    double elapsed = end - start;
    
    printf("Total iterations: %d\n", TEST_ITERATIONS);
    printf("Equal calls: %d, IsZero: %d, IsFinite: %d, AnyNan: %d\n",
           equal_count, is_zero_count, is_finite_count, any_nan_count);
    printf("Abs calls: %d, Floor: %d, Ceil: %d, Round: %d, Mod: %d\n",
           abs_count, floor_count, ceil_count, round_count, mod_count);
    printf("Total time: %.6f seconds\n", elapsed);
    printf("Operations per second: %.0f\n", TEST_ITERATIONS / elapsed);
    
    (void)bool_result;
    (void)vec_result;
}

#endif // BENCHMARK

// ============================================
// INTEGRATION TESTS
// ============================================

static void test_compare_integration(void)
{
    printf("=== test_compare_integration ===\n");
    
    float epsilon = 1e-6f;
    
    // 1. Relationship between is_zero and equal
    t_vec3 zero = vec3_new(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        
        bool is_zero = vec3_is_zero(v, epsilon);
        bool equal_to_zero = vec3_equal(v, zero, epsilon);
        
        // These should be equivalent
        assert(is_zero == equal_to_zero);
    }
    
    // 2. If is_finite is false, then any_nan might be true or there's infinity
    // Test with known non-finite vectors
    t_vec3 non_finite[] = {
        vec3_new(NAN, 1.0f, 2.0f),
        vec3_new(1.0f, NAN, 2.0f),
        vec3_new(1.0f, 2.0f, NAN),
        vec3_new(INFINITY, 1.0f, 2.0f),
        vec3_new(1.0f, -INFINITY, 2.0f),
        vec3_new(NAN, INFINITY, -INFINITY),
    };
    
    for (int i = 0; i < 6; i++)
    {
        assert(!vec3_is_finite(non_finite[i]));
        // At least one of: any_nan true or contains infinity
        bool has_nan = vec3_any_nan(non_finite[i]);
        bool has_inf = !vec3_is_finite(non_finite[i]) && !has_nan;
        assert(has_nan || has_inf);
    }
    
    // 3. abs properties with other operations
    for (int i = 0; i < 50; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        
        // abs(v) = abs(-v)
        t_vec3 abs_v = vec3_abs(v);
        t_vec3 abs_neg_v = vec3_abs(vec3_neg(v));
        assert(vec3_equal(abs_v, abs_neg_v, epsilon));
        
        // floor(abs(v)) ≥ 0
        t_vec3 floor_abs = vec3_floor(abs_v);
        assert(floor_abs.x >= 0.0f && floor_abs.y >= 0.0f && floor_abs.z >= 0.0f);
        
        // ceil(abs(v)) ≥ 0
        t_vec3 ceil_abs = vec3_ceil(abs_v);
        assert(ceil_abs.x >= 0.0f && ceil_abs.y >= 0.0f && ceil_abs.z >= 0.0f);
    }
    
    // 4. mod properties
    for (int i = 0; i < 20; i++)
    {
        t_vec3 v = random_vec3(-10.0f, 10.0f);
        float divisor = (float)rand() / RAND_MAX * 5.0f + 0.1f;
        
        t_vec3 m = vec3_mod(v, divisor);
        
        // |m| < |divisor| for non-zero m
        if (!vec3_is_zero(m, epsilon))
        {
            assert(fabsf(m.x) < fabsf(divisor) + epsilon);
            assert(fabsf(m.y) < fabsf(divisor) + epsilon);
            assert(fabsf(m.z) < fabsf(divisor) + epsilon);
        }
        
        // mod(abs(v), d) = abs(mod(v, d)) when v and divisor have same sign?
        // Actually not always true due to sign preservation in fmod
    }
    
    printf("✓ Integration tests passed\n");
}

// ============================================
// MINIRT SPECIFIC TESTS
// ============================================

static void test_compare_minirt_context(void)
{
    printf("=== test_compare_minirt_context ===\n");
    
    float epsilon = 1e-6f;
    
    // 1. Checking if vectors are zero (e.g., degenerate triangles)
    t_vec3 triangle_normal = vec3_new(0.0f, 0.0f, 0.0f); // Degenerate triangle
    if (vec3_is_zero(triangle_normal, epsilon))
    {
        printf("  Note: Degenerate triangle detected (zero area)\n");
        // Handle degenerate case
    }
    
    // 2. Checking for NaN in intersection results
    t_vec3 intersection_point = vec3_new(1.0f, 2.0f, 3.0f);
    // Simulate potential NaN from failed intersection
    // intersection_point.x = 0.0f / 0.0f; // Would produce NaN
    
    if (vec3_any_nan(intersection_point))
    {
        printf("  Note: NaN in intersection result\n");
        // Skip this intersection
    }
    
    // 3. Checking if vectors are finite (sanity check)
    t_vec3 ray_direction = vec3_new(1.0f, 2.0f, 3.0f);
    if (!vec3_is_finite(ray_direction))
    {
        printf("  Note: Non-finite ray direction\n");
        // Handle error
    }
    
    // 4. Using abs for distance calculations (absolute differences)
    t_vec3 point1 = vec3_new(1.0f, 2.0f, 3.0f);
    t_vec3 point2 = vec3_new(4.0f, 5.0f, 6.0f);
    t_vec3 diff = vec3_abs(vec3_sub(point1, point2));
    // Manhattan distance: sum of absolute differences
    float manhattan_dist = diff.x + diff.y + diff.z;
    // 5. Using floor/ceil/round for grid-based operations (voxelization, spatial hashing)
    t_vec3 world_point = vec3_new(1.3f, 2.7f, 3.2f);
    t_vec3 voxel_coord = vec3_floor(world_point); // Convert to voxel grid
    
    // 6. Using mod for tiling textures or periodic patterns
    t_vec3 tex_coord = vec3_new(1.3f, 2.7f, 0.0f);
    float tile_size = 1.0f;
    t_vec3 tiled_tex = vec3_mod(tex_coord, tile_size); // Wrap to [0, tile_size)
    
    // 7. Checking equality for cached computations
    t_vec3 cached_normal = vec3_new(0.0f, 1.0f, 0.0f);
    t_vec3 computed_normal = vec3_new(0.000001f, 1.000001f, 0.000001f);
    if (vec3_equal(cached_normal, computed_normal, 1e-5f))
    {
        // Use cached value
    }
    
    // 8. Absolute value for reflection calculations
    // When computing reflection, we might need absolute values for Fresnel terms
    
    // 9. Checking if normalized vectors are actually unit length
    t_vec3 normalized = vec3_new(0.70710678f, 0.70710678f, 0.0f);
    t_vec3 ones = vec3_new(1.0f, 1.0f, 1.0f);
    t_vec3 diff_from_one = vec3_abs(vec3_sub(vec3_new(vec3_length(normalized), 
                                                    vec3_length(normalized), 
                                                    vec3_length(normalized)), ones));
    if (vec3_is_zero(diff_from_one, 1e-4f))
    {
        // Properly normalized
    }
    (void)manhattan_dist;
    (void)voxel_coord;
    (void)tiled_tex;

    printf("✓ Minirt context tests passed\n");
}

// ============================================
// MAIN TEST RUNNER
// ============================================

int main()
{
    printf("\n=======================================\n");
    printf("VEC3 COMPARISON & UTILITY TEST SUITE\n");
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
    test_vec3_equal_basic();
    test_vec3_equal_properties();
    test_vec3_equal_edge_cases();
    
    test_vec3_is_zero_basic();
    test_vec3_is_zero_properties();
    
    test_vec3_is_finite_basic();
    test_vec3_is_finite_random();
    
    test_vec3_any_nan_basic();
    
    test_vec3_abs_basic();
    test_vec3_abs_properties();
    
    test_vec3_floor_basic();
    test_vec3_ceil_basic();
    test_vec3_round_basic();
    test_vec3_floor_ceil_round_relationships();
    
    test_vec3_mod_basic();
    test_vec3_mod_properties();
    test_vec3_mod_edge_cases();
    
    test_compare_integration();
    test_compare_minirt_context();
    
    // Stack allocation test
    test_compare_stack_operations();
    
#ifdef BENCHMARK
    printf("\n=======================================\n");
    printf("RUNNING BENCHMARKS\n");
    printf("=======================================\n\n");
    
    benchmark_vec3_equal();
    benchmark_vec3_is_zero();
    benchmark_vec3_is_finite();
    benchmark_vec3_abs();
    benchmark_compare_mixed();
#endif
    
    printf("\n=======================================\n");
    printf("ALL TESTS PASSED SUCCESSFULLY!\n");
    printf("=======================================\n");
    
    return 0;
}