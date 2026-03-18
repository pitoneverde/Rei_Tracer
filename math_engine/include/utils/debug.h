/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:23:17 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/18 18:23:17 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "core/vec3.h"
# include "core/mat4.h"

// debug utilities (prints, metrics)

void	vec3_print(const char *name, t_vec3 v);
void	mat4_print(const char *name, t_mat4 m);

#endif