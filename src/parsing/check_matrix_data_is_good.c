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
	int	i = 3;
	bool	shape = false;
	while (matrix[i])
	{
		if (!check_sphere(matrix[i]))
			return (false);
		else
		{
			printf("[%s][%d] la riga sp va bene\n", matrix[i], i);
			shape = true;
		}
		++i;
	}
	//while (matrix[i])
	//{
	//	if (!check_plane(matrix[i]))
	//		return (false);
	//	else
	//	{
	//		printf("[%s][%d] la riga pl va bene\n", matrix[i], i);
	//		shape = true;
	//	}
	//	++i;
	//}
	//while (matrix[i])
	//{
	//	if (!check_cylinder(matrix[i]))
	//		return (false);
	//	else
	//	{
	//		printf("[%s][%d] la riga cy va bene\n", matrix[i], i);
	//		shape = true;
	//	}
	//	++i;
	//}
	return (shape);
}
