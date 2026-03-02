/*==============================================================================
# test_special.c – Special RT operations & utility tests
==============================================================================*/

#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "core/mat4.h"
#include "core/vec3.h"
#include "utils/math_constants.h"
#include "core/test.h"

#ifndef EPSILON
# define EPSILON 1e-6f
#endif

/*------------------------------------------------------------------------------
  Unit tests
------------------------------------------------------------------------------*/

static void test_mat4_align_vectors(void)
{
    printf("=== test_mat4_align_vectors ===\n");

    t_vec3 from, to;
    t_mat4 R;

    // Same direction
    from = (t_vec3){1,0,0};
    to   = (t_vec3){1,0,0};
    R = mat4_align_vectors(from, to);
    assert(mat4_equal_eps(R, mat4_identity(), EPSILON));

    // Opposite direction (180°)
    from = (t_vec3){1,0,0};
    to   = (t_vec3){-1,0,0};
    R = mat4_align_vectors(from, to);
    // Should rotate 180° about any perpendicular axis, e.g., Y axis
    // Result should map (1,0,0) to (-1,0,0)
    t_vec3 v = mat4_transform_vector(R, from);
    assert(vec3_equal_eps(v, to, EPSILON));
    // Check orthogonality and determinant 1
    assert(mat4_is_orthogonal(R, EPSILON));
    assert(float_equal(mat4_determinant(R), 1.0f, EPSILON));

    // 90° about Z: from X to Y
    from = (t_vec3){1,0,0};
    to   = (t_vec3){0,1,0};
    R = mat4_align_vectors(from, to);
    v = mat4_transform_vector(R, from);
    assert(vec3_equal_eps(v, to, EPSILON));
    // Check orthogonality
    assert(mat4_is_orthogonal(R, EPSILON));

    // Arbitrary vectors (not unit)
    from = (t_vec3){2,0,0};
    to   = (t_vec3){0,3,0};
    R = mat4_align_vectors(from, to);
    v = mat4_transform_vector(R, vec3_normalize(from));
    t_vec3 to_norm = vec3_normalize(to);
    assert(vec3_equal_eps(v, to_norm, EPSILON));

    // 3D arbitrary: from (1,1,0) to (0,1,1)
    from = (t_vec3){1,1,0};
    to   = (t_vec3){0,1,1};
    R = mat4_align_vectors(from, to);
    v = mat4_transform_vector(R, vec3_normalize(from));
    assert(vec3_equal_eps(v, vec3_normalize(to), EPSILON));
    assert(mat4_is_orthogonal(R, EPSILON));

    // Edge: zero from vector – should handle (maybe return identity or something)
    from = VEC3_ZERO;
    to   = (t_vec3){1,0,0};
    R = mat4_align_vectors(from, to);
    // Implementation-dependent, but should not crash
    (void)R;

    // Edge: zero to vector
    from = (t_vec3){1,0,0};
    to   = VEC3_ZERO;
    R = mat4_align_vectors(from, to);
    (void)R;

    // Edge: both zero
    R = mat4_align_vectors(VEC3_ZERO, VEC3_ZERO);
    (void)R;

    // Edge: parallel but opposite with near-zero vectors (should still work)
    from = (t_vec3){1e-20f, 0, 0};
    to   = (t_vec3){-1e-20f, 0, 0};
    R = mat4_align_vectors(from, to);
    v = mat4_transform_vector(R, (t_vec3){1,0,0});
    assert(vec3_equal_eps(v, (t_vec3){-1,0,0}, EPSILON));

    printf("✓ align_vectors tests passed\n");
}

