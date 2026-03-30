/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 22:25:54 by gmu               #+#    #+#             */
/*   Updated: 2026/03/30 22:25:56 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_data.h"

t_rgb	rgb_new(uint8_t red, uint8_t green, uint8_t blue)
{
	return ((t_rgb){.rgba = {red, green, blue, 0}});
}

t_rgb	rgb_from_hex(uint32_t hex)
{
	return ((t_rgb){.hex = hex});
}
