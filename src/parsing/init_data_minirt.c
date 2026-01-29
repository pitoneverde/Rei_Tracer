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

	//print_debug_matrix(coordinates); // da togliere
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

	t_light *light = (t_light *)&(element->value);
	light->position = (t_point3)vec3_new(atof(coordinates[0]), atof(coordinates[1]), atof(coordinates[2]));
	light->brightness = atof(matrix[2]);
	light->color = rgb_new((uint8_t)ft_atoi(rgb[0]), (uint8_t)ft_atoi(rgb[1]), (uint8_t)ft_atoi(rgb[2]));
	mtxfree_str(matrix);
	mtxfree_str(coordinates);
	mtxfree_str(rgb);
}

t_element *init_data_minirt(char *s)
{
	char	**matrix = ft_split(s, '\n');
	int		i = 0;
	t_element *elements = malloc(sizeof(t_element) * mtx_count((void **)matrix));
	if (!elements)
		return (NULL);

	elements[0].id = "A";
	init_data_ambient(matrix[i++], &elements[0]);
	elements[1].id = "C";
	init_data_camera(matrix[i++], &elements[1]);
	elements[2].id = "L";
	init_data_light(matrix[i++], &elements[2]);
	mtxfree_str(matrix);
	return (elements);
}
