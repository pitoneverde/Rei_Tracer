/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:07:56 by gmu               #+#    #+#             */
/*   Updated: 2025/02/17 22:07:59 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_hex_to_str(unsigned long int num, char *str, size_t len)
{
	int	mod;

	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	len--;
	while (len != (size_t)-1)
	{
		mod = num % 16;
		if (mod < 10)
			str[len] = mod + '0';
		else if (mod >= 10)
			str[len] = (mod - 10) + 'a';
		num = num / 16;
		len--;
	}
	return (str);
}

char	*ft_itoa_hex(unsigned long int num, int is_up)
{
	size_t	len;
	char	*str;
	int		i;

	len = ft_numlen(num, 16);
	str = 0;
	str = ft_hex_to_str(num, str, len);
	if (!str)
		return (NULL);
	if (is_up == 1)
	{
		i = 0;
		while (str[i])
		{
			if (str[i] >= 'a' && str[i] <= 'f')
				str[i] -= 32;
			i++;
		}
	}
	return (str);
}
