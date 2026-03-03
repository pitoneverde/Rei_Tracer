#define _GNU_SOURCE
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "core/test.h"
#include "utils/math_constants.h"

inline bool float_equal(float a, float b, float eps)
{
    return fabsf(a - b) < eps;
}

float random_float(float min, float max)
{
    double r = (double)rand() / RAND_MAX;
    return (float)(min + r * (max - min));
}

t_vec3 random_vec3(float min, float max)
{
    return vec3_new(random_float(min, max),
                    random_float(min, max),
                    random_float(min, max));
}

t_mat4 random_mat4(float min, float max)
{
    t_mat4 m;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m.mat[i][j] = random_float(min, max);
    return m;
}

bool mat4_equal_eps(t_mat4 a, t_mat4 b, float eps)
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (!float_equal(a.mat[i][j], b.mat[i][j], eps))
                return false;
    return true;
}

void print_mat4(const char *name, t_mat4 m)
{
    printf("%s:\n", name);
    for (int i = 0; i < 4; ++i)
        printf("  [ %7.3f %7.3f %7.3f %7.3f ]\n",
               m.mat[i][0], m.mat[i][1], m.mat[i][2], m.mat[i][3]);
}

bool vec3_equal_eps(t_vec3 a, t_vec3 b, float eps)
{
    return float_equal(a.x, b.x, eps) &&
           float_equal(a.y, b.y, eps) &&
           float_equal(a.z, b.z, eps);
}

void print_vec3(const char *name, t_vec3 v)
{
    printf("%s: (%f, %f, %f)\n", name, v.x, v.y, v.z);
}

t_vec3 random_unit_vec3(void)
{
    // Generate random point on unit sphere
    float theta = random_float(0.0f, MATH_TAU);
    float phi = acosf(random_float(-1.0f, 1.0f));
    return vec3_new(
        sinf(phi) * cosf(theta),
        sinf(phi) * sinf(theta),
        cosf(phi)
    );
}

// Orthogonalize b relative to a (Gram-Schmidt)
t_vec3 orthogonalize(t_vec3 a, t_vec3 b)
{
    float dot = vec3_dot(a, b);
    float length_sq = vec3_length_sq(a);
    if (length_sq < 1e-12f) return b;
    float scale = dot / length_sq;
    return vec3_sub(b, vec3_scale(a, scale));
}

double time_diff_sec(struct timespec start, struct timespec end)
{
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) * 1e-9;
}
