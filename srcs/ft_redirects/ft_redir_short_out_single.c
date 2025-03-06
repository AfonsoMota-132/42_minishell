/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_short_out_single.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:41:21 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:35:05 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_redirects.h"

t_token	*ft_rmv_ros_before(t_token *tokens, t_token *head)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = head;
	while (tmp && tmp->type != PIPE)
	{
		tmp2 = tmp->next;
		if (tmp->next && (tmp->next->type == REDIRECT_OUT)
			&& tmp->next->next && tmp->next != tokens
			&& tmp->next->next->next)
		{
			tmp->next = tmp->next->next->next;
			ft_free_token(tmp2);
		}
		else if (tmp->next && (tmp->next->type == REDIRECT_OUT)
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

t_token	*ft_skip_to_pipe(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	return (tokens);
}

t_token	*ft_take_ros_out(t_token *tokens, t_token *tmp)
{
	t_token	*tmp2;

	if (!tmp)
		tokens = ft_skip_to_pipe(tokens);
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->next && (tokens->next->type == REDIRECT_OUT)
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

int	ft_redir_short_out_single2(t_token *tokens, t_token **tmp, t_token *head)
{
	if (((tokens->next->content[0] == '$'
				|| ft_strchr(tokens->next->content, '*'))
			&& tokens->next->quotes == 0)
		|| (open(tokens->next->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0644) == -1
			&& (access(tokens->next->content, W_OK) == -1)))
	{
		(*tmp) = ft_rmv_ros_before(tokens, head);
		return (1);
	}
	(*tmp) = tokens;
	return (0);
}

void	ft_redir_short_out_single(t_token *tokens)
{
	t_token	*head;
	t_token	*tmp;

	while (tokens)
	{
		tmp = NULL;
		head = tokens;
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == REDIRECT_OUT)
				if (ft_redir_short_out_single2(tokens, &tmp, head))
					break ;
			tokens = tokens->next;
		}
		tokens = head;
		tokens = ft_take_ros_out(tokens, tmp);
	}
}
