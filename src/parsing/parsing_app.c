/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gio <gio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:07:44 by gio               #+#    #+#             */
/*   Updated: 2026/03/30 15:08:15 by gio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

/*funzione utility per determinare se nella riga ci sono solo spazi vuoti*/

int	is_empty_lines(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		++i;
	}
	return (1);
}

/* conta il numero di righe non vuote*/
int	count_non_empty_lines(char **matrix)
{
	int	count;
	int	i;

	if (!matrix)
		return (0);
	count = 0;
	i = 0;
	while (matrix[i])
	{
		if (!is_empty_lines(matrix[i]))
			++count;
		++i;
	}
	return (count);
}

/*
 questo semplicemente
 toglie gli spazi doppi
 */

char	*compress_space(char *str)
{
	int	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (str[i[1]] != '\0')
	{
		if (str[i[1]] == ' ')
		{
			if (i[2] == 0)
			{
				str[i[0]++] = ' ';
				i[2] = 1;
			}
		}
		else
		{
			str[i[0]++] = str[i[1]];
			i[2] = 0;
		}
		++i[1];
	}
	str[i[0]] = '\0';
	return (str);
}

/* toglie le sgtringhe vuote dalla matrice
 */

bool	matrix_compress_app(char **matrix, char **new_matrix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (matrix[i])
	{
		if (!is_empty_lines(matrix[i]))
		{
			new_matrix[j] = ft_strdup(matrix[i]);
			if (!new_matrix[j])
			{
				mtxfree_str(new_matrix);
				return (true);
			}
			++j;
		}
		++i;
	}
	new_matrix[j] = NULL;
	return (false);
}

char	**matrix_compress(char **matrix)
{
	char	**new_matrix;
	int		non_empty_lines;

	if (!matrix)
		return (NULL);
	non_empty_lines = count_non_empty_lines(matrix);
	new_matrix = malloc(sizeof(char *) * (non_empty_lines + 1));
	if (!new_matrix)
		return (NULL);
	if (matrix_compress_app(matrix, new_matrix))
		return (NULL);
	mtxfree_str(matrix);
	return (new_matrix);
}
