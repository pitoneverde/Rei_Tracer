/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 22:51:26 by gmu               #+#    #+#             */
/*   Updated: 2026/03/31 22:55:26 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

double	ft_atod(const char *str)
{
	double	s[3];
	int		sign;

	s[0] = 0.0;
	s[1] = 0.0;
	s[2] = 1.0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str))
		s[0] = s[0] * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			s[1] = s[1] * 10.0 + (*str++ - '0');
			s[2] *= 10.0;
		}
		s[0] += s[1] / s[2];
	}
	return (sign * s[0]);
}
