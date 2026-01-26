#include "minirt.h"
#include "libft.h"

bool	check_plane(char *str)
{
	if (ft_word_count(str) != 4)
	{
		PRINT_ERR("Error: missing element in line pl\n");
		return (false);
	}
	char	**matrix;
	matrix = ft_split(str, ' ');
	if (ft_strcmp(matrix[0], "pl"))
	{
		PRINT_ERR("Error: missing pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_coordinates(matrix[1]))
	{
		PRINT_ERR("Error: coordinates format wrong in pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_normalizzation_limits(matrix[2]))
	{
		PRINT_ERR("Error: normalizzation wrong in pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_rgb_format(matrix[3]))
	{
		PRINT_ERR("Error: rgb format wrong in pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	mtxfree_str(matrix);
	return (true);
}
