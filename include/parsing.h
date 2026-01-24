#ifndef PARSING_H
# define PARSING_H 1


// utility per parsing
bool	check_n_comma(char *s, int n_comma);
int	ft_word_count(char *str);
int	check_rgb_format(char *str);
bool convertable_double(double *value, const char *str);
double	convert_double_strtod(char *str);
bool   check_coordinates(char *s);


//funzioni chiamate
bool    check_ambient(char *str);
bool	check_camera(char *str);
bool	check_light(char *s);

// funzione che chiama le funzioni sopra e controlla riga per riga
bool	check_matrix_data_is_good(char **matrix);

//funzione chiamata nel main che controlla il numero di '\n' minimo e la lunghezza minima della stringa
bool    parse_input(int argc, char **argv, t_element *data_file);

//utility per debug
void	print_debug_matrix(char **matrix);

#endif
