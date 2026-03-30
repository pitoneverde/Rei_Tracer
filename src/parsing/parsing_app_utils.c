/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_app_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gio <gio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:47:07 by gio               #+#    #+#             */
/*   Updated: 2026/03/30 17:47:14 by gio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

/*splitta le parti e controla la lunghezza minima*/
int	check_split(char *s1)
{
	int	i;
	int	n_newline;

	i = 0;
	n_newline = 0;
	while (s1[i])
	{
		if (s1[i] == '\n')
			++n_newline;
		++i;
	}
	if (n_newline < 4)
		return (0);
	return (1);
}

/*carica tutto il file
 * dentro un char* e toglie gli spazi doppiu
 */

/*il file deve avere una lunghezza determinata*/
int	matrix_strlen_check(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		if (ft_strlen(matrix[i]) < 11)
			return (1);
		++i;
	}
	return (0);
}

char	*read_from_file(int fd)
{
	char	*line;
	char	*content;
	char	*temp;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = content;
		content = ft_strjoin(content, line);
		free(temp);
		free(line);
		if (!content)
			return (NULL);
	}
	return (compress_space(content));
}
