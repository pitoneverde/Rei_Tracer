/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:53:42 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 16:45:48 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"
#include "strings.h"
#include "memory.h"

static void		count_objects(int *idx, int len, t_element *d);
static t_math	*malloc_math(t_element *data_file);

// TODO: if-elif cascade should be extracted each to its own function
// for id == "A" and id == "L", keep utils in this file, the others go to utils.c
// Assumes that data_file doesn't contain elements with a NULL id
// Follows manual RAII for each entity
t_math	*init_math(t_element *d)
{
	t_math	*m;
	int		i = 0;
	int		j = 0;
	int		k = 0;
	if (!d)
		return (NULL);
	m = malloc_math(d);
	if (!m)
		return (NULL);
	while(d->id)
	{
		if (ft_strcmp(d->id, "A") == 0)
		{
			if (create_ambient(&m->ambient, (t_ambient *)&d->value))
				return (destroy_math(m), NULL);
		}
		if (ft_strcmp(d->id, "C") == 0)
		{
			if (create_camera(&m->camera, (t_camera *)&d->value))
				return (destroy_math(m), NULL);
		}
		if (ft_strcmp(d->id, "L") == 0)
		{
			if (create_light(&m->light, (t_light *)&d->value))
				return (destroy_math(m), NULL);
		}
		else if (ft_strcmp(d->id, "sp") == 0 && i < m->sp_count)
		{
			if (create_sphere(&m->spheres[i], (t_sphere *)&d->value))
				return (destroy_math(m), NULL);
			i++;
		}
		else if (ft_strcmp(d->id, "pl") == 0 && j < m->pl_count)
		{
			if (create_plane(&m->planes[j], (t_plane *)&d->value))
				return (destroy_math(m), NULL);
			j++;
		}
		else if (ft_strcmp(d->id, "cy") == 0 && k < m->cy_count)
		{
			if (create_cylinder(&m->cys[k], (t_cylinder *)&d->value))
				return (destroy_math(m), NULL);
			j++;
		}
		d++;
	}
	return (m);
}

static void	count_objects(int *idx, int len, t_element *d)
{
	int	i;

	i = 0;
	while (i < len)
		idx[i++] = 0;
	while (d->id)
	{
		if (ft_strcmp(d->id, "cy") == 0)
			idx[0]++;
		if (ft_strcmp(d->id, "sp") == 0)
			idx[1]++;
		if (ft_strcmp(d->id, "pl") == 0)
			idx[2]++;
		d++;
	}
}

static t_math	*malloc_math(t_element *data_file)
{
	t_math	*math;
	int		idx[3];

	if (!data_file)
		return (NULL);
	math = ft_calloc(1, sizeof(t_math));
	if (!math)
		return (NULL);
	count_objects(idx, 3, data_file);
	math->cy_count = idx[0];
	math->sp_count = idx[1];
	math->pl_count = idx[2];
	math->cys = malloc(idx[0] * sizeof(t_cylinder_math));
	if (!math->cys)
		return (destroy_math(math), NULL);
	math->spheres = malloc(idx[1] * sizeof(t_sphere_math));
	if (!math->spheres)
		return (destroy_math(math), NULL);
	math->planes = malloc(idx[2] * sizeof(t_plane_math));
	if (!math->planes)
		return (destroy_math(math), NULL);
	return (math);
}
