#include "minirt.h"
#include "libft.h"

void	free_matrix(char **matrix)
{
	int	i = 0;

	while(matrix[i])
	{
		free(matrix[i]);
		++i;
	}
	free(matrix);
}

int	is_empty_lines(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!(str[i] <= ' '))
			return (0);
		++i;
	}
	return (1);
}

int	count_non_empty_lines(char **matrix)
{
	int	count;
	int	i;

	if (!matrix)
		return (0);
	count = 0;
	i = 0;
	while(matrix[i])
	{
		if (!is_empty_lines(matrix[i]))
			++count;
		++i;
	}
	return (count);
}

int	matrix_strlen_check(char **matrix)
{
	int	i;

	i = 0;
	while(matrix[i])
	{
		if (ft_strlen(matrix[i]) < 4)
			return (1);
	}
	return (0);
}

int	check_rgb_format(char *str)
{
	int	i;
	int	num;
	int	count;
	int	len;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	len = ft_strlen(str);
	while (i < len && count < 3)
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		num = 0;
		while (str[i] && ft_isdigit(str[i]))
		{
			num = num * 10 + (str[i] - '0');
			i++;
		}
		if (num < 0 || num > 255)
			return (0);
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (count < 2)
		{
			if (str[i] != ',')
				return (0);
			i++; // Salta la virgola
		}
		count++;
	}
	return (count == 3 && str[i] == '\0');
}

int	check_a_ok(char *str)
{
	int	i = 0;
	int	n_three = 0;

	n_three = 0;
	if (str[i] != 'A')
		n_three -= 1000;
	else
		++n_three;
	++i;
	if (!(str[i] <= ' '))
		n_three -= 1000;
	else
	{
		while(str[i] <= ' ')
			++i;
	}
	if (!(ft_isdigit(str[i]) && (str[i+1] == '.') && ft_isdigit(str[i+2])))
		n_three -= 1000;
	else
		++n_three;
	i += 3;
	if (check_rgb_format(&str[i]))
		n_three -= 1000;
	else
		++n_three;

	if (n_three != 3)
	{
		PRINT_ERR("Error: format should be\nA [0.0 - 1.0] [0 - 255], [0 - 255], [0 - 255]\n");
		return (0);
	}
	return (1);
}

int	check_matrix_data_ok(char **matrix)
{
	int	i = 0;
	if (!check_a_ok(matrix[0]))
		return (0);
	++i;
	return (1);
}

char	**matrix_compress(char **matrix)
{
	char	**new_matrix;
	int	i;
	int	j;
	int	non_empty_lines;

	if (!matrix)
		return (NULL);

	non_empty_lines = count_non_empty_lines(matrix);
	new_matrix =malloc(sizeof(char *) * (non_empty_lines + 1));
	if (!new_matrix)
		return (NULL);
	i = 0;
	j = 0;
	while(matrix[i])
	{
		if (!is_empty_lines(matrix[i]))
		{
			new_matrix[j] = ft_strdup(matrix[i]);
			if (!new_matrix[j])
			{
				free_matrix(new_matrix);
				return (NULL);
			}
			++j;
		}
		++i;
	}
	new_matrix[j] = NULL;
	free_matrix(matrix);
	return (new_matrix);
}


char	**splitted(char *s1)
{
	int	i = 0;
	int	n_newline = 0;
	char	**matrix = NULL;

	while(s1[i])
	{
		if (s1[i] == '\n')
		{
			++n_newline;
		}
		++i;
	}
	if (n_newline < 4)
	{
		PRINT_ERR("Error: too few items or missing data\n");
		free(s1);
		exit(1);
	}
	matrix = ft_split(s1, '\n');
	return (matrix);
}

char	*read_from_file(int fd)
{
	char	*line;
	char	*content;
	char	*temp;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	while(1)
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
	return (content);
}

void    parse_input(int argc, char **argv, t_element data_file)
{
	(void)data_file;
	if (argc != 2)
	{
        	printf("Usage: ./minirt <scene_file.rt>\n");
		exit (1);
	}
	int	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		PRINT_ERR("Error: %s does not exist or cannot access\n", argv[1]);
		exit(1);
	}
	char *s1 = read_from_file(fd);
	close(fd);
	printf("%s", s1);
	char	**matrix = splitted(s1);
	matrix = matrix_compress(matrix);
	if ((mtx_count((void **)matrix) < 5) || (matrix_strlen_check((char **)matrix)))
	{
		PRINT_ERR("Error: too few items or missing data\n");
		free_matrix(matrix);
		exit(1);
	}
	check_matrix_data_ok(matrix);
	
	free_matrix(matrix);
	free(s1);
}
