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

#include "ft_syntax.h"

int	ft_quote_syntax(char *command)
{
	int		i;
	char	quote;

	i = -1;
	while (command[++i] && \
		(ft_strchr(&command[i], '\'')
			|| ft_strchr(&command[i], '"')))
	{
		if (command[i] == '"' || command[i] == '\'')
		{
			quote = command[i++];
			while (command[i] && command[i] != quote)
				i++;
			if ((command[i] && command[i] != quote)
				|| !command[i])
				return (ft_putstr_fd("Minishell: Syntax error", 2),
					ft_putstr_fd(" unclosed quotes\n", 2), 1);
		}
	}
	return (0);
}

int	ft_pipe_syntax(char *command)
{
	int	i;

	i = -1;
	while (command[++i]
		&& ft_strchr("|", command[i]))
	{
		if (command[i] == '|' && command[i + 1]
			&& command[i + 1] == '|')
			return (ft_putstr_fd("Minishell: Syntax error", 2),
				ft_putstr_fd(" too many pipes\n", 2), 1);
	}
	return (0);
}

int	ft_redirect_syntax(char *command)
{
	int	i;

	i = -1;
	while (command[++i])
	{
		if (command[i] == '>' && command[i + 1] == '<')
			return (ft_putstr_fd("minishell: syntax error near", 2),
				ft_putstr_fd(" unexpected token `<'\n", 2), 1);
		else if (command[i] == '<' && command[i + 1] == '>')
			return (ft_putstr_fd("minishell: syntax error near", 2),
				ft_putstr_fd(" unexpected token `>'\n", 2), 1);
		if ((command[i] == '>' || command[i] == '<')
			&& (command[i + 1] == '>' || command[i + 1] == '<')
			&& command[i + 2] == '>')
			return (ft_putstr_fd("minishell: syntax error near", 2),
				ft_putstr_fd(" unexpected token `>'\n", 2), 1);
		if ((command[i] == '>' || command[i] == '<')
			&& (command[i + 1] == '>' || command[i + 1] == '<')
			&& command[i + 2] == '<')
			return (ft_putstr_fd("minishell: syntax error near", 2),
				ft_putstr_fd(" unexpected token `newline'\n", 2), 1);
	}
	return (0);
}

int	ft_syntax(char *command)
{
	if (ft_quote_syntax(command)
		|| ft_pipe_syntax(command)
		|| ft_redirect_syntax(command))
		return (1);
	return (0);
}
