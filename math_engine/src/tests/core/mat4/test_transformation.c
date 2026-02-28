/*==============================================================================
# test_mat4_transformations.c – Transformations tests
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
  Helper functions (identical to previous section – can be moved to a shared .h)
------------------------------------------------------------------------------*/

static inline bool float_equal(float a, float b, float eps)
{
    return fabsf(a - b) < eps;
}

// static float random_float(float min, float max)
// {
//     float r = (float)rand() / RAND_MAX;
//     return min + r * (max - min);
// }

// static t_vec3 random_vec3(float min, float max)
// {
//     return vec3_new(random_float(min, max),
//                     random_float(min, max),
//                     random_float(min, max));
// }

// static t_mat4 random_mat4(float min, float max)
// {
//     t_mat4 m;
//     for (int i = 0; i < 4; ++i)
//         for (int j = 0; j < 4; ++j)
//             m.mat[i][j] = random_float(min, max);
//     return m;
// }

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

static void test_mat4_translation(void)
{
    printf("=== test_mat4_translation ===\n");

    t_vec3 t = {2.0f, -3.0f, 5.0f};
    t_mat4 T = mat4_translation(t);

    // Check structure: last row = (t.x, t.y, t.z, 1), rotation part identity
    assert(float_equal(T.mat[0][0], 1.0f, EPSILON) && float_equal(T.mat[0][1], 0.0f, EPSILON) &&
           float_equal(T.mat[0][2], 0.0f, EPSILON) && float_equal(T.mat[0][3], 0.0f, EPSILON));
    assert(float_equal(T.mat[1][0], 0.0f, EPSILON) && float_equal(T.mat[1][1], 1.0f, EPSILON) &&
           float_equal(T.mat[1][2], 0.0f, EPSILON) && float_equal(T.mat[1][3], 0.0f, EPSILON));
    assert(float_equal(T.mat[2][0], 0.0f, EPSILON) && float_equal(T.mat[2][1], 0.0f, EPSILON) &&
           float_equal(T.mat[2][2], 1.0f, EPSILON) && float_equal(T.mat[2][3], 0.0f, EPSILON));
    assert(float_equal(T.mat[3][0], t.x, EPSILON) && float_equal(T.mat[3][1], t.y, EPSILON) &&
           float_equal(T.mat[3][2], t.z, EPSILON) && float_equal(T.mat[3][3], 1.0f, EPSILON));

    // Transform a point: p' = T * p  (should be p + t)
    t_vec3 p = {1.0f, 2.0f, 3.0f};
    t_vec3 p_trans = mat4_transform_point(T, p);
    t_vec3 expected = vec3_add(p, t);
    assert(vec3_equal(p_trans, expected, EPSILON));

    // Transform a vector (should be unchanged)
    t_vec3 v = {4.0f, 5.0f, 6.0f};
    t_vec3 v_trans = mat4_transform_vector(T, v);
    assert(vec3_equal(v_trans, v, EPSILON));

    // Zero translation
    T = mat4_translation(VEC3_ZERO);
    assert(mat4_equal_eps(T, mat4_identity(), EPSILON));

    // Large translation (should not overflow unreasonably)
    t_vec3 huge = {1e20f, -1e20f, 1e20f};
    T = mat4_translation(huge);
    (void)T;

    printf("✓ translation tests passed\n");
}

