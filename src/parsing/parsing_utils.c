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

bool	check_coordinates(char *s)
{
	char	**matrix;
	bool	is_good;
	int		i;
	double	val[3];

	if (!check_n_comma(s, 2))
		return (false);
	matrix = ft_split(s, ',');
	is_good = true;
	i = 0;
	if (matrix_size(matrix) != 3)
		is_good = false;
	while (i < matrix_size(matrix))
	{
		if (!convertable_double(&val[i], matrix[i]))
			is_good = false;
		++i;
	}
	mtxfree_str(matrix);
	return (is_good);
}

/*funzione utility che conta le parole in una stringa*/
int	ft_word_count(char *str)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_isspace(str[i]))
			in_word = 0;
		else if (!in_word)
		{
			++count;
			in_word = 1;
		}
		++i;
	}
	return (count);
}

bool	is_str_full_of_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		++i;
	}
	return (true);
}

/*controlla che la parte ['A'] ['float'] [rgb]
										questa sopra
							sia corretta*/

bool	check_rgb_format(char *str)
{
	char	**matrix;
	bool	is_valid;
	int		val;
	int		i;

	if (!check_n_comma(str, 2))
		return (false);
	matrix = ft_split(str, ',');
	i = 0;
	is_valid = true;
	while (i < 3)
	{
		if (!is_str_full_of_digits(matrix[i]))
			is_valid = false;
		val = ft_atoi(matrix[i]);
		if (val < 0 || val > 255)
			is_valid = false;
		++i;
	}
	mtxfree_str(matrix);
	return (is_valid);
}

bool	check_normalizzation_limits(char *str)
{
	char	**matrix;
	int		i;
	bool	good;
	double	val;

	if (!check_coordinates(str))
		return (false);
	matrix = ft_split(str, ',');
	good = true;
	i = 0;
	while (matrix[i])
	{
		val = convert_double_strtod(matrix[i]);
		if (val < -1 || val > 1)
			good = false;
		++i;
	}
	mtxfree_str(matrix);
	return (good);
}
