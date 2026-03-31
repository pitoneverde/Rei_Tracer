/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:17:19 by gmu               #+#    #+#             */
/*   Updated: 2026/03/31 16:34:14 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H 1
# define _GNU_SOURCE

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdbool.h>
# include <errno.h>
# include "libft.h"
# include "math_engine.h"
# include "minirt_data.h"
# include "parsing_minirt.h"
# include "mlx_minirt.h"
# include "minirt_renderer.h"

// Error: message
#define PRINT_ERR(fmt, ...) \
	do {\
		fprintf(stderr, "Error\n @ %s:%d in %s() " fmt "\n", \
		 __FILE__, __LINE__, __func__, ##__VA_ARGS__);\
	} while(0);

#endif
