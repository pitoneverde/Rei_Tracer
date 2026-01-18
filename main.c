#include "minirt.h"
#include <math.h>

int main(int argc, char **argv)
{
	t_element	data_file = {0};
	if (argc > 2)
		PRINT_ERR("Invalid argument count: %d", argc);
	parse_input(argc, argv, data_file);
    // init();
    // launch();
    // cleanup();
    return (0);
}
