/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:40:09 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/06 10:39:03 by afogonca         ###   ########.fr       */
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
	return (tokens);
}

t_token	*ft_put_cmd_first(t_token *tokens)
{
	t_token	*head;

	head = ft_pcmdf_first(tokens);
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

int	ft_redirects(t_token *tokens, t_data **data)
{
	tokens = ft_put_cmd_first(tokens);
	ft_redir_short_out_single(tokens);
	ft_redir_short_out_double(tokens);
	ft_redir_short_out(tokens);
	ft_redir_short_in_single(tokens);
	ft_heredoc(tokens, *data);
	(*data)->tokens_start = tokens;
	(*data)->tokens = tokens;
	return (0);
}
