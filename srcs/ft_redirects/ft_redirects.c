/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:40:09 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:35:11 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_redirects.h"

void	ft_free_token(t_token *tokens)
{
	t_token	*tmp;	

	tmp = tokens->next;
	free(tokens->content);
	free(tokens);
	free(tmp->content);
	free(tmp);
}

t_token	*ft_pcmdf_first(t_token *tokens)
{
	t_token	*prev;
	t_token	*head;

	prev = NULL;
	head = tokens;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == CMD && prev)
		{
			prev->next = tokens->next;
			tokens->next = head;
			break ;
		}
		else if (tokens->type == CMD)
			break ;
		else
			prev = tokens;
		tokens = tokens->next;
	}
	if (!tokens)
		return (head);
	return (tokens);
}

t_token	*ft_put_cmd_first(t_token *tokens)
{
	t_token	*head;

	head = ft_pcmdf_first(tokens);
	if (!head)
		return (tokens);
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	while (tokens)
	{
		if (tokens && tokens->type == PIPE)
		{
			tokens->next = ft_pcmdf_first(tokens->next);
			tokens = tokens->next;
		}
		else
			tokens = tokens->next;
	}
	return (head);
}

int	ft_only_one_redir(t_token *tokens, t_token_type redir)
{
	int	count;

	while (tokens)
	{
		count = 0;
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == redir && count == 0)
				count++;
			else if (tokens->type == redir && count > 0)
				return (1);
			tokens = tokens->next;
		}
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (0);
}

int	ft_only_one_redir_shor(t_token *tokens)
{
	int	s_redir;
	int	d_redir;

	while (tokens)
	{
		s_redir = 0;
		d_redir = 0;
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->type == D_REDIRECT_IN && s_redir == 0)
				d_redir++;
			else if (tokens->type == D_REDIRECT_IN && s_redir > 0)
				return (1);
			if (tokens->type == REDIRECT_IN && d_redir == 0)
				s_redir++;
			else if (tokens->type == REDIRECT_IN && d_redir > 0)
				return (1);
			tokens = tokens->next;
		}
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (0);
}

int	ft_redirects(t_token *tokens, t_data **data)
{
	tokens = ft_put_cmd_first(tokens);
	ft_redir_short_out_single(tokens);
	while (ft_only_one_redir(tokens, REDIRECT_OUT))
		ft_redir_short_out_single(tokens);
	ft_redir_short_out_double(tokens);
	while (ft_only_one_redir(tokens, D_REDIRECT_OUT))
		ft_redir_short_out_double(tokens);
	ft_redir_short_out(tokens);
	while (ft_only_one_redir(tokens, REDIRECT_IN))
		ft_redir_short_in_single(tokens);
	if (ft_heredoc(tokens, *data) == 130)
		return (1);
	(*data)->tokens_start = tokens;
	(*data)->tokens = tokens;
	return (0);
}
