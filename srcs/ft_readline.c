/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:55:02 by afogonca          #+#    #+#             */
/*   Updated: 2024/12/17 20:39:12 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*ft_addstr(char *s1, char s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (ft_strlen(s1) == 0 && !s2)
	{
		free(s1);
		return (NULL);
	}
	str = ft_calloc((ft_strlen(s1) + 2),
			sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	str[i++] = s2;
	str[i] = '\0';
	free(s1);
	return (str);
}
char ft_get_keypress() 
{
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 1;  
	newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return (ch);
}

char	*ft_rmv_nl(char *str)
{
	int		i;
	char	*nstr;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	nstr = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (str[++i] != '\0' && str[i] != '\n')
		nstr[i] = str[i];
	nstr[i] = '\0';
	free(str);
	return (nstr);
}

void	ft_fill(char *line)
{
	if (!line)
		printf("line is null\n");
}

char	*ft_readline(char *str)
{
	int		keypress;
	char	*line;

	line = NULL;
	ft_printf("%s\n", str);
	while (1)
	{
		keypress = ft_get_keypress();
		if (keypress == 9)
			ft_fill(line);
		if (keypress == 10)
			break ;
		if (keypress >= 65 && keypress <= 67)
		{
			printf("entered\n");
			continue ;
		}
		printf("keypress: %d\n", keypress);
		if (!line)
		{
			line = ft_calloc(1, sizeof(char));
			if (!line)
				return (NULL);
		}
		line = ft_addstr(line, keypress);
		printf("line: %s\n", line);
	}
	return (line);
}
