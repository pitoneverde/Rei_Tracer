#ifndef PARSING_H
# define PARSING_H 1

int	ft_word_count(char *str);
int	check_rgb_format(char *str);

bool    parse_input(int argc, char **argv, t_element *data_file);
bool	check_camera(char *str);
int	check_matrix_data_is_good(char **matrix);

#endif
