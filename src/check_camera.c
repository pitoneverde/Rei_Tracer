#include "minirt.h"
#include "libft.h"
#include <stdbool.h>

#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool convertable_double(double *value, const char *str)
{
	if (!str || *str == '\0')
		return false;
	char *endptr;
	errno = 0;
	double result = strtod(str, &endptr);

	if (errno == ERANGE)
		return false;
	if (endptr == str)
		return false;
	while (ft_isspace((unsigned char)*endptr))
		endptr++;
	if (*endptr != '\0')
		return false;
	if (value != NULL)
		*value = result;
	return true;
}

bool	check_coordinates(char *s)
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
	char	**matrix = ft_split(s, ',');
	double	coordinates[3];
	
	bool good = true;
	i = 0;
	while (i < 2)
	{
		if (!convertable_double(&coordinates[i], matrix[i]))
			good = false;
		++i;
	}
	mtxfree_str(matrix);
	return (good);
}

bool	check_camera(char *str)
{
	if (ft_word_count(str) != 4)
	{
		PRINT_ERR("Error: missing element in line C\n");
		return false;
	}
	char	**check_matrix = ft_split(str, ' ');
	if (ft_strcmp(check_matrix[0], "C"))
	{
		PRINT_ERR("Error: missing C\n");
		mtxfree_str(check_matrix);
		return (false);
	}
	if (!check_coordinates(check_matrix[1]))
	{
		PRINT_ERR("Error: coordinates format wrong\n");
		mtxfree_str(check_matrix);
		return (false);
	}
	mtxfree_str(check_matrix);
	return (true);
}
