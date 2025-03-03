/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_short_out_double.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:41:48 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:34:57 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_redirects.h"

t_token	*ft_rmv_rod_before(t_token *tokens, t_token *head)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = head;
	while (tmp && tmp->type != PIPE)
	{
		tmp2 = tmp->next;
		if (tmp->next && (tmp->next->type == D_REDIRECT_OUT)
			&& tmp->next->next && tmp->next != tokens
			&& tmp->next->next->next)
		{
			tmp->next = tmp->next->next->next;
			ft_free_token(tmp2);
		}
		else if (tmp->next && (tmp->next->type == D_REDIRECT_OUT)
			&& tmp->next->next && tmp->next != tokens)
		{
			tmp->next = NULL;
			ft_free_token(tmp2);
		}
		else
			tmp = tmp->next;
	}
	tokens = head;
	return (NULL);
}

t_token	*ft_take_rod_out(t_token *tokens, t_token *tmp)
{
	t_token	*tmp2;

	if (!tmp)
		tokens = ft_skip_to_pipe(tokens);
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->next && (tokens->next->type == D_REDIRECT_OUT)
			&& tokens->next->next && (tokens->next != tmp))
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

int	ft_redir_short_out_double2(t_token *tokens, t_token **tmp, t_token *head)
{
	if ((tokens->next->content[0] == '$' && tokens->next->quotes == 0)
		|| (open(tokens->next->content, O_WRONLY | O_CREAT, 0644) == -1
			&& access(tokens->next->content, W_OK) == -1))
	{
		(*tmp) = ft_rmv_rod_before(tokens, head);
		return (1);
	}
	(*tmp) = tokens;
	return (0);
}

void	ft_redir_short_out_double(t_token *tokens)
{
	t_token	*head;
	t_token	*tmp;

	while (tokens)
	{
		tmp = NULL;
		head = tokens;
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == D_REDIRECT_OUT)
				if (ft_redir_short_out_double2(tokens, &tmp, head))
					break ;
			tokens = tokens->next;
		}
		tokens = head;
		tokens = ft_take_rod_out(tokens, tmp);
	}
}
