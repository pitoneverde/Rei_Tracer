/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gio <gio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:07:35 by gio               #+#    #+#             */
/*   Updated: 2026/03/30 15:08:14 by gio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

void	print_debug_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("%d [%s]\n", i, matrix[i]);
		++i;
	}
}

int	matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		++i;
	return (i);
}

bool	check_n_comma(char *s, int n_comma)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ',')
			--n_comma;
		++i;
	}
	if (n_comma != 0)
		return (false);
	return (true);
}

double	convert_double_strtod(char *str)
{
	char	*endptr;
	double	result;

	result = ft_strtod(str, &endptr);
	if (str == endptr)
	{
		printf("Error: numer not converted\n");
		return (0.0);
	}
	if (*endptr != '\0' && !ft_isspace(*endptr))
	{
		printf("Error: extra carcter before numbers: '%s'\n", endptr);
	}
	return (result);
}

bool	convertable_double(double *value, const char *str)
{
	char	*endptr;
	double	result;

	if (!str || *str == '\0')
		return (false);
	errno = 0;
	result = ft_strtod(str, &endptr);
	if (errno == ERANGE)
		return (false);
	if (endptr == str)
		return (false);
	while (ft_isspace((unsigned char)*endptr))
		endptr++;
	if (*endptr != '\0')
		return (false);
	if (value != NULL)
		*value = result;
	return (true);
}
