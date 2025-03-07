/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:54:11 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/23 11:11:15 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_syntax.h"

int	ft_syntax_tokens2(t_token *tokens)
{
	if ((tokens->type == REDIRECT_IN || tokens->type == D_REDIRECT_IN
			|| tokens->type == D_REDIRECT_OUT || tokens->type == REDIRECT_OUT)
		&& tokens->next->type == REDIRECT_IN)
		return (ft_putstr_fd("minishell: syntax error ", 2),
			ft_putstr_fd("near unexpected token `<'\n", 2), 1);
	if ((tokens->type == REDIRECT_IN || tokens->type == D_REDIRECT_IN
			|| tokens->type == D_REDIRECT_OUT || tokens->type == REDIRECT_OUT)
		&& tokens->next->type == D_REDIRECT_IN)
		return (ft_putstr_fd("minishell: syntax error ", 2),
			ft_putstr_fd("near unexpected token `<<'\n", 2), 1);
	if ((tokens->type == REDIRECT_IN || tokens->type == D_REDIRECT_IN
			|| tokens->type == D_REDIRECT_OUT || tokens->type == REDIRECT_OUT)
		&& tokens->next->type == REDIRECT_OUT)
		return (ft_putstr_fd("minishell: syntax error ", 2),
			ft_putstr_fd("near unexpected token `>'\n", 2), 1);
	if ((tokens->type == REDIRECT_IN || tokens->type == D_REDIRECT_IN
			|| tokens->type == D_REDIRECT_OUT || tokens->type == REDIRECT_OUT)
		&& tokens->next->type == D_REDIRECT_OUT)
		return (ft_putstr_fd("minishell: syntax error ", 2),
			ft_putstr_fd("near unexpected token `>>'\n", 2), 1);
	return (0);
}

int	ft_syntax_tokens3(t_token *tokens)
{
	if (tokens->type == REDIRECT_IN && tokens->next->type == REDIRECT_IN)
		return (ft_putstr_fd("minishell: syntax error ", 2),
			ft_putstr_fd("near unexpected token `<'\n", 2), 1);
	if ((tokens->type == PIPE && tokens->next == NULL)
		|| (tokens->type == REDIRECT_IN && tokens->next->type == PIPE)
		|| (tokens->type == D_REDIRECT_IN && tokens->next == NULL
			&& tokens->next->type == PIPE)
		|| (tokens->type == D_REDIRECT_OUT && tokens->next == NULL
			&& tokens->next->type == PIPE)
		|| (tokens->type == REDIRECT_OUT && tokens->next->type == PIPE)
		|| (tokens->type == PIPE && tokens->next->type == PIPE))
		return (ft_putstr_fd("minishell: syntax error ", 2),
			ft_putstr_fd("near unexpected token `|'\n", 2), 1);
	return (0);
}

int	ft_syntax_tokens_quotes(t_token *tokens)
{
	int		i;
	char	quotes;

	while (tokens)
	{
		i = 0;
		while (tokens->content && tokens->content[i])
		{
			if (tokens->content[i] == '\'' || tokens->content[i] == '\"')
			{
				quotes = tokens->content[i++];
				while (tokens->content[i]
					&& tokens->content[i] != quotes)
					i++;
				if ((tokens->content[i] && tokens->content[i] != quotes)
					|| !tokens->content[i])
					return (ft_putstr_fd("minishell: syntax error ", 2),
						ft_putstr_fd("unclosed quotes\n", 2), 1);
			}
			i++;
		}
		tokens = tokens->next;
	}
	return (0);
}

int	ft_syntax_tokens(t_token *tokens)
{
	if (tokens->type == PIPE)
		return (ft_putstr_fd("minishell: syntax error near", 2),
			ft_putstr_fd(" unexpected token `|'\n", 2), 1);
	while (tokens)
	{
		if ((tokens->type == REDIRECT_IN || tokens->type == D_REDIRECT_IN
				|| tokens->type == D_REDIRECT_OUT
				|| tokens->type == REDIRECT_OUT) && tokens->next == NULL)
			return (ft_putstr_fd("minishell: syntax error ", 2),
				ft_putstr_fd("near unexpected token `newline'\n", 2), 1);
		if (ft_syntax_tokens2(tokens)
			|| ft_syntax_tokens3(tokens))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
