#include "minirt.h"
#include "libft.h"

bool	check_matrix_data_is_good(char **matrix)
{
	if (!check_ambient(matrix[0]))
		return (false);
	printf("La riga A va bene\n");
	if (!check_camera(matrix[1]))
		return (false);
	printf("La riga C va bene\n");
	if (!check_light(matrix[2]))
		return (false);
	printf("La riga L va bene\n");
	//int	i = 0;
	//while (ft_strcmp(matrix[i], "sp"))
	//{
	//	if (!check_spere(matrix[i]))
	//		return (false);
	//	++i;
	//}
	//while (ft_strcmp(matrix[i], "pl"))
	//{
	//	if (!check_plane(matrix[i]))
	//		return (false);
	//	++i;
	//}
	//while (ft_strcmp(matrix[i], "cy"))
	//{
	//	if (!check_cylinder(matrix[i]))
	//		return (false);
	//	++i;
	//}
	//if (matrix[i])
	//	return (false);
	return (true);
}
