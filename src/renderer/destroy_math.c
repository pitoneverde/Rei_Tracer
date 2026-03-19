/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:44:12 by sabruma           #+#    #+#             */
/*   Updated: 2026/03/19 23:12:05 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_engine.h"
#include <stdlib.h>

void	destroy_math(t_math *math_engine)
{
	free(math_engine->cylinders);
	free(math_engine->planes);
	free(math_engine->spheres);
	free(math_engine);
}