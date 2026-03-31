/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 22:59:34 by gmu               #+#    #+#             */
/*   Updated: 2026/03/31 22:59:55 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

static double	ft_pow10(int exp)
{
	double	result;

	result = 1.0;
	if (exp >= 0)
		while (exp--)
			result *= 10.0;
	else
		while (exp++)
			result /= 10.0;
	return (result);
}

static double	parse_integer(const char **s)
{
	double	num;

	num = 0.0;
	while (ft_isdigit(**s))
	{
		num = num * 10.0 + (**s - '0');
		(*s)++;
	}
	return (num);
}

static double	parse_fraction(const char **s)
{
	double	frac;
	double	div;

	frac = 0.0;
	div = 1.0;
	while (ft_isdigit(**s))
	{
		div *= 10.0;
		frac = frac * 10.0 + (**s - '0');
		(*s)++;
	}
	return (frac / div);
}

static int	parse_exponent(const char **s)
{
	int	sign;
	int	exp;

	exp = 0;
	if (**s == 'e' || **s == 'E')
	{
		(*s)++;
		sign = 1;
		if (**s == '+')
			(*s)++;
		else if (**s == '-')
		{
			sign = -1;
			(*s)++;
		}
		while (ft_isdigit(**s))
		{
			exp = exp * 10 + (**s - '0');
			(*s)++;
		}
		exp *= sign;
	}
	return (exp);
}

double	ft_strtod(const char *str, char **endptr)
{
	double	num;
	int		sign;
	int		exp;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	num = parse_integer(&str);
	if (*str == '.')
	{
		str++;
		num += parse_fraction(&str);
	}
	exp = parse_exponent(&str);
	num *= ft_pow10(exp);
	if (endptr)
		*endptr = (char *)str;
	return (sign * num);
}
