/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:40:09 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/29 10:44:18 by afogonca         ###   ########.fr       */
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

t_token *ft_pcmdf_first(t_token *tokens)
{
	t_token *prev;
	t_token	*head;

	prev = NULL;
	head = tokens;
	printf("tokens->content: %s\n", tokens->content);
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

t_token *ft_put_cmd_first(t_token *tokens)
{
	t_token *head;

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

t_token	*ft_take_ro_out(t_token *head, t_token *tokens, int	i)
{
	t_token	*tmp;

	if (i == -1)
		return (tokens);
	tokens = head;
	while (tokens && tokens->type != PIPE)
	{
		tmp = tokens->next;
		if (tokens->next && (tokens->next->type == D_REDIRECT_OUT
			|| tokens->next->type == REDIRECT_OUT) && tokens->next->next
			&&	i == 1)
		{
			tokens->next = tokens->next->next->next;
			ft_free_token(tmp);
			break ;
		}
		else if(tokens->next && (tokens->next->type == D_REDIRECT_OUT
			|| tokens->next->type == REDIRECT_OUT) && tokens->next->next
			&& !(--i))
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
			if ((tokens->type == D_REDIRECT_OUT || tokens->type == REDIRECT_OUT))
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

int	ft_redirects(t_token *tokens, t_data **data)
{
	tokens = ft_put_cmd_first(tokens);
	ft_redir_short_out_single(tokens);
	ft_redir_short_out_double(tokens);
	ft_redir_short_out(tokens);
	(*data)->tokens_start = tokens;
	(*data)->tokens = tokens;
	return (0);
}
