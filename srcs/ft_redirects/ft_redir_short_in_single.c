/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_short_in_single.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 08:52:19 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:28:09 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_token	*ft_rmv_ris_before(t_token *tokens, t_token *head)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = head;
	while (tmp && tmp->type != PIPE)
	{
		tmp2 = tmp->next;
		if (tmp->next && tmp->next->type == REDIRECT_IN
			&& tmp->next->next && tmp->next != tokens
			&& tmp->next->next->next)
		{
			tmp->next = tmp->next->next->next;
			ft_free_token(tmp2);
		}
		else if (tmp->next && tmp->next->type == REDIRECT_IN
			&& tmp->next->next && tmp->next != tokens)
		{
			tmp->next = NULL;
			ft_free_token(tmp2);
		}
		tmp = tmp->next;
	}
	tokens = head;
	return (NULL);
}

t_token	*ft_take_ris_out(t_token *tokens, t_token *tmp)
{
	t_token	*tmp2;

	if (!tmp)
		tokens = ft_skip_to_pipe(tokens);
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->next && tokens->next->type == REDIRECT_IN
			&& tokens->next->next && tokens->next != tmp)
		{
			tmp2 = tokens->next;
			tokens->next = tokens->next->next->next;
			ft_free_token(tmp2);
		}
		else
			tokens = tokens->next;
	}
	if (tokens && tokens->type == PIPE)
		tokens = tokens->next;
	return (tokens);
}

int	ft_redir_short_in_single2(t_token *tokens, t_token **tmp, t_token *head)
{
	if ((tokens->next->content[0] == '$' && tokens->next->quotes == 0)
		|| (access(tokens->next->content, F_OK) == -1
			|| access(tokens->next->content, R_OK) == -1))
	{
		(*tmp) = ft_rmv_ris_before(tokens, head);
		return (1);
	}
	(*tmp) = tokens;
	return (0);
}

void	ft_redir_short_in_single(t_token *tokens)
{
	t_token	*head;
	t_token	*tmp;

	while (tokens)
	{
		tmp = NULL;
		head = tokens;
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == REDIRECT_IN)
				if (ft_redir_short_in_single2(tokens, &tmp, head))
					break ;
			tokens = tokens->next;
		}
		tokens = head;
		tokens = ft_take_ris_out(tokens, tmp);
	}
}
