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

#include "../incs/minishell.h"

int	ft_syntax_tokens(t_token *tokens)
{
	if (tokens->type == PIPE)
		return (ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2), 1);
	while (tokens)
	{
		if ((tokens->type == REDIRECT_IN || tokens->type == D_REDIRECT_IN
				|| tokens->type == D_REDIRECT_OUT
				|| tokens->type == REDIRECT_OUT) && tokens->next == NULL)
			return (ft_putstr_fd("minishell: syntax error ", 2),
					ft_putstr_fd("near unexpected token `newline'idk\n", 2), 1);
		else if ((tokens->type == PIPE && tokens->next == NULL)
			|| (tokens->type == PIPE && tokens->next == NULL
				&& tokens->next->type == PIPE) || (tokens->type == REDIRECT_IN
				&& tokens->next == NULL && tokens->next->type == PIPE)
			|| (tokens->type == D_REDIRECT_IN && tokens->next == NULL
				&& tokens->next->type == PIPE)
			|| (tokens->type == D_REDIRECT_OUT && tokens->next == NULL
				&& tokens->next->type == PIPE)
			|| (tokens->type == REDIRECT_OUT && tokens->next->type == PIPE)
			|| (tokens->type == PIPE && tokens->next->type == PIPE))
			return (ft_putstr_fd("minishell: syntax error ", 2),
				ft_putstr_fd("near unexpected token `|'\n", 2), 1);
		tokens = tokens->next;
	}
	return (0);
}
