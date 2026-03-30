/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_matrix_data_is_good.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gio <gio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:07:25 by gio               #+#    #+#             */
/*   Updated: 2026/03/30 15:08:05 by gio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

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
	if (!check_matrix_data_is_good_app(matrix))
		return (false);
	return (true);
}
