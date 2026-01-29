#ifndef PARSING_H
# define PARSING_H 1

// utility per parsing
bool	check_n_comma(char *s, int n_comma);
int	ft_word_count(char *str);
int	check_rgb_format(char *str);
bool convertable_double(double *value, const char *str);
double	convert_double_strtod(char *str);
bool   check_coordinates(char *s);
bool	check_normalizzation_limits(char *str);


//funzioni chiamate
bool    check_ambient(char *str);
bool	check_camera(char *str);
bool	check_light(char *str);
bool	check_sphere(char *str);
bool	check_plane(char *str);
bool	check_cylinder(char *str);

// funzione che chiama le funzioni sopra e controlla riga per riga
// questa e' quella da modificare nel caso volessi aggiungere
// altre forme geometriche, per farlo aggiungi una funzione nella cascata degli if else
// le funzioni che stanno sopra controllano il formato riga per riga
// se realmente non e' chiaro ancora cosa fanno usa il printf
// per stampare le stringhe e usa print_debug_matrix
// per stampare le matrici,
// la funzione e' qua sotto per vedere cosa contiene
// DOPO aver letto il contenuto delle
// stringhe o matrici e' impossibile non capire
bool	check_matrix_data_is_good(char **matrix);

//funzione chiamata nel main che controlla il numero di '\n' minimo e la lunghezza minima della stringa
t_element *parse_input(int argc, char **argv);

//utility per debug
void	print_debug_matrix(char **matrix);

//init dei dati
// i dati sono gia' formattati in modo corretto
// bisogna modificare anche questo file che infila i dati
// in t_element nella cascata di if else
t_element *init_data_minirt(char *s);

#endif