static void test_mat4_billboard(void)
{
    printf("=== test_mat4_billboard ===\n");

    t_vec3 pos = {0,0,0};
    t_vec3 cam_pos, cam_up;
    t_mat4 B;

    // Camera at (0,0,1) looking at origin, up = Y
    cam_pos = (t_vec3){0,0,1};
    cam_up  = (t_vec3){0,1,0};
    B = mat4_billboard(pos, cam_pos, cam_up);
    // Billboard should rotate so that object's local Z points towards camera? 
    // Typically billboard makes object face camera, i.e., local Z (forward) points to camera.
    // So after transform, the object's Z axis (0,0,1) should point towards camera.
    // We can test by transforming a point in object space (e.g., (0,0,1)) and see it aligns with direction from object to camera.
    t_vec3 obj_forward = (t_vec3){0,0,1};
    t_vec3 world_forward = mat4_transform_vector(B, obj_forward);
    t_vec3 to_camera = vec3_normalize(vec3_sub(cam_pos, pos));
    assert(vec3_equal_eps(world_forward, to_camera, EPSILON));

    // Check that local Y stays as close as possible to world up (billboard constraint)
    t_vec3 obj_up = (t_vec3){0,1,0};
    t_vec3 world_up = mat4_transform_vector(B, obj_up);
    // world_up should be orthogonal to to_camera and point generally upward
    assert(float_equal(vec3_dot(world_up, to_camera), 0.0f, EPSILON));
    // world_up should have positive dot with original world up (0,1,0) if possible
    assert(vec3_dot(world_up, cam_up) > 0);

    // Camera at (1,1,1) looking at origin
    pos = (t_vec3){0,0,0};
    cam_pos = (t_vec3){1,1,1};
    cam_up  = (t_vec3){0,1,0};
    B = mat4_billboard(pos, cam_pos, cam_up);
    obj_forward = (t_vec3){0,0,1};
    world_forward = mat4_transform_vector(B, obj_forward);
    to_camera = vec3_normalize(vec3_sub(cam_pos, pos));
    assert(vec3_equal_eps(world_forward, to_camera, EPSILON));

    // Check orthogonality (should be orthogonal)
    assert(mat4_is_orthogonal(B, EPSILON));

    // Edge: camera at same position as object (undefined direction)
    cam_pos = pos;
    B = mat4_billboard(pos, cam_pos, cam_up);
    // Should handle (maybe identity) – just ensure no crash
    (void)B;

    // Edge: up parallel to view direction (gimbal lock) – should still produce valid orientation
    cam_pos = (t_vec3){0,1,0}; // directly above
    cam_up  = (t_vec3){0,1,0}; // up = view direction
    B = mat4_billboard(pos, cam_pos, cam_up);
    // Then the view direction is (0,1,0). The billboard's up should be something orthogonal, e.g., (1,0,0) or (0,0,1).
    obj_forward = (t_vec3){0,0,1};
    world_forward = mat4_transform_vector(B, obj_forward);
    to_camera = vec3_normalize(vec3_sub(cam_pos, pos)); // (0,1,0)
    assert(vec3_equal_eps(world_forward, to_camera, EPSILON));
    // local up (0,1,0) should map to a vector orthogonal to forward
    obj_up = (t_vec3){0,1,0};
    world_up = mat4_transform_vector(B, obj_up);
    assert(float_equal(vec3_dot(world_up, to_camera), 0.0f, EPSILON));
    // The billboard's up should be perpendicular to forward, and its direction should be chosen by some rule.
    // Possibly it uses cross(up, view) as right, then up = cross(view, right).
    // We'll just check it's orthogonal.

    printf("✓ billboard tests passed\n");
}

