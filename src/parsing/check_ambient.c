/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gio <gio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:07:06 by gio               #+#    #+#             */
/*   Updated: 2026/03/30 15:07:54 by gio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

int	parse_ambient_double_limits(char *str)
{
	double	value;

	value = convert_double_strtod(str);
	if (value < 0.0 || value > 1.0)
		return (0);
	return (1);
}

/*Controlla la lettera a e poi controlla il formato float
 * ['A'] [float]
 */
// check_matrix_data_is_good:
// if (check_ambient(...)) --> != 0 errore
// check(err); copia il codice errore nella funzione chaiamante
// return (err2); err2 piu' generico di err

// parse_input: required
// if (check_matrix_data....) ->> errore = err2
// check(err);
// return(err-parse)(";

// main:
// if (parse_input(...))
// check(err-parse);
// exit(err-main);

bool	check_ambient_app(char *str)
{
	char	**check_matrix;

	check_matrix = ft_split(str, ' ');
	if (ft_strcmp(check_matrix[0], "A"))
	{
		PRINT_ERR("Error: missing A\n");
		mtxfree_str(check_matrix);
		return (false);
	}
	if (!parse_ambient_double_limits(check_matrix[1]))
	{
		PRINT_ERR("Error: missing a float in line A\n");
		mtxfree_str(check_matrix);
		return (false);
	}
	if (!check_rgb_format(check_matrix[2]))
	{
		PRINT_ERR("Error: rgb format wrong\n");
		mtxfree_str(check_matrix);
		return (false);
	}
	mtxfree_str(check_matrix);
	return (true);
}

bool	check_ambient(char *str)
{
	if (ft_word_count(str) != 3)
	{
		PRINT_ERR("Error: missing element in line A\n");
		return (false);
	}
	if (!check_ambient_app(str))
		return (false);
	return (true);
}

bool	check_ambient(char *str)
{
	if (ft_word_count(str) != 3)
	{
		PRINT_ERR("Error: missing element in line A\n");
		return (0);
	}
	return (check_ambient_app(str));
}

/*controlla le varie righe siano
formattate in modo corretto */
