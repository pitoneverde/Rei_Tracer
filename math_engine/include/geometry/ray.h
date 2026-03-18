/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:21:05 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 18:21:22 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "core/vec3.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	float	t_max; // should be far clip
	float	t_min; // should be near clip
}	t_ray;

t_vec3	ray_at(t_ray ray, float t);

#endif