#include "minirt.h"
#include "libft.h"

bool	check_cylinder(char *str)
{
	if (ft_word_count(str) != 6)
	{
		PRINT_ERR("Error: missing element in line cy\n");
		return (false);
	}
	char	**matrix;
	matrix = ft_split(str, ' ');
	print_debug_matrix(matrix);
	printf("[%s]\n", matrix[0]);
	if (ft_strcmp(matrix[0], "cy"))
	{
		PRINT_ERR("Error: missing pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_coordinates(matrix[1]))
	{
		PRINT_ERR("Error: coordinates format wrong in cy\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_normalizzation_limits(matrix[2]))
	{
		PRINT_ERR("Error: normalizzation wrong in pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_cy_diameter(matrix[3])) // da fare
	{
		PRINT_ERR("Error: cylinder diameter\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_cy_height(matrix[4])) //da fare
	{
		PRINT_ERR("Error: cylinder height\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_rgb_format(matrix[5]))
	{
		PRINT_ERR("Error: rgb format wrong in cy\n");
		mtxfree_str(matrix);
		return (false);
	}
	mtxfree_str(matrix);
	return (true);
}
