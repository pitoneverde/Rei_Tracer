#include "minirt.h"
#include "libft.h"

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

// Error system glibc-like
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
	if (((str[0] == 's' && str[1] == 'p') ||
                (str[0] == 'p' && str[1] == 'l') ||
                (str[0] == 'c' && str[1] == 'y'))&& str[2] == ' ') {
		return (true);
            }
	return (false);
}

bool matrix_check_arguments(char **matrix) {
    for (int i = 0; matrix[i] != NULL; i++) {
        char *str = matrix[i];
        bool valid = false;
        
        if (str[0] == 'A' || str[0] == 'C' || str[0] == 'L') {
            valid = true;
        }
        else if (ft_strlen(str) >= 2) {
			if (valid_arguments_minirt(str))
				{
                valid = true;
            }
        }
        
        // Se una stringa non inizia con nessuno dei prefissi validi, ritorna falso
        if (!valid) {
            return false;
        }
    }
    
    // Tutte le stringhe iniziano con prefissi validi
    return true;
}

bool	parse_matrix(char *s1)
{
	char	**matrix;

	matrix = ft_split(s1, '\n');
	matrix = matrix_compress(matrix);
	print_debug_matrix(matrix); // da togliere
	if ((mtx_count((void **)matrix) < 4) || (matrix_strlen_check((char **)matrix)))
	{
		mtxfree_str(matrix);
		PRINT_ERR("Error: too few items or missing data\n");
		return (false);
	}
	if (!matrix_check_arguments(matrix))
	{
		mtxfree_str(matrix);
		PRINT_ERR("Error: too few items or missing data\n");
		return (false);
	}
	if (!check_matrix_data_is_good(matrix))
	{
		mtxfree_str(matrix);
		PRINT_ERR("Error: too few items or missing data\n");
		return (false);
	}
	mtxfree_str(matrix);
	return (true);
}

bool	readable_file_and_check_input(char *s1)
{

	s1 = compress_space(s1);
	printf("%s", s1); // per debug
	if (!check_split(s1))
	{
		PRINT_ERR("Error: too few items or missing data\n");
		return (false);
	}
	if (!parse_matrix(s1))
		return (false);
	return (true);
}

bool    parse_input(int argc, char **argv, t_element *data_file)
{
	(void)data_file;
	if (argc != 2)
	{
       	//printf("Usage: ./minirt <scene_file.rt>\n");
		//return (false);
		return(ERR_BAD_DATA);
	}
	int	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		PRINT_ERR("Error: %s does not exist or cannot access\n", argv[1]);
		return(false);
	}
	char *s1 = read_from_file(fd);
	close(fd);
	if (!readable_file_and_check_input(s1))
	{
		free(s1);
		return (false);
	}
	free(s1);
	return (true);
}
