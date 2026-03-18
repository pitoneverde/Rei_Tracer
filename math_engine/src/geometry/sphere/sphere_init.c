/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 11:03:52 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 11:52:15 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/sphere.h"

int		sphere_init(t_sphere_math *sp, t_sphere_data data)
{
	if (!sp)
		return (1);
	sp->center = data.center;
	sp->color = data.color;
	sp->radius = data.radius;
	sp->radius_sq = data.radius * data.radius;
	return (0);
}