/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:55:53 by gmu               #+#    #+#             */
/*   Updated: 2024/12/02 14:55:55 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*result;

	len = ft_strlen(s) + 1;
	result = (char *) malloc(len);
	if (result == NULL)
		return (NULL);
	return ((char *) ft_memcpy(result, s, len));
}
