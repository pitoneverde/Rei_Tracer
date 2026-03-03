// core module test functions

// ====== VEC3 ======

#ifdef QUICK_TEST
#define TEST_ITERATIONS 100
#define STACK_TEST_SIZE 1000
#elif defined(BENCHMARK)
#define TEST_ITERATIONS 10000000
#define STACK_TEST_SIZE 10000000
#else
#define TEST_ITERATIONS 10000
#define STACK_TEST_SIZE 100000
#endif

void test_vec3_angles_direction();
void test_vec3_basic();
void test_vec3_comp();
void test_vec3_compare();
void test_vec3_coordinates();
void test_vec3_create();
void test_vec3_length();
void test_vec3_normalize();
void test_vec3_product();
void test_vec3_project_distance();

// ====== MAT4 ======
void test_mat4_basic();
void test_mat4_decompose();
void test_mat4_properties();
void test_mat4_special();
void test_mat4_transform();
void test_mat4_transformation();

// ====== UTILS ======
#define _GNU_SOURCE
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "core/mat4.h"
#include "core/vec3.h"

bool	float_equal(float a, float b, float eps);
bool	mat4_equal_eps(t_mat4 a, t_mat4 b, float eps);
bool	vec3_equal_eps(t_vec3 a, t_vec3 b, float eps);
void	print_vec3(const char *name, t_vec3 v);
void	print_mat4(const char *name, t_mat4 m);
float	random_float(float min, float max);
t_vec3	random_unit_vec3(void);
t_vec3	random_vec3(float min, float max);
t_vec3	orthogonalize(t_vec3 a, t_vec3 b);
t_mat4	random_mat4(float min, float max);
double	time_diff_sec(struct timespec start, struct timespec end);