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

void	init_data_ambient(char *s, t_element *element)
{
	char		**matrix;
	char		**rgb;
	t_ambient	*ambient;

	matrix = ft_split(s, ' ');
	rgb = ft_split(matrix[2], ',');
	element->id = "A";
	ambient = (t_ambient *)&(element->value);
	ambient->brightness = ft_atod(matrix[1]);
	ambient->color = rgb_new((uint8_t)ft_atoi(rgb[0]), (uint8_t)ft_atoi(rgb[1]),
			(uint8_t)ft_atoi(rgb[2]));
	mtxfree_str(matrix);
	mtxfree_str(rgb);
}

void	init_data_camera(char *s, t_element *element)
{
	char		**matrix;
	char		**coordinates;
	char		**rgb;
	t_camera	*cam;

	matrix = ft_split(s, ' ');
	coordinates = ft_split(matrix[1], ',');
	rgb = ft_split(matrix[2], ',');
	element->id = "C";
	cam = (t_camera *)&(element->value);
	cam->viewpoint = (t_point3)vec3_new(ft_atod(coordinates[0]),
			ft_atod(coordinates[1]), ft_atod(coordinates[2]));
	cam->orientation = (t_vector3)vec3_new(ft_atod(rgb[0]), ft_atod(rgb[1]),
			ft_atod(rgb[2]));
	cam->fov = ft_atod(matrix[3]);
	mtxfree_str(matrix);
	mtxfree_str(coordinates);
	mtxfree_str(rgb);
}

void	init_data_light(char *s, t_element *element)
{
	char	**matrix;
	char	**coordinates;
	char	**rgb;
	t_light	*light;

	matrix = ft_split(s, ' ');
	coordinates = ft_split(matrix[1], ',');
	rgb = ft_split(matrix[3], ',');
	element->id = "L";
	light = (t_light *)&(element->value);
	light->position = (t_point3)vec3_new(ft_atod(coordinates[0]),
			ft_atod(coordinates[1]), ft_atod(coordinates[2]));
	light->brightness = ft_atod(matrix[2]);
	light->color = rgb_new((uint8_t)ft_atoi(rgb[0]), (uint8_t)ft_atoi(rgb[1]),
			(uint8_t)ft_atoi(rgb[2]));
	mtxfree_str(matrix);
	mtxfree_str(coordinates);
	mtxfree_str(rgb);
}

void	init_data_sphere(char *s, t_element *element)
{
	char		**matrix;
	char		**coordinates;
	char		**rgb;
	t_sphere	*sphere;

	matrix = ft_split(s, ' ');
	coordinates = ft_split(matrix[1], ',');
	rgb = ft_split(matrix[3], ',');
	element->id = "sp";
	sphere = (t_sphere *)&(element->value);
	sphere->center = (t_point3)vec3_new(ft_atod(coordinates[0]),
			ft_atod(coordinates[1]), ft_atod(coordinates[2]));
	sphere->diameter = ft_atod(matrix[2]);
	sphere->color = rgb_new((uint8_t)ft_atoi(rgb[0]), (uint8_t)ft_atoi(rgb[1]),
			(uint8_t)ft_atoi(rgb[2]));
	mtxfree_str(matrix);
	mtxfree_str(coordinates);
	mtxfree_str(rgb);
}

void	init_data_plane(char *s, t_element *element)
{
	char	**matrix;
	char	**point;
	char	**normal;
	char	**rgb;
	t_plane	*plane;

	matrix = ft_split(s, ' ');
	point = ft_split(matrix[1], ',');
	normal = ft_split(matrix[2], ',');
	rgb = ft_split(matrix[3], ',');
	element->id = "pl";
	plane = (t_plane *)&(element->value);
	plane->point = (t_point3)vec3_new(ft_atod(point[0]), ft_atod(point[1]),
			ft_atod(point[2]));
	plane->normal = (t_point3)vec3_new(ft_atod(normal[0]), ft_atod(normal[1]),
			ft_atod(normal[2]));
	plane->color = rgb_new((uint8_t)ft_atoi(rgb[0]), (uint8_t)ft_atoi(rgb[1]),
			(uint8_t)ft_atoi(rgb[2]));
	mtxfree_str(matrix);
	mtxfree_str(point);
	mtxfree_str(normal);
	mtxfree_str(rgb);
}
