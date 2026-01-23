#include "minirt.h"
#include "libft.h"

double convert_double_strtod(char *str)
{
	char *endptr;
	double result = strtod(str, &endptr);

	if (str == endptr)
	{
	    printf("Error: numer not converted\n");
	    return 0.0;
	}

	if (*endptr != '\0' && !ft_isspace(*endptr)) {
	    printf("Error: extra carcter before numbers: '%s'\n", endptr);
	}
	return result;
}

int parse_double(char *str)
{
	double	value;

	value = convert_double_strtod(str);
	if (value < 0.0 || value > 1.0)
		return (0);
	return (1);
}

/*Controlla la lettera a e poi controlla il formato float
 * ['A'] [float]
*/
// check_matrix_data_is_good:
// if (check_ambient(...)) --> != 0 errore
// check(err); copia il codice errore nella funzione chaiamante
// return (err2); err2 piu' generico di err

// parse_input: required
// if (check_matrix_data....) ->> errore = err2
// check(err);
// return(err-parse)(";

//main:
// if (parse_input(...))
// check(err-parse);
// exit(err-main);

bool	check_ambient(char *str)
{
	if (ft_word_count(str) != 3)
	{
		PRINT_ERR("Error: missing element in line A\n");
		return 0;
	}
	char	**check_matrix = ft_split(str, ' ');
	if (ft_strcmp(check_matrix[0], "A"))
	{
		PRINT_ERR("Error: missing A\n");
		mtxfree_str(check_matrix);
		return (0);
	}

	if (!parse_double(check_matrix[1]))
	{
		PRINT_ERR("Error: missing a float in line A\n");
		mtxfree_str(check_matrix);
		return (0);
	}
	if(!check_rgb_format(check_matrix[2]))
	{
		PRINT_ERR("Error: rgb format wrong\n");
		mtxfree_str(check_matrix);
		return (0);
	}
	mtxfree_str(check_matrix);
	return (1);
}

/*controlla le varie righe siano
formattate in modo corretto */

bool	check_matrix_data_is_good(char **matrix)
{
	if (!check_ambient(matrix[0]))
		return (false);
	printf("La riga A va bene\n");
	if (!check_camera(matrix[1]))
		return (false);
	printf("La riga C va bene\n");
	//if (!check_light(matrix[2]))
	//	return (0);
	//printf("La riga L va bene\n");
	//int	i = 0;
	//while (ft_strcmp(matrix[i], "sp"))
	//{
	//	if (!check_spere(matrix[i]))
	//		return (false);
	//	++i;
	//}
	//while (ft_strcmp(matrix[i], "pl"))
	//{
	//	if (!check_plane(matrix[i]))
	//		return (false);
	//	++i;
	//}
	//while (ft_strcmp(matrix[i], "cy"))
	//{
	//	if (!check_cylinder(matrix[i]))
	//		return (false);
	//	++i;
	//}
	//if (matrix[i])
	//	return (false);
	return (true);
}