static void test_mat4_scaling(void)
{
    printf("=== test_mat4_scaling ===\n");

    t_vec3 s = {2.0f, 3.0f, 4.0f};
    t_mat4 S = mat4_scaling(s);

    // Check structure
    assert(float_equal(S.mat[0][0], s.x, EPSILON) && float_equal(S.mat[0][1], 0.0f, EPSILON) &&
           float_equal(S.mat[0][2], 0.0f, EPSILON) && float_equal(S.mat[0][3], 0.0f, EPSILON));
    assert(float_equal(S.mat[1][0], 0.0f, EPSILON) && float_equal(S.mat[1][1], s.y, EPSILON) &&
           float_equal(S.mat[1][2], 0.0f, EPSILON) && float_equal(S.mat[1][3], 0.0f, EPSILON));
    assert(float_equal(S.mat[2][0], 0.0f, EPSILON) && float_equal(S.mat[2][1], 0.0f, EPSILON) &&
           float_equal(S.mat[2][2], s.z, EPSILON) && float_equal(S.mat[2][3], 0.0f, EPSILON));
    assert(float_equal(S.mat[3][0], 0.0f, EPSILON) && float_equal(S.mat[3][1], 0.0f, EPSILON) &&
           float_equal(S.mat[3][2], 0.0f, EPSILON) && float_equal(S.mat[3][3], 1.0f, EPSILON));

    // Transform a point: p' = S * p
    t_vec3 p = {1.0f, 2.0f, 3.0f};
    t_vec3 p_scaled = mat4_transform_point(S, p);
    t_vec3 expected = vec3_mul_comp(p, s); // component‑wise
    assert(vec3_equal(p_scaled, expected, EPSILON));

    // Transform a vector (same as point)
    t_vec3 v = {4.0f, 5.0f, 6.0f};
    t_vec3 v_scaled = mat4_transform_vector(S, v);
    assert(vec3_equal(v_scaled, vec3_mul_comp(v, s), EPSILON));

    // Uniform scaling (s.x == s.y == s.z)
    s = (t_vec3){5.0f, 5.0f, 5.0f};
    S = mat4_scaling(s);
    p_scaled = mat4_transform_point(S, p);
    expected = vec3_scale(p, 5.0f);
    assert(vec3_equal(p_scaled, expected, EPSILON));

    // Zero scaling (should collapse to zero for points/vectors)
    s = VEC3_ZERO;
    S = mat4_scaling(s);
    p_scaled = mat4_transform_point(S, p);
    assert(vec3_equal(p_scaled, VEC3_ZERO, EPSILON));

    // Negative scaling (reflection)
    s = (t_vec3){-1.0f, 1.0f, 1.0f};
    S = mat4_scaling(s);
    p_scaled = mat4_transform_point(S, p);
    expected = (t_vec3){-p.x, p.y, p.z};
    assert(vec3_equal(p_scaled, expected, EPSILON));

    printf("✓ scaling tests passed\n");
}

static void test_mat4_rotation_x(void)
{
    printf("=== test_mat4_rotation_x ===\n");

    float angle = MATH_PI / 2.0f; // 90°
    t_mat4 R = mat4_rotation_x(angle);

    // Check structure: rotation about x leaves x unchanged, rotates y,z
    // Should be orthogonal with determinant 1
    t_vec3 x_axis = {1,0,0};
    t_vec3 y_axis = {0,1,0};
    t_vec3 z_axis = {0,0,1};

    t_vec3 rx = mat4_transform_vector(R, x_axis);
    t_vec3 ry = mat4_transform_vector(R, y_axis);
    t_vec3 rz = mat4_transform_vector(R, z_axis);

    assert(vec3_equal(rx, x_axis, EPSILON));
    assert(vec3_equal(ry, (t_vec3){0,0,1}, EPSILON)); // y -> z
    assert(vec3_equal(rz, (t_vec3){0,-1,0}, EPSILON)); // z -> -y

    // Determinant should be 1
    float det = mat4_determinant(R);
    assert(float_equal(det, 1.0f, EPSILON));

    // Inverse should be transpose (orthogonal)
    t_mat4 inv = mat4_inverse(R);
    t_mat4 trans = mat4_transpose(R);
    assert(mat4_equal_eps(inv, trans, EPSILON));

    // Rotating by 0 gives identity
    R = mat4_rotation_x(0.0f);
    assert(mat4_equal_eps(R, mat4_identity(), EPSILON));

    // Rotating by 2π gives identity
    R = mat4_rotation_x(2.0f * MATH_PI);
    assert(mat4_equal_eps(R, mat4_identity(), 1e-5f)); // allow some FP error

    // Rotating by -90° is inverse
    t_mat4 Rneg = mat4_rotation_x(-MATH_PI/2.0f);
    t_mat4 R90 = mat4_rotation_x(MATH_PI/2.0f);
    t_mat4 prod = mat4_mul(R90, Rneg);
    assert(mat4_equal_eps(prod, mat4_identity(), EPSILON));

    printf("✓ rotation_x tests passed\n");
}

