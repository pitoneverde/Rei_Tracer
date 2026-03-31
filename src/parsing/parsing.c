/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gio <gio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:07:44 by gio               #+#    #+#             */
/*   Updated: 2026/03/31 23:34:52 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

#define ERR_BAD_DATA 1
#define MSG_BAD_DATA "Usage: ./minirt <scene_file.rt> %d\n"

// //main()
// // check_parsing_error(int err_code); <--- ERR_* = printf(MSG_*, id);
// #define ERR_NO_DATA 2
// #define ERR_INVALID_FILENAME 3
// #define ERR_TOO_MANY_ARGS 4
// #define ERR_ARGM
// #define ERR_TO_MSG(err) ((ERR_## = MSG_##))
// //...

bool	valid_arguments_minirt(char *str)
{
	if (((str[0] == 's' && str[1] == 'p') || (str[0] == 'p' && str[1] == 'l')
			|| (str[0] == 'c' && str[1] == 'y')) && str[2] == ' ')
	{
		return (true);
	}
	return (false);
}

bool	matrix_check_arguments(char **matrix)
{
	char	*str;
	bool	valid;
	int		i;

	i = 0;
	while (matrix[i] != NULL)
	{
		str = matrix[i];
		valid = false;
		if (str[0] == 'A' || str[0] == 'C' || str[0] == 'L')
			valid = true;
		else if (ft_strlen(str) >= 2)
		{
			if (valid_arguments_minirt(str))
				valid = true;
		}
		if (!valid)
			return (false);
		++i;
	}
	return (true);
}

bool	parse_matrix(char *s1)
{
	char	**matrix;

	matrix = ft_split(s1, '\n');
	matrix = matrix_compress(matrix);
	if ((mtx_count((void **)matrix) < 4) || (matrix_strlen_check(matrix)))
	{
		mtxfree_str(matrix);
		printf("Error: too few items or missing data\n");
		return (false);
	}
	if (!matrix_check_arguments(matrix))
	{
		mtxfree_str(matrix);
		printf("Error: too few items or missing data\n");
		return (false);
	}
	if (!check_matrix_data_is_good(matrix))
	{
		mtxfree_str(matrix);
		printf("Error: too few items or missing data\n");
		return (false);
	}
	mtxfree_str(matrix);
	return (true);
}

bool	readable_file_and_check_input(char *s1)
{
	s1 = compress_space(s1);
	if (!check_split(s1))
	{
		printf("Error: too few items or missing data\n");
		return (false);
	}
	if (!parse_matrix(s1))
		return (false);
	return (true);
}

t_element	*parse_input(int argc, char **argv)
{
	int			fd;
	char		*s1;
	t_element	*elements;

	if (argc != 2)
	{
		printf("Usage: ./minirt <scene_file.rt>\n");
		return (NULL);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error: %s does not exist or cannot access\n", argv[1]);
		return (NULL);
	}
	s1 = read_from_file(fd);
	close(fd);
	if (!readable_file_and_check_input(s1))
	{
		free(s1);
		return (NULL);
	}
	elements = init_data_minirt(s1);
	free(s1);
	return (elements);
}
