#include "minirt.h"
#include "libft.h"

bool	check_matrix_data_is_good(char **matrix)
{
	print_debug_matrix(matrix);
	if (!check_ambient(matrix[0]))
		return (false);
	printf("La riga A va bene\n");
	if (!check_camera(matrix[1]))
		return (false);
	printf("La riga C va bene\n");
	if (!check_light(matrix[2]))
		return (false);
	printf("La riga L va bene\n");
	int	i = 3;
	while (matrix[i] != NULL)
	{
		if (ft_strncmp(matrix[i], "sp ", 3) == 0)
		{
			if (!check_sphere(matrix[i]))
				return (false);
		}
		else if (ft_strncmp(matrix[i], "pl ", 3) == 0)
		{
			if (!check_plane(matrix[i]))
				return (false);
		}
		else if (ft_strncmp(matrix[i], "cy ", 3) == 0)
		{
			if (!check_cylinder(matrix[i]))
				return (false);
		}
		else
			return (false);
		i++;
	}
	return (true);
}
