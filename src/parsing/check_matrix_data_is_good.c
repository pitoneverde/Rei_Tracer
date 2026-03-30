/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_matrix_data_is_good.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:37:13 by gmu               #+#    #+#             */
/*   Updated: 2026/03/30 19:39:24 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

bool	check_matrix_data_is_good_app(char **matrix)
{
	int	i;

	i = 3;
	while (matrix[i] != NULL)
	{
		if (ft_strncmp(matrix[i], "sp ", 3) == 0)
		{
			if (!check_sphere(matrix[i]))
				return (false);
		}
		else if (ft_strncmp(matrix[i], "pl ", 3) == 0)
		{
			if (!check_plane(matrix[i]))
				return (false);
		}
		else if (ft_strncmp(matrix[i], "cy ", 3) == 0)
		{
			if (!check_cylinder(matrix[i]))
				return (false);
		}
		else
			return (false);
		i++;
	}
	return (true);
}

bool	check_matrix_data_is_good(char **matrix)
{
	if (!check_ambient(matrix[0]))
		return (false);
	if (!check_camera(matrix[1]))
		return (false);
	if (!check_light(matrix[2]))
		return (false);
	return (check_matrix_data_is_good_app(matrix));
}
