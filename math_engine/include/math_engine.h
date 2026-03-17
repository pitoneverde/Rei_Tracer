#ifndef MATH_ENGINE_H
# define MATH_ENGINE_H

// master header
#define _GNU_SOURCE
#include <math.h>

#include "core/vec3.h"
#include "core/mat4.h"
#include "core/test.h"
#include "core/color.h"
#include "core/constants.h"

#include "utils/common.h"
#include "utils/debug.h"
#include "utils/math_constants.h"

#include "geometry/camera.h"

// modify this when supporting new geometry
typedef struct s_math
{
	t_camera_math	camera;
	// t_ambient_math	*ambient;
	// t_light_math	*lights;
	// t_sphere_math	*spheres;
	// t_plane_math		*planes;
	// t_cylinder_math	*cylinders;
}	t_math;

// ===== TEST SUITE =====
// void test_vec3();
// void test_mat4();
// void test_color();

#endif