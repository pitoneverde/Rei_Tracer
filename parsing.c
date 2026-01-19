#include "minirt.h"
#include "libft.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

void	print_debug_matrix(char **matrix)
{
	int	i;

	i = 0;
	printf("debug matrix\n");
	while(matrix[i])
	{
		printf("%d [%s]\n",i , matrix[i]);
		++i;
	}
}

int	is_empty_lines(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
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

/*
 questo semplicemente
 toglie gli spazi doppi
 */

char	*compress_space(char *str)
{
	int	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (str[i[1]] != '\0')
	{
		if (str[i[1]] == ' ')
		{
			if (i[2] == 0)
			{
				str[i[0]++] = ' ';
				i[2] = 1;
			}
		}
		else
		{
			str[i[0]++] = str[i[1]];
			i[2] = 0;
		}
		++i[1];
	}
	str[i[0]] = '\0';
	return (str);
}

int	matrix_strlen_check(char **matrix)
{
	int	i;

	i = 0;
	while(matrix[i])
	{
		if (ft_strlen(matrix[i]) < 11)
			return (1);
		++i;
	}
	return (0);
}

int	check_rgb_format(char *str)
{
	int	i[4];

	i[0] = 0;
	i[2] = 0;
	i[3] = ft_strlen(str);
	while (i[0] < i[3] && i[2] < 3)
	{
		while (str[i[0]] && (str[i[0]] == ' ' || str[i[0]] == '\t'))
			i[0]++;
		if (!ft_isdigit(str[i[0]]))
			return (0);
		i[1] = 0;
		while (str[i[0]] && ft_isdigit(str[i[0]]))
			i[1] = i[1] * 10 + (str[i[0]++] - '0');
		if (i[1] < 0 || i[1] > 255)
			return (0);
		while (str[i[0]] && (str[i[0]] == ' ' || str[i[0]] == '\t'))
			i[0]++;
		if (i[2] < 2)
			if (str[i[0]++] != ',')
				return (0);
		i[2]++;
	}
	return (i[2] == 3 && str[i[0]] == '\0');
}

int	ft_word_count(char *str)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	if(!str)
		return (0);

	while(str[i])
	{
		if (ft_isspace(str[i]))
			in_word = 0;
		else if (!in_word)
		{
			++count;
			in_word = 1;
		}
		++i;
	}
	return (count);
}

int check_integer_is_valid(char *n)
{
	if (n == NULL || *n == '\0')
		return (0);

    int i = 0;
	if (n[i] == '+' || n[i] == '-')
		i++;

	if (n[i] == '\0')
		return (0);

	while (n[i] != '\0')
	{
		if (!ft_isdigit((unsigned char)n[i]))
			return (0);
		i++;
	}

	return (1);
}

int ft_atoi_minirt(const char *str)
{
	int	value;
	int		sign;

	sign = 1;
	value = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
		sign = 44 - *str++;
	while (ft_isdigit(*str))
	{
		value = value * 10 + (*str++ - '0');
		if (value > 1 && sign == -1)
			return (sign * value);
		if (value > 255 && sign == 1)
			return (sign * value);
	}
	return (sign * value);
}

int check_a_ok1(char *str)
{
    char   **check_matrix = ft_split(str, ',');

    if (mtx_count((void **)check_matrix) != 3)
    {
        mtxfree_str(check_matrix);
        return (0);
    }
    int i = 0;
    while (i < 4)
    {
        if (!check_integer_is_valid(check_matrix[i]))
        {
            mtxfree_str(check_matrix);
            return (0);
        }
        if (0 > ft_atoi_minirt(check_matrix[i]) || ft_atoi_minirt(check_matrix[i]) > 255)
        {
            mtxfree_str(check_matrix);
            return (0);
        }
    }
    mtxfree_str(check_matrix);
    return (1);
}

int	check_a_ok(char *str)
{
	//int	i;

	//i = 0;
	if (ft_word_count(str) != 3)
	{
		return 0;
	}
	char	**check_matrix = ft_split(str, ' ');
	if (!ft_strcmp(check_matrix[0], "A"))
	{
		mtxfree_str(check_matrix);
		return (0);
	}
	if ((ft_strlen(check_matrix[1]) != 3) && ft_isdigit(check_matrix[1][0]) && (check_matrix[1][1] == '.') && ft_isdigit(check_matrix[1][2]))
	{
		mtxfree_str(check_matrix);
		return (0);
	}
	//check_rgb
	printf("printa a \n\n");
	print_debug_matrix(check_matrix);

	return 1;
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
				mtxfree_str(new_matrix);
				return (NULL);
			}
			++j;
		}
		++i;
	}
	new_matrix[j] = NULL;
	mtxfree_str(matrix);
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
		free(s1);
		PRINT_ERR("Error: too few items or missing data\n");
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
	return (compress_space(content));
}

void    parse_input(int argc, char **argv, t_element *data_file)
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
	free(s1);
	matrix = matrix_compress(matrix);
	print_debug_matrix(matrix);
	if ((mtx_count((void **)matrix) < 4) || (matrix_strlen_check((char **)matrix)))
	{
		mtxfree_str(matrix);
		PRINT_ERR("Error: too few items or missing data\n");
		exit(1);
	}
	check_matrix_data_ok(matrix);
	mtxfree_str(matrix);
    return ;
}
