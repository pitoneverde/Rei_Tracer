/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gio <gio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:07:22 by gio               #+#    #+#             */
/*   Updated: 2026/03/31 23:36:58 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

bool	check_bringhtness_limits(char *s)
{
	double	value;

	if (!convertable_double(&value, s))
		return (false);
	if (value < 0 || value > 1)
		return (false);
	return (true);
}

bool	check_light_app(char **matrix)
{
	if (!check_coordinates(matrix[1]))
	{
		printf("Error: coordinates format wrong in L\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_bringhtness_limits(matrix[2]))
	{
		printf("Error: bringhtmess wrong in L\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_rgb_format(matrix[3]))
	{
		printf("Error: rgb format wrong in L\n");
		mtxfree_str(matrix);
		return (false);
	}
	return (true);
}

bool	check_light(char *s)
{
	char	**matrix;

	if (ft_word_count(s) != 4)
	{
		printf("Error: missing element in line L\n");
		return (false);
	}
	matrix = ft_split(s, ' ');
	if (ft_strcmp(matrix[0], "L"))
	{
		printf("Error: missing L\n");
		mtxfree_str(matrix);
		return (false);
	}
	if (!check_light_app(matrix))
		return (false);
	mtxfree_str(matrix);
	return (true);
}
