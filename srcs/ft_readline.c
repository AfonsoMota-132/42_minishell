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

char	*ft_addstr(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		s1 = (char *) ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	if (ft_strlen(s1) + ft_strlen(s2) == 0)
	{
		free(s1);
		return (NULL);
	}
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1),
			sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	free(s1);
	return (str);
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

char	*ft_readline(char *str)
{
	char	*buffer;
	int		bytes;
	char	*line;

	line = NULL;
	ft_printf("%s", str);
	buffer = malloc(sizeof(char) * 11);
	while (1)
	{
		bytes = read(1, buffer, 10);
		buffer[bytes] = '\0';
		line = ft_addstr(line, buffer);
		if (ft_strchr(line, '\n'))
			break ;
	}
	free (buffer);
	return (ft_rmv_nl(line));
}
