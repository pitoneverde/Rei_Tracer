/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_minirt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gio <gio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:07:41 by gio               #+#    #+#             */
/*   Updated: 2026/03/31 23:49:06 by gmu              ###   ########.fr       */
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
	cylinder->center = (t_point3)vec3_new(ft_atod(center[0]),
			ft_atod(center[1]), ft_atod(center[2]));
	cylinder->axis = (t_vector3)vec3_new(ft_atod(axis[0]),
			ft_atod(axis[1]), ft_atod(axis[2]));
	cylinder->diameter = ft_atod(matrix[3]);
	cylinder->height = ft_atod(matrix[4]);
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

static bool	init_data_minirt_app(char **matrix, t_element *elements)
{
	int			i;

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
			return (false);
		i++;
	}
	elements[i].id = NULL;
	return (true);
}

t_element	*init_data_minirt(char *s)
{
	char		**matrix;
	t_element	*elements;

	printf("%s", s);
	matrix = ft_split(s, '\n');
	elements = malloc(sizeof(t_element) * (mtx_count((void **)matrix) + 1));
	if (!elements)
		return (NULL);
	init_acl(matrix, elements);
	if (!init_data_minirt_app(matrix, elements))
		return (NULL);
	mtxfree_str(matrix);
	return (elements);
}