static void test_mat4_lerp(void)
{
    printf("=== test_mat4_lerp ===\n");

    t_mat4 A, B, L;

    // Simple case: identity to identity
    A = mat4_identity();
    B = mat4_identity();
    L = mat4_lerp(A, B, 0.5f);
    assert(mat4_equal_eps(L, A, EPSILON));

    // Translation matrices
    A = mat4_translation((t_vec3){1,2,3});
    B = mat4_translation((t_vec3){4,5,6});
    L = mat4_lerp(A, B, 0.25f);
    t_mat4 expected = mat4_translation((t_vec3){1.75f, 2.75f, 3.75f}); // A + 0.25*(B-A)
    assert(mat4_equal_eps(L, expected, EPSILON));

    // Scaling matrices
    A = mat4_scaling((t_vec3){2,3,4});
    B = mat4_scaling((t_vec3){6,5,8});
    L = mat4_lerp(A, B, 0.5f);
    expected = mat4_scaling((t_vec3){4,4,6}); // linear interpolation of scale factors
    assert(mat4_equal_eps(L, expected, EPSILON));

    // Rotation matrices (should interpolate rotations properly, but linear interpolation may not preserve orthogonality)
    A = mat4_rotation_z(0.0f);
    B = mat4_rotation_z(MATH_PI); // 180°
    L = mat4_lerp(A, B, 0.5f);
    // Linear interpolation of rotation matrices gives a matrix that may not be a pure rotation.
    // But we can test that the interpolation at t=0.5 gives the matrix halfway in terms of angle.
    // For rotation about Z, the matrix entries are cos(theta), sin(theta), etc.
    // At theta = 90°, cos=0, sin=1. So expected for 90°:
    // [0, -1, 0, 0; 1, 0, 0, 0; 0,0,1,0; 0,0,0,1]
    t_mat4 R90 = mat4_rotation_z(MATH_PI/2);
    assert(mat4_equal_eps(L, R90, 1e-5f));

    // Check interpolation extremes
    L = mat4_lerp(A, B, 0.0f);
    assert(mat4_equal_eps(L, A, EPSILON));
    L = mat4_lerp(A, B, 1.0f);
    assert(mat4_equal_eps(L, B, EPSILON));

    // Combined affine matrices
    A = mat4_mul(mat4_translation((t_vec3){1,0,0}), mat4_rotation_z(0));
    B = mat4_mul(mat4_translation((t_vec3){0,1,0}), mat4_rotation_z(MATH_PI/2));
    L = mat4_lerp(A, B, 0.5f);
    // Expected translation: (0.5, 0.5, 0)
    t_vec3 trans = mat4_get_translation(L);
    assert(vec3_equal_eps(trans, (t_vec3){0.5f, 0.5f, 0.0f}, EPSILON));
    // Expected rotation: 45° about Z
    t_mat4 R45 = mat4_rotation_z(MATH_PI/4);
    // Extract rotation part (upper 3x3) from L and compare to R45's upper 3x3
    t_mat4 L_rot_part = { .mat = {
        {L.mat[0][0], L.mat[0][1], L.mat[0][2], 0},
        {L.mat[1][0], L.mat[1][1], L.mat[1][2], 0},
        {L.mat[2][0], L.mat[2][1], L.mat[2][2], 0},
        {0,0,0,1}
    }};
    t_mat4 R45_upper = { .mat = {
        {R45.mat[0][0], R45.mat[0][1], R45.mat[0][2], 0},
        {R45.mat[1][0], R45.mat[1][1], R45.mat[1][2], 0},
        {R45.mat[2][0], R45.mat[2][1], R45.mat[2][2], 0},
        {0,0,0,1}
    }};
    assert(mat4_equal_eps(L_rot_part, R45_upper, 1e-5f));

    // Edge: t outside [0,1] – should clamp? Usually lerp is defined for t in [0,1], but implementation may not clamp.
    // We'll just call with t=1.5 and see if it doesn't crash.
    L = mat4_lerp(A, B, 1.5f);
    (void)L;

    // Edge: NaN/inf t
    L = mat4_lerp(A, B, NAN);
    (void)L;
    L = mat4_lerp(A, B, INFINITY);
    (void)L;

    printf("✓ lerp tests passed\n");
}

static void test_mat4_to_float_array(void)
{
    printf("=== test_mat4_to_float_array ===\n");

    t_mat4 M = random_mat4(-10, 10);
    float arr[16];
    mat4_to_float_array(M, arr);

    // Compare with mat4_from_float_array to ensure round-trip
    t_mat4 M2 = mat4_from_float_array(arr);
    assert(mat4_equal_eps(M, M2, EPSILON));

    // Edge: matrix with NaN/Inf
    t_mat4 nan_mat = { .arr = {NAN, NAN, NAN, NAN,
                                NAN, NAN, NAN, NAN,
                                NAN, NAN, NAN, NAN,
                                NAN, NAN, NAN, NAN} };
    mat4_to_float_array(nan_mat, arr);
    // just ensure no crash
    (void)arr;

    t_mat4 inf_mat = { .arr = {INFINITY, INFINITY, INFINITY, INFINITY,
                                INFINITY, INFINITY, INFINITY, INFINITY,
                                INFINITY, INFINITY, INFINITY, INFINITY,
                                INFINITY, INFINITY, INFINITY, INFINITY} };
    mat4_to_float_array(inf_mat, arr);
    (void)arr;

    printf("✓ to_float_array tests passed\n");
}

