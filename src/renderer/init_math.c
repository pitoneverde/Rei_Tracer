/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:53:42 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/17 19:13:17 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"
#include "strings.h"

static void	count_objects(int *idx, int len, t_element *d)
{
	int	i;

	i = 0;
	while (i < len)
		idx[i++] = 0;
	printf("cylinders: %d, spheres: %d, planes: %d\n", idx[0], idx[1], idx[2]);
	while(d->id)
	{
		if (ft_strcmp(d->id, "cy") == 0)
			idx[0]++;
		if (ft_strcmp(d->id, "sp") == 0)
			idx[1]++;
		if (ft_strcmp(d->id, "pl") == 0)
			idx[2]++;
		d++;		
	}
	(void)d;
	(void)i;
	(void)len;
}

static t_math	*malloc_math(t_element *data_file)
{
	t_math	*math;
	int	idx[3];

	math = calloc(1, sizeof(t_math));
	if (!math)
		return (NULL);
	count_objects(idx, 3, data_file);
	printf("cylinders: %d, spheres: %d, planes: %d\n", idx[0], idx[1], idx[2]);
	// math->spheres = malloc(sp * sizeof(t_sphere_math));
	// if (!math->spheres)
	// 	return (destroy_math(math), NULL);
	// math->cylinders = malloc(cy * sizeof(t_cylinder_math));
	// if (!math->cylinders)
	// 	return (destroy_math(math), NULL);
	// math->planes = malloc(pl * sizeof(t_plane_math));
	// if (!math->cylinders)
	// 	return (destroy_math(math), NULL);
	return (math);
}

// Assumes that data_file doesn't contain elements with a NULL id
// Follows manual RAII for each entity
t_math	*init_math(t_element *d)
{
	t_math	*m;
	if (!d)
		return (NULL);
	m = malloc_math(d);
	if (!m)
		return (NULL);
	else printf("MATH CREATED\n");
	while(d->id)
	{
		print_t_element(d);
		if (ft_strcmp(d->id, "C") == 0)
		{
			if (create_camera(&m->camera, (t_camera *)&d->value))
			// {
			// 	vec3_print("viewpoint", ((t_camera *)&d->value)->viewpoint);
			// 	vec3_print("orientation", ((t_camera *)&d->value)->orientation);
			// 	// mat4_print("cam to world", m->camera->cam_to_world);
				return (destroy_math(m), NULL);
			// }
			else
				printf("CAM CREATED\n");
		}
		// if (ft_strcmp(d->id, "A") == 0)
		// 	if (create_ambient(&m->ambient, (t_ambient_lighting *)&d->value))
		// 		return (destroy_math(m), NULL);
		// if (ft_strcmp(d->id, "L") == 0)
		// 	if (create_light(&m->ambient, (t_ambient_lighting *)&d->value))
		// 		return (destroy_math(m), NULL);
		d++;
	}
	return (m);
}