static void test_mat4_rotation_y(void)
{
    printf("=== test_mat4_rotation_y ===\n");

    float angle = MATH_PI / 2.0f;
    t_mat4 R = mat4_rotation_y(angle);

    t_vec3 x_axis = {1,0,0};
    t_vec3 y_axis = {0,1,0};
    t_vec3 z_axis = {0,0,1};

    t_vec3 rx = mat4_transform_vector(R, x_axis);
    t_vec3 ry = mat4_transform_vector(R, y_axis);
    t_vec3 rz = mat4_transform_vector(R, z_axis);

    assert(vec3_equal(rx, (t_vec3){0,0,-1}, EPSILON)); // x -> -z
    assert(vec3_equal(ry, y_axis, EPSILON));
    assert(vec3_equal(rz, (t_vec3){1,0,0}, EPSILON));  // z -> x

    float det = mat4_determinant(R);
    assert(float_equal(det, 1.0f, EPSILON));

    t_mat4 inv = mat4_inverse(R);
    t_mat4 trans = mat4_transpose(R);
    assert(mat4_equal_eps(inv, trans, EPSILON));

    // Rotating by 0 gives identity
    R = mat4_rotation_y(0.0f);
    assert(mat4_equal_eps(R, mat4_identity(), EPSILON));

    printf("✓ rotation_y tests passed\n");
}

static void test_mat4_rotation_z(void)
{
    printf("=== test_mat4_rotation_z ===\n");

    float angle = MATH_PI / 2.0f;
    t_mat4 R = mat4_rotation_z(angle);

    t_vec3 x_axis = {1,0,0};
    t_vec3 y_axis = {0,1,0};
    t_vec3 z_axis = {0,0,1};

    t_vec3 rx = mat4_transform_vector(R, x_axis);
    t_vec3 ry = mat4_transform_vector(R, y_axis);
    t_vec3 rz = mat4_transform_vector(R, z_axis);

    assert(vec3_equal(rx, (t_vec3){0,1,0}, EPSILON)); // x -> y
    assert(vec3_equal(ry, (t_vec3){-1,0,0}, EPSILON)); // y -> -x
    assert(vec3_equal(rz, z_axis, EPSILON));

    float det = mat4_determinant(R);
    assert(float_equal(det, 1.0f, EPSILON));

    t_mat4 inv = mat4_inverse(R);
    t_mat4 trans = mat4_transpose(R);
    assert(mat4_equal_eps(inv, trans, EPSILON));

    // Rotating by 0 gives identity
    R = mat4_rotation_z(0.0f);
    assert(mat4_equal_eps(R, mat4_identity(), EPSILON));

    printf("✓ rotation_z tests passed\n");
}

static void test_mat4_rotation_axis(void)
{
    printf("=== test_mat4_rotation_axis ===\n");

    // Rotate around X axis by 90° using axis = (1,0,0)
    t_vec3 axis = {1,0,0};
    float angle = MATH_PI / 2.0f;
    t_mat4 R = mat4_rotation_axis(axis, angle);

    t_vec3 x_axis = {1,0,0};
    t_vec3 y_axis = {0,1,0};
    t_vec3 z_axis = {0,0,1};

    t_vec3 rx = mat4_transform_vector(R, x_axis);
    t_vec3 ry = mat4_transform_vector(R, y_axis);
    t_vec3 rz = mat4_transform_vector(R, z_axis);

    assert(vec3_equal(rx, x_axis, EPSILON));
    assert(vec3_equal(ry, (t_vec3){0,0,1}, EPSILON));
    assert(vec3_equal(rz, (t_vec3){0,-1,0}, EPSILON));

    // Determinant = 1
    float det = mat4_determinant(R);
    assert(float_equal(det, 1.0f, EPSILON));

    // Inverse = transpose (orthogonal)
    t_mat4 inv = mat4_inverse(R);
    t_mat4 trans = mat4_transpose(R);
    assert(mat4_equal_eps(inv, trans, EPSILON));

    // Rotate around arbitrary axis
    axis = (t_vec3){1,1,1}; vec3_normalize(axis);
    angle = MATH_PI / 3.0f; // 60°
    R = mat4_rotation_axis(axis, angle);

    // Check that axis itself is unchanged
    t_vec3 axis_rot = mat4_transform_vector(R, axis);
    assert(vec3_equal(axis_rot, axis, EPSILON));

    // Check that a vector perpendicular to axis rotates correctly
    t_vec3 perp = (t_vec3){1,-1,0}; // perpendicular to (1,1,1)? Dot = 1-1+0=0, yes
    vec3_normalize(perp);
    t_vec3 perp_rot = mat4_transform_vector(R, perp);

    // Angle between perp and perp_rot should be 60°
    float dot = vec3_dot(perp, perp_rot);
    float cos_angle = dot; // both unit
    assert(float_equal(cos_angle, cosf(angle), 1e-5f));

    // Rotating by 0 gives identity
    R = mat4_rotation_axis(axis, 0.0f);
    assert(mat4_equal_eps(R, mat4_identity(), EPSILON));

    // Rotating by 2π gives identity (approximately)
    R = mat4_rotation_axis(axis, 2.0f * MATH_PI);
    assert(mat4_equal_eps(R, mat4_identity(), 1e-5f));

    // Invalid axis (zero) – should maybe return identity or handle gracefully
    // We'll just ensure it doesn't crash
    t_vec3 zero_axis = VEC3_ZERO;
    R = mat4_rotation_axis(zero_axis, angle);
    (void)R;

    printf("✓ rotation_axis tests passed\n");
}

