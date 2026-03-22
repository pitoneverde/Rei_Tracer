/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:01:29 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/23 00:01:29 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPES_H
# define MINIRT_TYPES_H

# include <stdint.h>
# include "core/vec3.h"

typedef struct s_color
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;	//unused just to pad
}	t_color;

typedef union u_rgb
{
	t_color		rgba;
	uint32_t	hex;
}	t_rgb;

typedef t_vec3	t_point3;
typedef t_vec3	t_vector3;

#endif