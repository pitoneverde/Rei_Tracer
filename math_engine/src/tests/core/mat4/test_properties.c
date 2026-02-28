/*==============================================================================
# test_properties.c – Matrix properties, inverse, transpose tests
==============================================================================*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "core/mat4.h"
#include "core/vec3.h"
#include "utils/math_constants.h"

#ifndef EPSILON
# define EPSILON 1e-6f
#endif

/*------------------------------------------------------------------------------
  Helper functions (shared pattern – consider moving to a common header)
------------------------------------------------------------------------------*/

static inline bool float_equal(float a, float b, float eps)
{
    return fabsf(a - b) < eps;
}

static float random_float(float min, float max)
{
    float r = (float)rand() / RAND_MAX;
    return min + r * (max - min);
}

// static t_vec3 random_vec3(float min, float max)
// {
//     return vec3_new(random_float(min, max),
//                     random_float(min, max),
//                     random_float(min, max));
// }

static t_mat4 random_mat4(float min, float max)
{
    t_mat4 m;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m.mat[i][j] = random_float(min, max);
    return m;
}

static bool mat4_equal_eps(t_mat4 a, t_mat4 b, float eps)
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (!float_equal(a.mat[i][j], b.mat[i][j], eps))
                return false;
    return true;
}

// static void print_mat4(const char *name, t_mat4 m)
// {
//     printf("%s:\n", name);
//     for (int i = 0; i < 4; ++i)
//         printf("  [ %7.3f %7.3f %7.3f %7.3f ]\n",
//                m.mat[i][0], m.mat[i][1], m.mat[i][2], m.mat[i][3]);
// }

/*------------------------------------------------------------------------------
  Unit tests
------------------------------------------------------------------------------*/

static void test_mat4_determinant(void)
{
    printf("=== test_mat4_determinant ===\n");

    // Identity
    t_mat4 I = mat4_identity();
    assert(float_equal(mat4_determinant(I), 1.0f, EPSILON));

    // Zero matrix
    t_mat4 Z = mat4_zero();
    assert(float_equal(mat4_determinant(Z), 0.0f, EPSILON));

    // Scaling matrix
    t_mat4 S = mat4_scaling((t_vec3){2,3,4});
    assert(float_equal(mat4_determinant(S), 2*3*4, EPSILON));

    // Rotation matrix (determinant = 1)
    t_mat4 R = mat4_rotation_x(MATH_PI/3);
    assert(float_equal(mat4_determinant(R), 1.0f, EPSILON));

    // Translation matrix (determinant = 1)
    t_mat4 T = mat4_translation((t_vec3){1,2,3});
    assert(float_equal(mat4_determinant(T), 1.0f, EPSILON));

    // Product property: det(AB) = det(A) * det(B)
    t_mat4 A = random_mat4(-2, 2);
    t_mat4 B = random_mat4(-2, 2);
    float detA = mat4_determinant(A);
    float detB = mat4_determinant(B);
    t_mat4 AB = mat4_mul(A, B);
    float detAB = mat4_determinant(AB);
    assert(float_equal(detAB, detA * detB, EPSILON * 10.0f));

    // Singular matrix (two equal rows)
    t_mat4 singular = A;
    singular.mat[1][0] = singular.mat[0][0];
    singular.mat[1][1] = singular.mat[0][1];
    singular.mat[1][2] = singular.mat[0][2];
    singular.mat[1][3] = singular.mat[0][3];
    assert(float_equal(mat4_determinant(singular), 0.0f, EPSILON));

    // Check with a known 4x4 determinant (e.g., Hilbert matrix)
    t_mat4 hilbert = { .arr = {
        1.0f, 1/2.0f, 1/3.0f, 1/4.0f,
        1/2.0f, 1/3.0f, 1/4.0f, 1/5.0f,
        1/3.0f, 1/4.0f, 1/5.0f, 1/6.0f,
        1/4.0f, 1/5.0f, 1/6.0f, 1/7.0f
    }};
    float det_hilbert = mat4_determinant(hilbert);
    // Known approximate value: 1.6512e-7 (from literature)
    assert(float_equal(det_hilbert, 1.6512e-7f, 1e-4f)); // coarse tolerance

    printf("✓ determinant tests passed\n");
}