/*------------------------------------------------------------------------------
  Combined edge case test
------------------------------------------------------------------------------*/

static void test_special_edge_cases(void)
{
    printf("=== test_special_edge_cases ===\n");

    // align_vectors with near-zero vectors
    t_vec3 tiny = {1e-30f, 0, 0};
    t_vec3 huge = {1e30f, 0, 0};
    t_mat4 R = mat4_align_vectors(tiny, huge);
    (void)R;

    // billboard with camera at same position
    t_mat4 B = mat4_billboard((t_vec3){0,0,0}, (t_vec3){0,0,0}, (t_vec3){0,1,0});
    (void)B;

    // lerp with NaN matrices
    t_mat4 nan_mat = { .arr = {NAN, NAN, NAN, NAN,
                                NAN, NAN, NAN, NAN,
                                NAN, NAN, NAN, NAN,
                                NAN, NAN, NAN, NAN} };
    t_mat4 I = mat4_identity();
    t_mat4 L = mat4_lerp(nan_mat, I, 0.5f);
    (void)L;

    // to_float_array with null output? Not possible, but we can pass valid.

    printf("✓ special edge cases passed\n");
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

static void bench_mat4_align_vectors(void)
{
    const int N = 1000000;
    t_vec3 from = {1,2,3};
    t_vec3 to   = {4,5,6};
    t_mat4 R;

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < N; ++i)
        R = mat4_align_vectors(from, to);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    double sec = time_diff_sec(t1, t2);
    printf("mat4_align_vectors: %d ops in %.3f s -> %.1f ops/s\n",
           N, sec, N / sec);
    (void)R;
}

static void bench_mat4_billboard(void)
{
    const int N = 1000000;
    t_vec3 pos = {0,0,0};
    t_vec3 cam = {1,2,3};
    t_vec3 up  = {0,1,0};
    t_mat4 B;

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < N; ++i)
        B = mat4_billboard(pos, cam, up);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    double sec = time_diff_sec(t1, t2);
    printf("mat4_billboard: %d ops in %.3f s -> %.1f ops/s\n",
           N, sec, N / sec);
    (void)B;
}

static void bench_mat4_lerp(void)
{
    const int N = 1000000;
    t_mat4 A = random_mat4(-10,10);
    t_mat4 B = random_mat4(-10,10);
    float t = 0.3f;
    t_mat4 L;

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < N; ++i)
        L = mat4_lerp(A, B, t);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    double sec = time_diff_sec(t1, t2);
    printf("mat4_lerp: %d ops in %.3f s -> %.1f ops/s\n",
           N, sec, N / sec);
    (void)L;
}

static void bench_mat4_to_float_array(void)
{
    const int N = 10000000;
    t_mat4 M = random_mat4(-10,10);
    float arr[16];

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < N; ++i)
        mat4_to_float_array(M, arr);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    double sec = time_diff_sec(t1, t2);
    printf("mat4_to_float_array: %d ops in %.3f s -> %.1f Mops/s\n",
           N, sec, N / sec / 1e6);
}

static void run_benchmarks(void)
{
    printf("\n=== Running benchmarks (special & utility) ===\n");
    bench_mat4_align_vectors();
    bench_mat4_billboard();
    bench_mat4_lerp();
    bench_mat4_to_float_array();
}

#endif /* BENCHMARK */

/*------------------------------------------------------------------------------
  Main – dispatch tests or benchmarks
------------------------------------------------------------------------------*/

void test_mat4_special()
{
    srand(42);

#ifdef BENCHMARK
    run_benchmarks();
#else
    printf("===== SPECIAL RT OPERATIONS & UTILITY =====\n\n");

    test_mat4_align_vectors();
    printf("\n");
    test_mat4_billboard();
    printf("\n");
    test_mat4_lerp();
    printf("\n");
    test_mat4_to_float_array();
    printf("\n");
    test_special_edge_cases();
    printf("\n");

    printf("\nAll special & utility tests passed.\n");
#endif
}