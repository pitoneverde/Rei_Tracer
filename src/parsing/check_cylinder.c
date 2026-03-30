/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:48:03 by gmu               #+#    #+#             */
/*   Updated: 2026/03/30 19:48:06 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

bool	check_cy_diameter(char *s)
{
	double	val;

	if (!convertable_double(&val, s))
		return (false);
	return (true);
}

bool	check_cy_height(char *s)
{
	double	val;

	if (!convertable_double(&val, s))
		return (false);
	return (true);
}

bool	check_cylinder_app(char **matrix)
{
	if (!check_normalizzation_limits(matrix[2]))
	{
		PRINT_ERR("Error: normalizzation wrong in pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_cy_diameter(matrix[3]))
	{
		PRINT_ERR("Error: cylinder diameter\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_cy_height(matrix[4]))
	{
		PRINT_ERR("Error: cylinder height\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_rgb_format(matrix[5]))
	{
		PRINT_ERR("Error: rgb format wrong in cy\n");
		mtxfree_str(matrix);
		return (false);
	}
	return (true);
}

bool	check_cylinder(char *str)
{
	char	**matrix;

	if (ft_word_count(str) != 6)
	{
		PRINT_ERR("Error: missing element in line cy\n");
		return (false);
	}
	matrix = ft_split(str, ' ');
	if (ft_strcmp(matrix[0], "cy"))
	{
		PRINT_ERR("Error: missing cy\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_coordinates(matrix[1]))
	{
		PRINT_ERR("Error: coordinates format wrong in cy\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_cylinder_app(matrix))
		return (false);
	mtxfree_str(matrix);
	return (true);
}