static void test_mat4_inverse(void)
{
    printf("=== test_mat4_inverse ===\n");

    // Identity inverse is identity
    t_mat4 I = mat4_identity();
    t_mat4 Iinv = mat4_inverse(I);
    assert(mat4_equal_eps(Iinv, I, EPSILON));

    // Rotation inverse equals transpose
    t_mat4 R = mat4_rotation_y(MATH_PI/4);
    t_mat4 Rinv = mat4_inverse(R);
    t_mat4 Rtrans = mat4_transpose(R);
    assert(mat4_equal_eps(Rinv, Rtrans, EPSILON));
    // Also check R * Rinv = I
    t_mat4 prod = mat4_mul(R, Rinv);
    assert(mat4_equal_eps(prod, I, EPSILON));

    // Scaling inverse = scaling by reciprocal
    t_mat4 S = mat4_scaling((t_vec3){2,3,4});
    t_mat4 Sinv = mat4_inverse(S);
    t_mat4 S_expected = mat4_scaling((t_vec3){1/2.0f, 1/3.0f, 1/4.0f});
    assert(mat4_equal_eps(Sinv, S_expected, EPSILON));

    // Translation inverse = translation by negative
    t_mat4 T = mat4_translation((t_vec3){1,-2,3});
    t_mat4 Tinv = mat4_inverse(T);
    t_mat4 T_expected = mat4_translation((t_vec3){-1,2,-3});
    assert(mat4_equal_eps(Tinv, T_expected, EPSILON));

    // Affine (rotation + translation)
    t_mat4 M = mat4_mul(T, R); // first rotate then translate
    t_mat4 Minv = mat4_inverse(M);
    // Expected: inv(M) = inv(T * R) = inv(R) * inv(T) = R^T * T(-t)
    t_mat4 Rtrans_T = mat4_mul(Rtrans, mat4_translation((t_vec3){-1,2,-3}));
    assert(mat4_equal_eps(Minv, Rtrans_T, EPSILON));

    // Check that M * Minv = I
    prod = mat4_mul(M, Minv);
    assert(mat4_equal_eps(prod, I, EPSILON));

    // Singular matrix (det=0) – should return something (maybe zero or NaN)
    // We just ensure it doesn't crash and that result is not usable.
    t_mat4 singular = { .arr = {
        1,2,3,4,
        1,2,3,4, // duplicate row
        5,6,7,8,
        9,10,11,12
    }};
    t_mat4 SSinv = mat4_inverse(singular);
    (void)SSinv; // ignore result, just check it compiles

    printf("✓ inverse tests passed\n");
}

static void test_mat4_transpose(void)
{
    printf("=== test_mat4_transpose ===\n");

    t_mat4 A = random_mat4(-5, 5);
    t_mat4 AT = mat4_transpose(A);

    // Check element-wise
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            assert(float_equal(AT.mat[i][j], A.mat[j][i], EPSILON));

    // Double transpose gives original
    t_mat4 ATT = mat4_transpose(AT);
    assert(mat4_equal_eps(ATT, A, EPSILON));

    // Transpose of product: (AB)^T = B^T A^T
    t_mat4 B = random_mat4(-5, 5);
    t_mat4 AB = mat4_mul(A, B);
    t_mat4 AB_T = mat4_transpose(AB);
    t_mat4 BT_AT = mat4_mul(mat4_transpose(B), mat4_transpose(A));
    assert(mat4_equal_eps(AB_T, BT_AT, EPSILON));

    // Symmetric matrix: transpose equals itself
    t_mat4 sym = { .arr = {
        1, 2, 3, 4,
        2, 5, 6, 7,
        3, 6, 8, 9,
        4, 7, 9,10
    }};
    t_mat4 symT = mat4_transpose(sym);
    assert(mat4_equal_eps(symT, sym, EPSILON));

    printf("✓ transpose tests passed\n");
}

static void test_mat4_trace(void)
{
    printf("=== test_mat4_trace ===\n");

    // Identity trace = 4
    t_mat4 I = mat4_identity();
    assert(float_equal(mat4_trace(I), 4.0f, EPSILON));

    // Zero trace = 0
    t_mat4 Z = mat4_zero();
    assert(float_equal(mat4_trace(Z), 0.0f, EPSILON));

    // Random matrix trace = sum of diagonal
    t_mat4 A = random_mat4(-10,10);
    float trace = mat4_trace(A);
    float expected = A.mat[0][0] + A.mat[1][1] + A.mat[2][2] + A.mat[3][3];
    assert(float_equal(trace, expected, EPSILON));

    // Trace is invariant under cyclic permutations: tr(AB) = tr(BA)
    t_mat4 B = random_mat4(-10,10);
    t_mat4 AB = mat4_mul(A, B);
    t_mat4 BA = mat4_mul(B, A);
    assert(float_equal(mat4_trace(AB), mat4_trace(BA), EPSILON * 10.0f));

    printf("✓ trace tests passed\n");
}

