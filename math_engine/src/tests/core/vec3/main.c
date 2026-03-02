#include "core/test.h"

int main(void)
{
	test_vec3_angles_direction();
	test_vec3_basic();
	test_vec3_comp();
	test_vec3_compare();
	test_vec3_coordinates();
	test_vec3_create();
	test_vec3_length();
	test_vec3_normalize();
	test_vec3_product();
	test_vec3_project_distance();
    printf("✓ ALL VEC3 TESTS PASSED!\n");
	return 0;
}