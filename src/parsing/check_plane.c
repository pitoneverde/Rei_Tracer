/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gio <gio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:07:28 by gio               #+#    #+#             */
/*   Updated: 2026/03/30 15:08:08 by gio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

bool	check_plane_app(char **matrix)
{
	if (!check_coordinates(matrix[1]))
	{
		PRINT_ERR("Error: coordinates format wrong in pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_normalizzation_limits(matrix[2]))
	{
		PRINT_ERR("Error: normalizzation wrong in pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_rgb_format(matrix[3]))
	{
		PRINT_ERR("Error: rgb format wrong in pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	return (true);
}

bool	check_plane(char *str)
{
	char	**matrix;

	if (ft_word_count(str) != 4)
	{
		PRINT_ERR("Error: missing element in line pl\n");
		return (false);
	}
	matrix = ft_split(str, ' ');
	if (ft_strcmp(matrix[0], "pl"))
	{
		PRINT_ERR("Error: missing pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_plane_app(matrix))
		return (false);
	mtxfree_str(matrix);
	return (true);
}
