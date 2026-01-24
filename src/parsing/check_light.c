#include "minirt.h"
#include "libft.h"

bool	check_bringhtness_limits(char *s)
{
	double	value;

	if (!convertable_double(&value, s))
		return (false);
	if (value < 0 || value > 1)
		return (false);
	return (true);
}

bool	check_light(char *s)
{
	if (ft_word_count(s) != 4)
	{
		PRINT_ERR("Error: missing element in line L\n");
		return (false);
	}
	char	**matrix = ft_split(s, ' ');
	if (ft_strcmp(matrix[0], "L"))
	{
		PRINT_ERR("Error: missing L\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_coordinates(matrix[1]))
	{
		PRINT_ERR("Error: coordinates format wrong in L\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_bringhtness_limits(matrix[2]))
	{
		PRINT_ERR("Error: bringhtmess wrong in L\n");
		mtxfree_str(matrix);
		return (false);
	}
	if(!check_rgb_format(matrix[3]))
	{
		PRINT_ERR("Error: rgb format wrong in L\n");
		mtxfree_str(matrix);
		return (false);
	}
	mtxfree_str(matrix);
	return (true);
}

