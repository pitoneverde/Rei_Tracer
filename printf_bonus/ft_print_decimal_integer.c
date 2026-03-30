/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal_integer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:11:57 by gmu               #+#    #+#             */
/*   Updated: 2025/02/17 22:11:59 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_fap_nbr(char *nbr, int n, t_format flags)
{
	int	cum_len;

	cum_len = 0;
	if (n < 0)
	{
		if (flags.zero == 0 || flags.precision >= 0)
			cum_len += ft_putchar('-');
	}
	else if (flags.plus == 1 && flags.zero == 0)
		cum_len += ft_putchar('+');
	else if (flags.space == 1 && flags.zero == 0)
		cum_len += ft_putchar(' ');
	if (flags.precision >= 0)
		cum_len += ft_apply_padding(flags.precision - 1,
				ft_strlen(nbr) - 1, 1);
	cum_len += ft_print_str(nbr);
	return (cum_len);
}

static int	ft_print_sign(int n, t_format *flags)
{
	int	cum_len;

	cum_len = 0;
	if (n < 0 && flags->precision == -1)
	{
		cum_len += ft_putchar('-');
		flags->width--;
	}
	else if (flags->plus == 1)
		cum_len += ft_putchar('+');
	else if (flags->space == 1)
	{
		cum_len += ft_putchar(' ');
		flags->width--;
	}
	return (cum_len);
}

static int	ft_format_and_print(char *nmbstr, int n, t_format flags)
{
	int	cum_len;

	cum_len = 0;
	if (flags.zero == 1)
		cum_len += ft_print_sign(n, &flags);
	if (flags.left == 1)
		cum_len += ft_fap_nbr(nmbstr, n, flags);
	if (flags.precision >= 0 && (size_t)flags.precision < ft_strlen(nmbstr))
		flags.precision = ft_strlen(nmbstr);
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		if (n < 0 && flags.left == 0)
			flags.width -= 1;
		cum_len += ft_apply_padding(flags.width, 0, 0);
	}
	else
		cum_len += ft_apply_padding(flags.width - flags.plus - flags.space,
				ft_strlen(nmbstr), flags.zero);
	if (flags.left == 0)
		cum_len += ft_fap_nbr(nmbstr, n, flags);
	return (cum_len);
}

int	ft_print_decimal_integer(int n, t_format flags)
{
	char	*nmbstr;
	long	nb;
	int		cum_len;

	nb = n;
	cum_len = 0;
	if (nb < 0)
	{
		nb *= -1;
		if (flags.zero == 0)
			flags.width--;
	}
	if (flags.precision == 0 && n == 0)
	{
		cum_len += ft_apply_padding(flags.width, 0, 0);
		return (cum_len);
	}
	nmbstr = ft_itoa_base(nb, 10);
	if (!nmbstr)
		return (0);
	cum_len += ft_format_and_print(nmbstr, n, flags);
	free(nmbstr);
	return (cum_len);
}
