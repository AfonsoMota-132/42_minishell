/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 09:03:43 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/02 09:04:11 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_syntax(char *command)
{
	int		i;
	char	quote;

	i = -1;
	while (command[++i])
	{
		if (command[i] == '"' || command[i] == '\'')
		{
			quote = command[i++];
			while (command[i] && command[i] != quote)
				i++;
			if (command[i] != quote)
				return (printf("Syntax error\nUnclosed quotes\n"));
		}
		if (command[i] == '|' && command[i + 1] == '|')
			return (printf("Syntax error\nToo many pipes\n"));
		if ((command[i] == '<' && command[i + 1] == '<'
			&& command[i + 2] == '<')
			|| (command[i] == '>' && command[i + 1] == '>'
			&& command[i + 2] == '>'))
			return (printf("Syntax error\nToo many redirects\n"));
		if (command[i] == '\\' || command[i] == ';'
			|| (command[i] == '&' && command[i + 1] == '&'))
			return (printf("Syntax error\nUnrecognized intachter(s)\n"));
	}
	return (0);
}