static void test_mat4_look_at(void)
{
    printf("=== test_mat4_look_at ===\n");

    // Standard look-at: eye at (0,0,0), target at (0,0,-1), up = (0,1,0)
    // This should produce identity (camera looks down -z, y up)
    t_vec3 eye    = {0,0,0};
    t_vec3 target = {0,0,-1};
    t_vec3 up     = {0,1,0};
    t_mat4 view = mat4_look_at(eye, target, up);
    t_mat4 expected = mat4_identity();
    assert(mat4_equal_eps(view, expected, EPSILON));

    // Look from (0,0,5) to origin – camera at +z looking towards -z
    // Should be a translation by -5 in z (since we move world so that camera goes to origin)
    eye    = (t_vec3){0,0,5};
    target = (t_vec3){0,0,0};
    up     = (t_vec3){0,1,0};
    view = mat4_look_at(eye, target, up);

    // Expected: rotation part identity (since direction is still -z), translation by -eye
    // Actually, view matrix should map eye to origin, so T = translation(-eye)
    t_mat4 T = mat4_translation((t_vec3){0,0,-5});
    assert(mat4_equal_eps(view, T, EPSILON));

    // Check that a point at world origin transforms to camera space at (0,0,-5)?? Wait,
    // In camera space, the camera is at origin looking down -z, so world origin should be at (0,0,-distance)
    // With eye at (0,0,5) looking at (0,0,0), the direction is -z. So view matrix = translation(-5,0,0)? No,
    // It should be translation by (-0, -0, -5) = (0,0,-5). Then world origin (0,0,0) becomes (0,0,-5) in camera space,
    // which is correct: the camera at (0,0,5) sees origin 5 units in front (down -z).
    t_vec3 p_cam = mat4_transform_point(view, (t_vec3){0,0,0});
    t_vec3 expected_p = (t_vec3){0,0,-5};
    assert(vec3_equal(p_cam, expected_p, EPSILON));

    // Now look from (1,2,3) to (4,5,6) with up = (0,1,0)
    eye    = (t_vec3){1,2,3};
    target = (t_vec3){4,5,6};
    up     = (t_vec3){0,1,0};
    view = mat4_look_at(eye, target, up);

    // Verify properties:
    // 1. The forward vector (z-axis in camera space) should point from eye to target.
    t_vec3 f = vec3_normalize(vec3_sub(target, eye)); // world forward
    // In view matrix, the third row (since we use row-major? careful) Actually our convention:
    // mat4_from_basis places right, up, forward in rows 0,1,2, and translation in row 3.
    // For look_at, the matrix should transform world to camera. So the camera axes (right, up, -forward) should
    // be the rows of the rotation part? Let's test: transform the world forward vector by the view matrix.
    // The view matrix should map world forward to (0,0,-1) (camera's -z).
    t_vec3 world_fwd = f;
    t_vec3 cam_fwd = mat4_transform_vector(view, world_fwd);
    t_vec3 expected_cam_fwd = (t_vec3){0,0,-1};
    assert(vec3_equal(cam_fwd, expected_cam_fwd, EPSILON));

    // 2. The world up vector should be mapped to camera up (y) in the plane perpendicular to forward.
    // But not exactly, because up is projected onto the plane. Instead, we can check that the transformed up
    // has zero x and positive y (if up is (0,1,0) world).
    t_vec3 world_up = up;
    t_vec3 cam_up = mat4_transform_vector(view, world_up);
    // cam_up should lie in the y-z plane? Actually with our look_at, the camera's y axis is the projection of world up
    // onto the plane orthogonal to forward. So we expect cam_up.x ≈ 0, cam_up.y positive.
    assert(float_equal(cam_up.x, 0.0f, 1e-5f));
    assert(cam_up.y > 0);
    // Also, the camera's right vector should be cross(up, forward) (or forward x up?). For a right-handed system,
    // typically right = up x forward (if forward is -z). Let's compute expected right:
    t_vec3 expected_right = vec3_cross(up, f); // because we want right = up x f (to get orthogonal basis)
    vec3_normalize(expected_right);
    t_vec3 cam_right = mat4_transform_vector(view, expected_right);
    // The camera right should map to (1,0,0)
    t_vec3 expected_cam_right = (t_vec3){1,0,0};
    assert(vec3_equal(cam_right, expected_cam_right, EPSILON));

    // Edge: degenerate case when target == eye (should probably return identity or something)
    // Ensure it doesn't crash.
    view = mat4_look_at(eye, eye, up);
    (void)view;

    // Edge: up parallel to forward (gimbal lock) – should still produce a matrix (maybe with some axis)
    up = vec3_normalize(vec3_sub(target, eye)); // up = forward
    view = mat4_look_at(eye, target, up);
    (void)view;

    printf("✓ look_at tests passed\n");
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

static void bench_mat4_translation(void)
{
    const int N = 10000000;
    t_vec3 t = {1,2,3};
    t_mat4 M;

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < N; ++i)
        M = mat4_translation(t);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    double sec = time_diff_sec(t1, t2);
    printf("mat4_translation: %d ops in %.3f s -> %.1f Mops/s\n",
           N, sec, N / sec / 1e6);
    (void)M;
}

