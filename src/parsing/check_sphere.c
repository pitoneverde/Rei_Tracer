/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gio <gio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:07:31 by gio               #+#    #+#             */
/*   Updated: 2026/03/31 23:37:33 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

bool	check_sphere_app(char **matrix)
{
	double	val;

	if (!convertable_double(&val, matrix[2]))
	{
		printf("Error: sphere diameter wrong in sp\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_rgb_format(matrix[3]))
	{
		printf("Error: rgb format wrong in sp\n");
		mtxfree_str(matrix);
		return (false);
	}
	mtxfree_str(matrix);
	return (true);
}

bool	check_sphere(char *str)
{
	char	**matrix;

	if (ft_word_count(str) != 4)
	{
		printf("Error: missing element in line sp\n");
		return (false);
	}
	matrix = ft_split(str, ' ');
	if (ft_strcmp(matrix[0], "sp"))
	{
		printf("Error: missing sp\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_coordinates(matrix[1]))
	{
		printf("Error: coordinates format wrong in sp\n");
		mtxfree_str(matrix);
		return (false);
	}
	return (check_sphere_app(matrix));
}
