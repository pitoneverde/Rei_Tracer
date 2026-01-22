#include "minirt.h"
#include "libft.h"

/* funzione utility per stampare la matrice per debug*/
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

/*funzione utility per determinare se nella riga ci sono solo spazi vuoti*/

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

/* conta il numero di righe non vuote*/
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

/*il file deve avere una lunghezza determinata*/
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





/*controlla che quando un numero e'
 di formato integer che tra le
 lettere ci siano solo digits*/
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
		if (!ft_isdigit(n[i]))
			return (0);
		i++;
	}

	return (1);
}

/* controlla e fa atoi per minirt
    il numero deve essere compreso tra
    0 e 255 */
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




/* toglie le sgtringhe vuote dalla matrice
 */

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


/*splitta le parti e controla la lunghezza minima*/

int	check_split(char *s1)
{
	int	i = 0;
	int	n_newline = 0;

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
		return (0);
	}
	return (1);
}

/*carica tutto il file
 * dentro un char* e toglie gli spazi doppiu
 */

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

/*tenta di aprire un file
 * toglie le stringhe vuote
 * e poi passsa tutto a check_matrix_data_ok
 * per assicurarsi che i dati sono formattati in modo corretto
 */
int    parse_input(int argc, char **argv, t_element *data_file)
{
	(void)data_file;
	if (argc != 2)
	{
       	printf("Usage: ./minirt <scene_file.rt>\n");
		return (1);
	}
	int	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		PRINT_ERR("Error: %s does not exist or cannot access\n", argv[1]);
		return (1);
	}
	char *s1 = read_from_file(fd);
	s1 = compress_space(s1);
	close(fd);
	printf("%s", s1);
	if (!check_split(s1))
	{
		free(s1);
		PRINT_ERR("Error: too few items or missing data\n");
		return (0);
	}

	char	**matrix = ft_split(s1, '\n');
	free(s1);
	matrix = matrix_compress(matrix);
	print_debug_matrix(matrix);
	if ((mtx_count((void **)matrix) < 4) || (matrix_strlen_check((char **)matrix)))
	{
		mtxfree_str(matrix);
		PRINT_ERR("Error: too few items or missing data\n");
		return (0);
	}
	check_matrix_data_is_good(matrix);
	mtxfree_str(matrix);
	return 1;
}
