/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:11:44 by gmu               #+#    #+#             */
/*   Updated: 2025/02/17 22:11:47 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_prec(const char *str, int precision)
{
	int	cum_len;

	cum_len = 0;
	while (str[cum_len] && cum_len < precision)
		write(1, &str[cum_len++], 1);
	return (cum_len);
}

static int	ft_print_str_with_flags(const char *str, t_format flags)
{
	int	cum_len;

	cum_len = 0;
	if (flags.precision >= 0)
	{
		cum_len += ft_apply_padding(flags.precision, ft_strlen(str), 0);
		cum_len += ft_print_prec(str, flags.precision);
	}
	else
		cum_len += ft_print_prec(str, ft_strlen(str));
	return (cum_len);
}

static int	ft_print_string(const char *str, t_format flags)
{
	int	cum_len;

	cum_len = 0;
	if (str == NULL && flags.precision >= 0 && flags.precision < 6)
	{
		cum_len += ft_apply_padding(flags.width, 0, 0);
		return (cum_len);
	}
	if (str == NULL)
		str = "(null)";
	if (flags.precision >= 0 && (size_t)flags.precision > ft_strlen(str))
		flags.precision = ft_strlen(str);
	if (flags.left == 1)
		cum_len += ft_print_str_with_flags(str, flags);
	if (flags.precision >= 0)
		cum_len += ft_apply_padding(flags.width, flags.precision, 0);
	else
		cum_len += ft_apply_padding(flags.width, ft_strlen(str), 0);
	if (flags.left == 0)
		cum_len += ft_print_str_with_flags(str, flags);
	return (cum_len);
}

static int	ft_print_char(char c, t_format flags)
{
	int	count;

	count = 0;
	if (flags.left == 1)
		count += ft_putchar(c);
	count += ft_apply_padding(flags.width, 1, flags.zero);
	if (flags.left == 0)
		count += ft_putchar(c);
	return (count);
}

int	ft_init_format(char format, va_list args, t_format flags)
{
	int	cum_len;

	cum_len = 0;
	if (format == 'c')
		cum_len += ft_print_char(va_arg(args, int), flags);
	else if (format == 's')
		cum_len += ft_print_string(va_arg(args, const char *), flags);
	else if (format == 'p')
		cum_len
			+= ft_print_pointer((unsigned long int)va_arg(args, void *), flags);
	else if (format == 'd' || format == 'i')
		cum_len
			+= ft_print_decimal_integer(va_arg(args, int), flags);
	else if (format == 'u')
		cum_len
			+= ft_print_unsigned_decimal(va_arg(args, unsigned int), flags);
	else if (format == 'X')
		cum_len
			+= ft_print_hexadecimal(va_arg(args, unsigned int), 1, flags);
	else if (format == 'x' )
		cum_len
			+= ft_print_hexadecimal(va_arg(args, unsigned int), 0, flags);
	else if (format == '%')
		cum_len += ft_print_char('%', flags);
	return (cum_len);
}
