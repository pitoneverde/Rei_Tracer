/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:13:35 by gmu               #+#    #+#             */
/*   Updated: 2025/02/17 22:13:39 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_format	ft_flags_handle(void)
{
	t_format	flags;

	flags.spec = 0;
	flags.width = 0;
	flags.left = 0;
	flags.zero = 0;
	flags.star = 0;
	flags.precision = -1;
	flags.hash = 0;
	flags.space = 0;
	flags.plus = 0;
	return (flags);
}

static int	ft_handle(char *str, va_list args)
{
	int			i;
	int			j;
	int			count;
	t_format	flags;

	i = -1;
	count = 0;
	while (str[++i])
	{
		flags = ft_flags_handle();
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			j = ft_init_flags(str, i, args, &flags);
			if (flags.spec > 0)
				i = j;
			if (str[i] != '\0' && flags.spec > 0 && ft_isspec(str[i]))
				count += ft_init_format(str[i], args, flags);
			else if (str[i] != '\0')
				count += ft_putchar(str[i]);
		}
		else
			count += ft_putchar(str[i]);
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			cum_len;
	char		*dest;

	if (!str || *str == '\0')
		return (0);
	dest = ft_strdup(str);
	if (!dest || *dest == '\0')
		return (0);
	cum_len = 0;
	va_start(args, str);
	cum_len = ft_handle(dest, args);
	va_end(args);
	free(dest);
	return (cum_len);
}
