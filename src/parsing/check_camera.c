#include "minirt.h"
#include "libft.h"
#include <stdbool.h>

#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool	check_camera_vectors_limits_app(char *s)
{
	char	**matrix = ft_split(s, ',');
	double	coordinates[3];
	
	bool good = true;
	int i = 0;
	while (i < 2)
	{
		if (!convertable_double(&coordinates[i], matrix[i]))
		{
			good = false;
		}
		++i;
	}
	i = 0;
	while (i < 2)
	{
		if (coordinates[i] < -1 || coordinates[i] > 1)
		{
			good = false;
		}
		++i;
	}
	mtxfree_str(matrix);
	return (good);
}

bool	check_camera_vectors_limits(char *s)
{
	int	i;
	int	n_comma;

	i = 0;
	n_comma = 0;
	while(s[i])
		if (s[i++] == ',')
			++n_comma;
	if (n_comma != 2)
		return (false);
	return (check_camera_vectors_limits_app(s));
}

bool	check_camera_fov_limits(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
		{
			return (false);
		}
		++i;
	}
	i = ft_atoi(s);
	if (i < 0 || i > 180)
		return (false);
	return (true);
}

bool	check_camera(char *str)
{
	if (ft_word_count(str) != 4)
	{
		PRINT_ERR("Error: missing element in line C\n");
		return (false);
	}
	char	**matrix = ft_split(str, ' ');
	if (ft_strcmp(matrix[0], "C"))
	{
		PRINT_ERR("Error: missing C\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_coordinates(matrix[1]))
	{
		PRINT_ERR("Error: coordinates format wrong\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_camera_vectors_limits(matrix[2]))
	{
		PRINT_ERR("Error: vector normalizzation wrong\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_camera_fov_limits(matrix[3]))
	{
		PRINT_ERR("Error: fov wrong\n");
		mtxfree_str(matrix);
		return (false);
	}
	mtxfree_str(matrix);
	return (true);
}
