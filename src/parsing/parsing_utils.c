#include "minirt.h"
#include "libft.h"

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
