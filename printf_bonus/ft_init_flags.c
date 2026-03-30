/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:07:25 by gmu               #+#    #+#             */
/*   Updated: 2025/02/17 22:07:27 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_format	ft_flag_digit(char c, t_format flags)
{
	if (flags.star == 1)
		flags.width = 0;
	flags.width = (flags.width * 10) + (c - '0');
	return (flags);
}

static t_format	ft_flag_width(va_list args, t_format flags)
{
	flags.star = 1;
	flags.width = va_arg(args, int);
	if (flags.width < 0)
	{
		flags.left = 1;
		flags.width *= -1;
	}
	return (flags);
}

static int	ft_flag_precision(const char *str, int pos, va_list args,
			t_format *flags)
{
	int	i;

	i = pos + 1;
	if (str[i] == '*')
	{
		flags->precision = va_arg(args, int);
		return (i++);
	}
	flags->precision = 0;
	while (ft_isdigit(str[i]))
	{
		flags->precision = (flags->precision * 10) + (str[i] - '0');
		i++;
	}
	return (i);
}

static t_format	ft_flag_left(t_format flags)
{
	flags.left = 1;
	flags.zero = 0;
	return (flags);
}

int	ft_init_flags(const char *str, int i, va_list args, t_format *flags)
{
	while (str[++i] && ft_isflag(str[i]))
	{
		if (str[i] == '-')
			*flags = ft_flag_left(*flags);
		if (str[i] == '#')
			flags->hash = 1;
		if (str[i] == ' ')
			flags->space = 1;
		if (str[i] == '+')
			flags->plus = 1;
		if (str[i] == '0' && flags->left == 0 && flags->width == 0)
			flags->zero = 1;
		if (str[i] == '.')
			i = ft_flag_precision(str, i, args, flags);
		if (str[i] == '*')
			*flags = ft_flag_width(args, *flags);
		if (ft_isdigit(str[i]))
			*flags = ft_flag_digit(str[i], *flags);
		if (ft_isspec(str[i]))
		{
			flags->spec = str[i];
			break ;
		}
	}
	return (i);
}
