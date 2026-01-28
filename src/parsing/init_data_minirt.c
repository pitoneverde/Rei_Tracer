#include "minirt.h"
#include "libft.h"

void	init_data_ambient(char *s, t_element *element)
{
	char	**matrix = ft_split(s, ' ');

	element->value.a.brightness = atof(matrix[1]);
	char	**rgb = ft_split(matrix[2], ',');
	element->value.a.color.rgba.red = (uint8_t)atoi(rgb[0]);
	element->value.a.color.rgba.green = (uint8_t)atoi(rgb[1]);
	element->value.a.color.rgba.blue = (uint8_t)atoi(rgb[2]);
	mtxfree_str(matrix);
	mtxfree_str(rgb);
}

void	init_data_camera(char *s, t_element *element)
{
	char	**matrix = ft_split(s, ' ');
	char	**coordinates = ft_split(matrix[1], ',');
	char	**rgb = ft_split(matrix[2], ',');

	t_camera *cam = (t_camera *)&(element->value);
	//riempi camera cam->fov....

	cam->viewpoint = (t_point3)vec3_new(atof(coordinates[0]), atof(coordinates[1]), atof(coordinates[2]));
	cam->orientation = (t_vector3)vec3_new(atof(rgb[0]), atof(rgb[1]), atof(rgb[2]));
	cam->fov = (uint8_t)atoi(matrix[3]);
	mtxfree_str(matrix);
	mtxfree_str(coordinates);
	mtxfree_str(rgb);
}

void	init_data_light(char *s, t_element *element)
{
	char	**matrix = ft_split(s, ' ');
	char	**coordinates = ft_split(matrix[1], ',');
	char	**rgb = ft_split(matrix[3], ',');

	element->value.l.position.x = atof(coordinates[0]);
	element->value.l.position.y = atof(coordinates[1]);
	element->value.l.position.z = atof(coordinates[2]);

	element->value.l.brightness = atof(matrix[2]);

	element->value.l.color.rgba.red = (uint8_t)atoi(rgb[0]);
	element->value.l.color.rgba.green = (uint8_t)atoi(rgb[1]);
	element->value.l.color.rgba.blue = (uint8_t)atoi(rgb[2]);

	mtxfree_str(matrix);
	mtxfree_str(coordinates);
	mtxfree_str(rgb);
}

void	init_data_minirt(char *s, t_element *elements)
{
	char	**matrix = ft_split(s, '\n');
	int		i = 0;

	elements[0].id = "A";
	init_data_ambient(matrix[i], &elements[0]);
	elements[1].id = "C";
	init_data_camera(matrix[i], &elements[1]);
	elements[2].id = "L";
	init_data_light(matrix[i], &elements[2]);
	mtxfree_str(matrix);
}