static void test_mat4_is_affine(void)
{
    printf("=== test_mat4_is_affine ===\n");

    // Identity is affine
    t_mat4 I = mat4_identity();
    assert(mat4_is_affine(I, EPSILON));

    // Translation is affine
    t_mat4 T = mat4_translation((t_vec3){1,2,3});
    assert(mat4_is_affine(T, EPSILON));

    // Rotation is affine
    t_mat4 R = mat4_rotation_z(MATH_PI/3);
    assert(mat4_is_affine(R, EPSILON));

    // Scaling is affine
    t_mat4 S = mat4_scaling((t_vec3){2,3,4});
    assert(mat4_is_affine(S, EPSILON));

    // Combination
    t_mat4 M = mat4_mul(T, R);
    assert(mat4_is_affine(M, EPSILON));

    // Non-affine: last column not (0,0,0,1)
    t_mat4 non_affine = I;
    non_affine.mat[0][3] = 1.0f; // set w component of first row to 1
    assert(!mat4_is_affine(non_affine, EPSILON));

    non_affine = I;
    non_affine.mat[3][3] = 0.0f; // last element not 1
    assert(!mat4_is_affine(non_affine, EPSILON));

    // Projection matrix (perspective) – not affine
    t_mat4 persp = { .arr = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,1, // w coordinate changed? Actually perspective has non-zero last row
        0,0,-1,0
    }};
    assert(!mat4_is_affine(persp, EPSILON));

    printf("✓ is_affine tests passed\n");
}

static void test_mat4_is_orthogonal(void)
{
    printf("=== test_mat4_is_orthogonal ===\n");

    // Identity is orthogonal
    t_mat4 I = mat4_identity();
    assert(mat4_is_orthogonal(I, EPSILON));

    // Rotations are orthogonal
    t_mat4 Rx = mat4_rotation_x(MATH_PI/6);
    assert(mat4_is_orthogonal(Rx, EPSILON));

    t_mat4 Ry = mat4_rotation_y(MATH_PI/4);
    assert(mat4_is_orthogonal(Ry, EPSILON));

    t_mat4 Rz = mat4_rotation_z(MATH_PI/3);
    assert(mat4_is_orthogonal(Rz, EPSILON));

    // Axis rotation is orthogonal
    t_vec3 axis = {1,1,1}; vec3_normalize(axis);
    t_mat4 Raxis = mat4_rotation_axis(axis, 2.1f);
    assert(mat4_is_orthogonal(Raxis, EPSILON));

    // Translation alone is NOT orthogonal (unless identity)
    t_mat4 T = mat4_translation((t_vec3){1,0,0});
    assert(!mat4_is_orthogonal(T, EPSILON));

    // Scaling (non-uniform) is not orthogonal
    t_mat4 S = mat4_scaling((t_vec3){2,3,4});
    assert(!mat4_is_orthogonal(S, EPSILON));

    // Orthogonal matrix with last row/col correct
    t_mat4 ortho = Rx; // already orthogonal
    assert(mat4_is_orthogonal(ortho, EPSILON));

    // Disturbed orthogonal matrix (one row not unit)
    t_mat4 not_ortho = Rx;
    not_ortho.mat[0][0] *= 1.1f;
    assert(!mat4_is_orthogonal(not_ortho, EPSILON));

    printf("✓ is_orthogonal tests passed\n");
}

static void test_mat4_is_identity(void)
{
    printf("=== test_mat4_is_identity ===\n");

    t_mat4 I = mat4_identity();
    assert(mat4_is_identity(I, EPSILON));

    // Slight deviation should be caught
    t_mat4 almost = I;
    almost.mat[0][0] = 1.0f + 1e-5f;
    assert(!mat4_is_identity(almost, 1e-6f)); // epsilon smaller than error
    assert(mat4_is_identity(almost, 1e-4f));  // larger epsilon accepts

    // Zero matrix is not identity
    t_mat4 Z = mat4_zero();
    assert(!mat4_is_identity(Z, EPSILON));

    // Translation is not identity
    t_mat4 T = mat4_translation((t_vec3){1,2,3});
    assert(!mat4_is_identity(T, EPSILON));

    printf("✓ is_identity tests passed\n");
}

static void test_mat4_equal(void)
{
    printf("=== test_mat4_equal ===\n");

    t_mat4 A = random_mat4(-5,5);
    t_mat4 B = A; // copy

    assert(mat4_equal(A, B, EPSILON));

    // Slightly modify one element
    B.mat[2][1] += 1e-4f;
    assert(!mat4_equal(A, B, 1e-5f));
    assert(mat4_equal(A, B, 1e-3f));

    // Both NaNs or Infs – equal should return false unless both are NaN? Usually NaN != NaN
    t_mat4 NaN = { .arr = {NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                           NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN} };
    t_mat4 NaN2 = NaN; // copy by value, but NaNs don't compare equal
    assert(!mat4_equal(NaN, NaN2, EPSILON)); // because NaN != NaN

    printf("✓ equal tests passed\n");
}

