/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_short_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:09:59 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/05 09:10:40 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_token	*ft_take_ro_out(t_token *head, t_token *tokens, int i)
{
	t_token	*tmp;

	if (i == -1)
		return (tokens);
	tokens = head;
	while (tokens && tokens->type != PIPE)
	{
		tmp = tokens->next;
		if (tokens->next && (tokens->next->type == D_REDIRECT_OUT
				|| tokens->next->type == REDIRECT_OUT)
			&& tokens->next->next && i == 1)
		{
			tokens->next = tokens->next->next->next;
			ft_free_token(tmp);
			break ;
		}
		else if (tokens->next && (tokens->next->type == D_REDIRECT_OUT
				|| tokens->next->type == REDIRECT_OUT)
			&& tokens->next->next && !(--i))
			tokens = tokens->next;
		else
			tokens = tokens->next;
	}
	return (head);
}

void	ft_redir_short_out(t_token *tokens)
{
	t_token	*head;
	int		i;

	while (tokens)
	{
		i = -1;
		head = tokens;
		while (tokens && tokens->type != PIPE)
		{
			if ((tokens->type == D_REDIRECT_OUT
					|| tokens->type == REDIRECT_OUT))
			{
				if (access(tokens->next->content, W_OK) == -1)
					i = 0;
				else
					i = 1;
				break ;
			}
			else
				tokens = tokens->next;
		}
		tokens = ft_take_ro_out(head, tokens, i);
		if (tokens && tokens->next)
			tokens = tokens->next;
	}
}
