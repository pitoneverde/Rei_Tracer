#include "minirt.h"
#include "libft.h"

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

int	matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while(matrix[i])
		++i;
	return (i);
}

bool	check_n_comma(char *s, int n_comma)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ',')
			--n_comma;
		++i;
	}
	if (n_comma != 0)
		return (false);
	return (true);
}

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


bool convertable_double(double *value, const char *str)
{
	if (!str || *str == '\0')
		return false;
	char *endptr;
	errno = 0;
	double result = strtod(str, &endptr);

	if (errno == ERANGE)
		return false;
	if (endptr == str)
		return false;
	while (ft_isspace((unsigned char)*endptr))
		endptr++;
	if (*endptr != '\0')
		return false;
	if (value != NULL)
		*value = result;
	return true;
}

bool	check_coordinates(char *s)
{
	if (!check_n_comma(s, 2))
		return (false);
	char	**matrix = ft_split(s, ',');
	bool	is_good = true;
	int i = 0;
	double	val[3];
	if (matrix_size(matrix) != 3)
		is_good = false;
	while(i < matrix_size(matrix))
	{
		if (!convertable_double(&val[i], matrix[i]))
			is_good = false;
		++i;
	}
	mtxfree_str(matrix);
	return (is_good);
}

/*funzione utility che conta le parole in una stringa*/
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

/*controlla che la parte ['A'] ['float'] [rgb]
                                        questa sopra
                            sia corretta*/
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

bool	check_normalizzation_limits(char *str)
{
	if (!check_coordinates(str))
		return (false);
	char	**matrix = ft_split(str, ',');
	int	i;
	bool	good;
	good = true;
	i = 0;
	while (matrix[i])
	{
		double val = convert_double_strtod(matrix[i]);
		if (val < -1 || val > 1)
			good = false;
		++i;
	}
	mtxfree_str(matrix);
	return (good);
}