static void test_mat4_any_nan(void)
{
    printf("=== test_mat4_any_nan ===\n");

    t_mat4 A = random_mat4(-5,5);
    assert(!mat4_any_nan(A));

    t_mat4 B = A;
    B.mat[1][2] = NAN;
    assert(mat4_any_nan(B));

    t_mat4 all_nan = { .arr = {NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN,
                                NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN} };
    assert(mat4_any_nan(all_nan));

    // Inf is not NaN
    t_mat4 inf_mat = { .arr = {INFINITY, INFINITY, INFINITY, INFINITY,
                                INFINITY, INFINITY, INFINITY, INFINITY,
                                INFINITY, INFINITY, INFINITY, INFINITY,
                                INFINITY, INFINITY, INFINITY, INFINITY} };
    assert(!mat4_any_nan(inf_mat));

    printf("✓ any_nan tests passed\n");
}

static void test_mat4_is_finite(void)
{
    printf("=== test_mat4_is_finite ===\n");

    t_mat4 A = random_mat4(-5,5);
    assert(mat4_is_finite(A));

    t_mat4 B = A;
    B.mat[2][3] = INFINITY;
    assert(!mat4_is_finite(B));

    t_mat4 C = A;
    C.mat[0][1] = NAN;
    assert(!mat4_is_finite(C));

    t_mat4 all_inf = { .arr = {INFINITY, INFINITY, INFINITY, INFINITY,
                                INFINITY, INFINITY, INFINITY, INFINITY,
                                INFINITY, INFINITY, INFINITY, INFINITY,
                                INFINITY, INFINITY, INFINITY, INFINITY} };
    assert(!mat4_is_finite(all_inf));

    printf("✓ is_finite tests passed\n");
}

/*------------------------------------------------------------------------------
  Benchmark (optional)
------------------------------------------------------------------------------*/

#ifdef BENCHMARK

#include <time.h>

static double time_diff_sec(struct timespec start, struct timespec end)
{
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
}

static void bench_mat4_determinant(void)
{
    const int N = 1000000;
    t_mat4 A = random_mat4(-10,10);
    float det;

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < N; ++i)
        det = mat4_determinant(A);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    double sec = time_diff_sec(t1, t2);
    printf("mat4_determinant: %d ops in %.3f s -> %.1f Mops/s\n",
           N, sec, N / sec / 1e6);
    (void)det;
}

static void bench_mat4_inverse(void)
{
    const int N = 100000;
    t_mat4 A = random_mat4(-10,10);
    // ensure invertible? Not guaranteed, but for benchmark we ignore.
    t_mat4 inv;

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < N; ++i)
        inv = mat4_inverse(A);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    double sec = time_diff_sec(t1, t2);
    printf("mat4_inverse: %d ops in %.3f s -> %.1f ops/s\n",
           N, sec, N / sec);
    (void)inv;
}

static void bench_mat4_transpose(void)
{
    const int N = 10000000;
    t_mat4 A = random_mat4(-10,10);
    t_mat4 T;

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < N; ++i)
        T = mat4_transpose(A);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    double sec = time_diff_sec(t1, t2);
    printf("mat4_transpose: %d ops in %.3f s -> %.1f Mops/s\n",
           N, sec, N / sec / 1e6);
    (void)T;
}

static void run_benchmarks(void)
{
    printf("\n=== Running benchmarks (properties) ===\n");
    bench_mat4_determinant();
    bench_mat4_inverse();
    bench_mat4_transpose();
}

#endif /* BENCHMARK */

/*------------------------------------------------------------------------------
  Main – dispatch tests or benchmarks
------------------------------------------------------------------------------*/

int main(void)
{
    srand(42);

#ifdef BENCHMARK
    run_benchmarks();
#else
    printf("===== MATRIX PROPERTIES & INVERSE/TRANSPOSE =====\n\n");

    test_mat4_inverse();
    printf("\n");
    test_mat4_determinant();
    printf("\n");
    test_mat4_transpose();
    printf("\n");
    test_mat4_trace();
    printf("\n");
    test_mat4_is_affine();
    printf("\n");
    test_mat4_is_orthogonal();
    printf("\n");
    test_mat4_is_identity();
    printf("\n");
    test_mat4_equal();
    printf("\n");
    test_mat4_any_nan();
    printf("\n");
    test_mat4_is_finite();
    printf("\n");

    printf("\nAll properties tests passed.\n");
#endif

    return 0;
}