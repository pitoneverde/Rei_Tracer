#include "core/test.h"

int main()
{
	test_mat4_basic();
	// test_mat4_decompose();
	test_mat4_properties();
	// test_mat4_special();
	test_mat4_transform();
	test_mat4_transformation();
#ifdef BENCHMARK
	printf("✓ ALL MAT4 BECNHMARKS COMPLETE!\n");
#else
	printf("✓ ALL MAT4 TESTS PASSED!\n");
#endif
	return 0;
}