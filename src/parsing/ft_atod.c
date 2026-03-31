/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 22:20:37 by gmu               #+#    #+#             */
/*   Updated: 2026/03/31 22:20:40 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

double	ft_atof(const char *str)
{
	const int	decimal = ft_atoi (str);
	double		fractional;
	double		mul;
	char		*cp;

	fractional = 0.00;
	mul = 0.10;
	cp = ft_strchr (str, '.');
	if (!cp)
		return ((double)(1.0 * decimal));
	while (ft_isdigit (*(++cp)) )
	{
		fractional += (double)(*cp - '0') * mul;
		mul *= 0.10;
	}
	return ((double)(decimal * (1.0 + fractional)));
}
