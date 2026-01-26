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
	bool	shape = false;
	if (!check_sphere(matrix[i]))
		return (false);
	else
	{
		printf("La riga sp va bene[%s][%d]\n", matrix[i], i);
		shape = true;
	}
	++i;
	if (!check_plane(matrix[i]))
		return (false);
	else
	{
		printf("La riga pl va bene[%s][%d]\n", matrix[i], i);
		shape = true;
	}
	++i;
	if (!check_cylinder(matrix[i]))
		return (false);
	else
	{
		printf("La riga cy va bene[%s][%d]\n", matrix[i], i);
		shape = true;
	}
	++i;
	return (shape);
}
