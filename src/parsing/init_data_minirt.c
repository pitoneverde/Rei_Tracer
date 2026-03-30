/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_minirt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gio <gio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:07:41 by gio               #+#    #+#             */
/*   Updated: 2026/03/30 15:08:12 by gio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

void	init_data_cylinder(char *s, t_element *element)
{
	char		**matrix;
	char		**center;
	char		**axis;
	char		**rgb;
	t_cylinder	*cylinder;

	matrix = ft_split(s, ' ');
	center = ft_split(matrix[1], ',');
	axis = ft_split(matrix[2], ',');
	rgb = ft_split(matrix[5], ',');
	element->id = "cy";
	cylinder = (t_cylinder *)&(element->value);
	cylinder->center = (t_point3)vec3_new(atof(center[0]), atof(center[1]),
			atof(center[2]));
	cylinder->axis = (t_vector3)vec3_new(atof(axis[0]), atof(axis[1]),
			atof(axis[2]));
	cylinder->diameter = atof(matrix[3]);
	cylinder->height = atof(matrix[4]);
	cylinder->color = rgb_new((uint8_t)ft_atoi(rgb[0]),
			(uint8_t)ft_atoi(rgb[1]), (uint8_t)ft_atoi(rgb[2]));
	mtxfree_str(matrix);
	mtxfree_str(center);
	mtxfree_str(axis);
	mtxfree_str(rgb);
}

void	init_acl(char **matrix, t_element *elements)
{
	init_data_ambient(matrix[0], &elements[0]);
	init_data_camera(matrix[1], &elements[1]);
	init_data_light(matrix[2], &elements[2]);
}

t_element	*init_data_minirt(char *s)
{
	char		**matrix;
	int			i;
	t_element	*elements;

	matrix = ft_split(s, '\n');
	elements = malloc(sizeof(t_element) * (mtx_count((void **)matrix) + 1));
	if (!elements)
		return (NULL);
	i = 3;
	while (matrix[i] != NULL)
	{
		if (ft_strncmp(matrix[i], "sp ", 3) == 0)
			init_data_sphere(matrix[i], &elements[i]);
		else if (ft_strncmp(matrix[i], "pl ", 3) == 0)
			init_data_plane(matrix[i], &elements[i]);
		else if (ft_strncmp(matrix[i], "cy ", 3) == 0)
			init_data_cylinder(matrix[i], &elements[i]);
		else
			return (NULL);
		i++;
	}
	elements[i].id = NULL;
	mtxfree_str(matrix);
	return (elements);
}
