/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_numlen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:07:42 by gmu               #+#    #+#             */
/*   Updated: 2025/02/17 22:07:44 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned_numlen(unsigned long num, int base)
{
	int	len;

	if (base < 2 || base > 16)
		return (0);
	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num = num / base;
		len++;
	}
	return (len);
}
