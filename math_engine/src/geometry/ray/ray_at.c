/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 18:59:08 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/14 00:35:14 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry/ray.h"

inline t_vec3 ray_at(t_ray ray, float t)
{
	return (vec3_add(ray.origin, vec3_scale(ray.direction, t)));
}