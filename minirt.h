#ifndef MINIRT_H
# define MINIRT_H 1

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
// #include "libft.h"
#include "minirt_data.h"

// Error: message
#define PRINT_ERR(fmt, ...) \
	do {\
		fprintf(stderr, "Error\n @ %s:%d in %s() " fmt "\n", \
		 __FILE__, __LINE__, __func__, ##__VA_ARGS__);\
	} while(0);

void    parse_input(int argc, char **argv);
#endif