/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_math_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 23:00:52 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/31 23:11:46 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_renderer.h"
#include "strings.h"

t_math	*init_spheres(t_math *m, t_element *d, int *i)
{
	if (ft_strcmp(d->id, "sp") == 0 && *i < m->sp_count)
	{
		if (create_sphere(&m->spheres[*i], (t_sphere *)&d->value))
			return (destroy_math(m), NULL);
		(*i)++;
	}
	return (m);
}

t_math	*init_planes(t_math *m, t_element *d, int *i)
{
	if (ft_strcmp(d->id, "pl") == 0 && *i < m->pl_count)
	{
		if (create_plane(&m->planes[*i], (t_plane *)&d->value))
			return (destroy_math(m), NULL);
		(*i)++;
	}
	return (m);
}

t_math	*init_cylinders(t_math *m, t_element *d, int *i)
{
	if (ft_strcmp(d->id, "cy") == 0 && *i < m->cy_count)
	{
		if (create_cylinder(&m->cys[*i], (t_cylinder *)&d->value))
			return (destroy_math(m), NULL);
		(*i)++;
	}
	return (m);
}
