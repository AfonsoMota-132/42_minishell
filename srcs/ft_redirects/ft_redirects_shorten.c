/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects_shorten.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:21:33 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/29 10:22:24 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"


void	ft_free_token(t_token *tokens)
{
	t_token	*tmp;
	
	tmp = tokens->next;
	free(tokens->content);
	free(tokens);
	free(tmp->content);
	free(tmp);
}

void	ft_take_last_redir_out(t_token *tokens)
{
	t_token	*head;
	t_token *tmp;
	t_token *tmp2;

	while (tokens)
	{
		head = tokens;
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == REDIRECT_OUT
				|| tokens->type == D_REDIRECT_OUT)
				tmp = tokens;
			tokens = tokens->next;
		}
		tokens = head;
		while (tokens && tokens->type != PIPE)
		{
		if (tokens->next && (tokens->next->type == REDIRECT_OUT
		|| tokens->next->type == D_REDIRECT_OUT)
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
	}
}

void	ft_take_last_redir_in(t_token *tokens)
{
	t_token	*head;
	t_token *tmp;
	t_token *tmp2;

	while (tokens)
	{
		head = tokens;
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == REDIRECT_IN
				|| tokens->type == D_REDIRECT_IN)
				tmp = tokens;
			tokens = tokens->next;
		}
		tokens = head;
		while (tokens && tokens->type != PIPE)
		{
		if (tokens->next && (tokens->next->type == REDIRECT_IN
		|| tokens->next->type == D_REDIRECT_IN)
		&& tokens->next->next && tokens->next != tmp)
		{
			tmp2 = tokens->next;
			tokens->next = tokens->next->next->next;
			ft_free_token(tmp2);
		}
		else
			tokens = tokens->next;
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
		}
	}
}	