static void bench_mat4_rotation_axis(void)
{
    const int N = 1000000;
    t_vec3 axis = {1,1,1};
    vec3_normalize(&axis);
    float angle = MATH_PI / 3.0f;
    t_mat4 M;

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < N; ++i)
        M = mat4_rotation_axis(axis, angle);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    double sec = time_diff_sec(t1, t2);
    printf("mat4_rotation_axis: %d ops in %.3f s -> %.1f Mops/s\n",
           N, sec, N / sec / 1e6);
    (void)M;
}

static void bench_mat4_look_at(void)
{
    const int N = 1000000;
    t_vec3 eye    = {1,2,3};
    t_vec3 target = {4,5,6};
    t_vec3 up     = {0,1,0};
    t_mat4 M;

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < N; ++i)
        M = mat4_look_at(eye, target, up);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    double sec = time_diff_sec(t1, t2);
    printf("mat4_look_at: %d ops in %.3f s -> %.1f Mops/s\n",
           N, sec, N / sec / 1e6);
    (void)M;
}

static void run_benchmarks(void)
{
    printf("\n=== Running benchmarks (transformations) ===\n");
    bench_mat4_translation();
    bench_mat4_rotation_axis();
    bench_mat4_look_at();
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
    printf("===== TRANSFORMATIONS (RT ESSENTIALS) =====\n\n");

    test_mat4_translation();
    printf("\n");
    test_mat4_scaling();
    printf("\n");
    test_mat4_rotation_x();
    printf("\n");
    test_mat4_rotation_y();
    printf("\n");
    test_mat4_rotation_z();
    printf("\n");
    test_mat4_rotation_axis();
    printf("\n");
    test_mat4_look_at();
    printf("\n");

    printf("\nAll transformations tests passed.\n");
#endif

    return 0;
}