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

t_token	*ft_take_ro_out(t_token *head, t_token *tokens)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = head;
	while (tmp && tmp->type != PIPE)
	{
		tmp2 = tmp->next;
		if (tmp->next && (tmp->next->type == D_REDIRECT_OUT
		|| tmp->next->type == REDIRECT_OUT) && tmp->next->next 
			&& tmp->next != tokens && tmp->next->next->next)
		{
			tmp->next = tmp->next->next->next;
			ft_free_token(tmp2);
		}
		else if (tmp->next && (tmp->next->type == D_REDIRECT_OUT
		|| tmp->next->type == REDIRECT_OUT) && tmp->next->next 
			&& tmp->next != tokens)
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

void	ft_redir_short_out(t_token *tokens)
{
	t_token	*head;
	t_token	*tmp;
	int		i;

	i = 0;
	while (tokens)
	{
		tmp = NULL;
		head = tokens;
		while (tokens && tokens->type != PIPE)
		{
			if ((tokens->type == D_REDIRECT_OUT || tokens->type == REDIRECT_OUT))
			{
				i++;
				if (access(tokens ->next->content, W_OK) == -1)
				{
					tmp = ft_take_ro_out(tokens, tmp);
					break ;
				}
				if (tokens->type == D_REDIRECT_OUT || tokens->type == REDIRECT_OUT)
					tmp = tokens;
			}
			tokens = tokens->next;
		}
		if (tmp)
		{
			tokens = head;
			tokens = ft_take_ros_out(tokens, tmp);
			tokens = ft_take_rod_out(tokens, tmp);
		}
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
