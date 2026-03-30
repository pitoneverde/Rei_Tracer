/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:14:01 by gmu               #+#    #+#             */
/*   Updated: 2025/02/17 22:14:03 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>

typedef struct s_format
{
	int	spec;
	int	width;
	int	left;
	int	zero;
	int	star;
	int	precision;
	int	hash;
	int	space;
	int	plus;
}		t_format;

//	libft
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
void	ft_bzero(void *s, size_t n);
int		ft_putchar(char c);
void	*ft_memcpy(void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s);
//	libft printf
int		ft_isspec(int c);
int		ft_isflag(int c);

//	funzioni meta
int		ft_numlen(long num, int base);
char	*ft_itoa_base(long n, int base);
int		ft_unsigned_numlen(unsigned long num, int base);
int		ft_prefix(int is_up);
int		ft_print_str(const char *str);

//		funzioni ft_printf

int		ft_apply_padding(int total_width, int size, int zero);

int		ft_init_flags(const char *str, int i, va_list args, t_format *flags);
char	*ft_itoa_hex(unsigned long int num, int is_up);
int		ft_print_hexadecimal(unsigned int n, int is_up, t_format flags);
int		ft_print_unsigned_decimal(long n, t_format flags);
int		ft_print_decimal_integer(int n, t_format flags);
int		ft_print_pointer(unsigned long int ptr, t_format flags);
int		ft_init_format(char format, va_list args, t_format flags);
int		ft_printf(const char *str, ...);

#endif
