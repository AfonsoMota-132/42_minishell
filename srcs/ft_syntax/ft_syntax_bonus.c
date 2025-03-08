/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:58:56 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/08 20:00:03 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_syntax.h"

int	ft_ver_close_par(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == OUT_PAR && count == 0)
			return (ft_putstr_fd("minishell: syntax error ", 2),
				ft_putstr_fd("near unexpected token `)'\n", 2), 1);
		if (tokens->type == IN_PAR)
			count++;
		if (tokens->type == OUT_PAR && count)
			count--;
		tokens = tokens->next;
	}
	if (count)
		return (ft_putstr_fd("minishell: syntax error ", 2),
			ft_putstr_fd("near unexpected token `)'\n", 2), 1);
	return (0);
}

int	ft_syntax_par(t_token *tokens)
{
	if (ft_ver_close_par(tokens))
		return (1);
	while (tokens)
	{
		if ((tokens->type == AND || tokens->type == OR
				|| tokens->type == SEMI || tokens->type == PIPE)
			&& tokens->next && tokens->next->type == OUT_PAR)
			return (ft_putstr_fd("minishell: syntax error ", 2),
				ft_putstr_fd("near unexpected token `)'\n", 2), 1);
		if ((tokens->type == AND || tokens->type == OR
				|| tokens->type == SEMI || tokens->type == PIPE)
			&& tokens->next && tokens->next->type == IN_PAR)
			return (ft_putstr_fd("minishell: syntax error ", 2),
				ft_putstr_fd("near unexpected token `('\n", 2), 1);
		tokens = tokens->next;
	}
	return (0);
}

int	ft_syntax_con(t_token *tokens)
{
	if (tokens && (tokens->type == SEMI
			|| tokens->type == AND
			|| tokens->type == OR))
		return (ft_putstr_fd("minishell: syntax error\n", 2), 1);
	while (tokens)
	{
		if ((tokens->type == AND && tokens->next == NULL)
			|| (tokens->type == AND && tokens->next->type == AND
				&& tokens->next->type == OR && tokens->next->type == SEMI))
			return (ft_putstr_fd("minishell: syntax error ", 2),
				ft_putstr_fd("near unexpected token `&&'\n", 2), 1);
		if ((tokens->type == OR && tokens->next == NULL)
			|| (tokens->type == OR && tokens->next->type == AND
				&& tokens->next->type == OR && tokens->next->type == SEMI))
			return (ft_putstr_fd("minishell: syntax error ", 2),
				ft_putstr_fd("near unexpected token `||'\n", 2), 1);
		if ((tokens->type == SEMI && tokens->next == NULL)
			|| (tokens->type == SEMI && tokens->next->type == AND
				&& tokens->next->type == OR && tokens->next->type == SEMI))
			return (ft_putstr_fd("minishell: syntax error ", 2),
				ft_putstr_fd("near unexpected token `;'\n", 2), 1);
		tokens = tokens->next;
	}
	return (0);
}
