#include "minirt.h"
#include "libft.h"

/*
int    is_id_char(const char **c)
{
    if (**c == 'A' || **c == 'C'|| **c == 'L')
        return (1);
    if (**c == 's' && *(*c + 1) == 'p')
        return (1);
    if (**c == 'p' && *(*c + 1) == 'l')
        return (1);
    if (**c == 'c' && *(*c + 1) == 'y')
        return (1);
    return (0);
}
*/
/*
char *read_next_token(const char *line, const char **p)
{
    if (*p == NULL)
        return (NULL);
    if (!is_id_char(**p))
    {
		PRINT_ERR();
        return (NULL);
    }
    
    {
    }
    
	
	if (is_id_char(*p))	read_id(p)
	if (is_signed_num(*p)) read_data(p)
	usare strbuilder
	printf("file: %s", __FILE__, __LINE__, __func__, __DATE__, __TIME__, )
	
}*/
/*
t_list *tokenize(const char *line)
{
    t_list		*tokens;
    t_list        *new_token;
    char        *word;
	const char	*p = line;

	if (!line)
		return (NULL);
	tokens = NULL;
	while (*p)
	{
        //while(is_whitespace(*p))
        //    ++p;
		if(*p == '\0' || *p == '\n')
			break ;
        word = read_next_token(line, &p);
        if (!word)
			return (ft_lstclear(&tokens, free), NULL);
        new_token = ft_lstnew(word);
        if (new_token == NULL)
            return (free(word), ft_lstclear(&tokens, free), NULL);
        ft_lstadd_back(&tokens, new_token);
	}
	return (tokens);
}*/

void    parse_input(int argc, char **argv)
{
    if (argc != 2)
	{
        printf("Usage: ./minirt <scene_file.rt>");
	}
	
	(void)argv;
    // exit (1);
    //t_list  *tokens;
	//while (!EOF)
	//line = get_next_line(scene.rt)
	//rt_parse(line);
	// if parsed == error
	//print error: invalid scene
	//else...
}