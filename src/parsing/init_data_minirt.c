#include "minirt.h"
#include "libft.h"

void	init_data_ambient(char *s, t_element *element)
{
	char	**matrix = ft_split(s, ' ');
	char	**rgb = ft_split(matrix[2], ',');

	element->id = "A";
	t_ambient_lighting *ambient = (t_ambient_lighting *)&(element->value);
	ambient->brightness = atof(matrix[1]);
	ambient->color = rgb_new((uint8_t)ft_atoi(rgb[0]), (uint8_t)ft_atoi(rgb[1]), (uint8_t)ft_atoi(rgb[2]));
	mtxfree_str(matrix);
	mtxfree_str(rgb);
}

void	init_data_camera(char *s, t_element *element)
{
	char	**matrix = ft_split(s, ' ');
	char	**coordinates = ft_split(matrix[1], ',');
	char	**rgb = ft_split(matrix[2], ',');

	element->id = "C";
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

	element->id = "L";
	t_light *light = (t_light *)&(element->value);
	light->position = (t_point3)vec3_new(atof(coordinates[0]), atof(coordinates[1]), atof(coordinates[2]));
	light->brightness = atof(matrix[2]);
	light->color = rgb_new((uint8_t)ft_atoi(rgb[0]), (uint8_t)ft_atoi(rgb[1]), (uint8_t)ft_atoi(rgb[2]));
	mtxfree_str(matrix);
	mtxfree_str(coordinates);
	mtxfree_str(rgb);
}

void	init_data_sphere(char *s, t_element *element)
{
	char	**matrix = ft_split(s, ' ');
	char	**coordinates = ft_split(matrix[1], ',');
	char	**rgb = ft_split(matrix[3], ',');

	element->id = "sp";
	t_sphere *sphere = (t_sphere *)&(element->value);
	sphere->center = (t_point3)vec3_new(atof(coordinates[0]), atof(coordinates[1]), atof(coordinates[2]));
	sphere->diameter = atof(matrix[2]);
	sphere->color = rgb_new((uint8_t)ft_atoi(rgb[0]), (uint8_t)ft_atoi(rgb[1]), (uint8_t)ft_atoi(rgb[2]));
	mtxfree_str(matrix);
	mtxfree_str(coordinates);
	mtxfree_str(rgb);
}
void	init_data_plane(char *s, t_element *element)
{
	char	**matrix = ft_split(s, ' ');
	char	**point = ft_split(matrix[1], ',');
	char	**normal = ft_split(matrix[2], ',');
	char	**rgb = ft_split(matrix[3], ',');

	element->id = "pl";
	t_plane *plane = (t_plane *)&(element->value);
	plane->point = (t_point3)vec3_new(atof(point[0]), atof(point[1]), atof(point[2]));
	plane->normal = (t_point3)vec3_new(atof(normal[0]), atof(normal[1]), atof(normal[2]));
	plane->color = rgb_new((uint8_t)ft_atoi(rgb[0]), (uint8_t)ft_atoi(rgb[1]), (uint8_t)ft_atoi(rgb[2]));
	mtxfree_str(matrix);
	mtxfree_str(point);
	mtxfree_str(normal);
	mtxfree_str(rgb);
}

void	init_data_cylinder(char *s, t_element *element)
{
	char	**matrix = ft_split(s, ' ');
	char	**center = ft_split(matrix[1], ',');
	char	**axis = ft_split(matrix[2], ',');
	char	**rgb = ft_split(matrix[5], ',');

	element->id = "cy";
	t_cylinder *cylinder = (t_cylinder *)&(element->value);
	cylinder->center = (t_point3)vec3_new(atof(center[0]), atof(center[1]), atof(center[2]));
	cylinder->axis = (t_vector3)vec3_new(atof(axis[0]), atof(axis[1]), atof(axis[2]));
	cylinder->diameter = atof(matrix[3]);
	cylinder->height = atof(matrix[4]);
	cylinder->color = rgb_new((uint8_t)ft_atoi(rgb[0]), (uint8_t)ft_atoi(rgb[1]), (uint8_t)ft_atoi(rgb[2]));
	mtxfree_str(matrix);
	mtxfree_str(center);
	mtxfree_str(axis);
	mtxfree_str(rgb);
}

t_element *init_data_minirt(char *s)
{
	char	**matrix = ft_split(s, '\n');
	int		i = 0;
	t_element *elements = malloc(sizeof(t_element) * mtx_count((void **)matrix));
	if (!elements)
		return (NULL);

	init_data_ambient(matrix[i++], &elements[0]);
	init_data_camera(matrix[i++], &elements[1]);
	init_data_light(matrix[i++], &elements[2]);
	//... e cosi via per gli altri elementi

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
	mtxfree_str(matrix);
	return (elements);
}
