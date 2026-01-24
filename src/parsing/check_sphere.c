#include "minirt.h"
#include "libft.h"

bool	check_sphere(char *str)
{
	if (ft_word_count(str) != 4)
	{
		PRINT_ERR("Error: missing element in line sp\n");
		return (false);
	}
	char	**matrix;
	matrix = ft_split(str, ' ');
	print_debug_matrix(matrix);
	printf("[%s]\n", matrix[0]);
	if (ft_strcmp(matrix[0], "sp"))
	{
		PRINT_ERR("Error: missing sp\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_coordinates(matrix[1]))
	{
		PRINT_ERR("Error: coordinates format wrong in sp\n");
		mtxfree_str(matrix);
		return (false);
	}
	double val;
	if(!convertable_double(&val, matrix[2]))
	{
		PRINT_ERR("Error: sphere diameter wrong in sp\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_rgb_format(matrix[3]))
	{
		PRINT_ERR("Error: rgb format wrong in sp\n");
		mtxfree_str(matrix);
		return (false);
	}
	mtxfree_str(matrix);
	return (true);
}
