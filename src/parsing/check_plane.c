/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gio <gio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:07:28 by gio               #+#    #+#             */
/*   Updated: 2026/03/31 23:38:35 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

bool	check_plane_app(char **matrix)
{
	if (!check_coordinates(matrix[1]))
	{
		printf("Error: coordinates format wrong in pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_normalizzation_limits(matrix[2]))
	{
		printf("Error: normalizzation wrong in pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_rgb_format(matrix[3]))
	{
		printf("Error: rgb format wrong in pl\n");
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
		printf("Error: missing element in line pl\n");
		return (false);
	}
	matrix = ft_split(str, ' ');
	if (ft_strcmp(matrix[0], "pl"))
	{
		printf("Error: missing pl\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_plane_app(matrix))
		return (false);
	mtxfree_str(matrix);
	return (true);
}
