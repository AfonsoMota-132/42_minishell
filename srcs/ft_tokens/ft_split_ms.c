/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 09:17:34 by afogonca          #+#    #+#             */
/*   Updated: 2024/12/28 09:18:51 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tokens.h"

int	ft_quote_len(char const *s)
{
	int		i;
	char	quote;

	i = 0;
	if (s[i] == '"' || s[i] == '\'')
	{
		while (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
			if (!s[i])
				break ;
			i++;
			if (s[i] == ' ')
				break ;
		}
		i--;
	}
	return (i);
}

int	ft_seglen2(char const *s, int i)
{
	if ((s[i] == '|' && s[i + 1] == '|')
		|| (s[i] == '&' && s[i + 1] == '&'))
		return (2);
	if (s[i] == '|' || s[i] == ';')
		return (1);
	return (0);
}

int	ft_seglen(char const *s)
{
	int		i;
	char	quote;

	i = ft_quote_len(s);
	if (s[i] == '<' || s[i] == '>')
	{
		quote = s[i];
		i++;
		if (s[i] == quote)
			return (2);
		return (1);
	}
	if (ft_seglen2(s, i))
		return (ft_seglen2(s, i));
	while (s[i] && s[i] != ' ' && s[i] != '\t'
		&& s[i] != '|' && s[i] != '<'
		&& s[i] != '>' && s[i] != ';')
	{
		if (s[i] == '&' && s[i + 1] == '&')
			break ;
		i++;
		if (s[i] == '\'' || s[i] == '"')
			i += ft_quote_len(&s[i]);
	}
	return (i);
}

int	ft_count_parts(char const *s)
{
	int		i;
	int		j;
	char	*test;

	i = 0;
	j = 0;
	test = ft_substr(&s[i], 0, ft_seglen(&s[i]));
	while (ft_seglen(&s[i]) > 0)
	{
		free(test);
		j++;
		test = ft_substr(&s[i], 0, ft_seglen(&s[i]));
		i += ft_seglen(&s[i]);
		while (s[i] == ' ' || s[i] == '\t')
			i++;
	}
	free(test);
	return (j);
}

char	**ft_split_cmds(char *command)
{
	int		i;
	int		j;
	int		k;
	char	**commands;

	i = 0;
	k = -1;
	j = ft_count_parts(command);
	commands = ft_calloc(j + 1, sizeof(char *));
	if (!commands)
		return (NULL);
	while (++k < j)
	{
		while (command[i] == ' ' || command[i] == '\t')
			i++;
		commands[k] = ft_substr(&command[i], 0, ft_seglen(&command[i]));
		i += ft_seglen(&command[i]);
	}
	commands[k] = NULL;
	return (commands);
}
