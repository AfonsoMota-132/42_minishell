/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:36:33 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/21 15:00:46 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_has_pipes(t_data *data)
{
	int	count;

	data->tokens = data->tokens_start;
	count = 0;
	while (data->tokens)
	{
		if (data->tokens->type == PIPE)
			count++;
		data->tokens = data->tokens->next;
	}
	return (count);
}

t_bin_token	*ft_calloc_bin_token(t_bin_token_type type)
{
	t_bin_token	*new;

	new = malloc(sizeof(t_bin_token));
	new->tokens = NULL;
	new->right = NULL;
	new->left = NULL;
	new->type = type;
	return (new);
}


t_bin_token	*ft_initialize_all_pipes(int pipe_count)
{
	t_bin_token	*start;
	t_bin_token	*tmp;

	start = ft_calloc_bin_token(PIPE_NODE);
	tmp = start;
	while(--pipe_count)
	{
		tmp->left = ft_calloc_bin_token(PIPE_NODE);
		tmp->right = ft_calloc_bin_token(CMD_NODE);
		tmp = tmp->left;
	}
	tmp->left = ft_calloc_bin_token(CMD_NODE);
	tmp->right = ft_calloc_bin_token(CMD_NODE);
	return (start);
}

t_token		*ft_take_last_pipe(t_token *tokens)
{
	t_token	*tmp;
	t_token	*ret;

	tmp = NULL;
	while (tokens)
	{
		if (tokens->next && tokens->next->type == PIPE)
			tmp = tokens;
		tokens = tokens->next;
	}
	ret = tmp->next;
	if (tmp)
		tmp->next = NULL;
	tmp = ret->next;
	free(ret->content);
	free(ret);
	return (tmp);
}

t_bin_token	*ft_bin_tokens(t_data *data)
{
	t_bin_token	*start;
	t_bin_token	*tmp;
	int			pipe_count;

	pipe_count = ft_has_pipes(data);
	if (pipe_count == 0)
	{
		start = ft_calloc_bin_token(CMD_NODE);
		start->tokens = data->tokens_start;
	}
	else
	{
		start = ft_initialize_all_pipes(pipe_count);
		tmp = start;
		while (pipe_count != 1)
		{
			tmp->right->tokens = ft_take_last_pipe(data->tokens_start);
			tmp = tmp->left;
			pipe_count--;
		}
		tmp->right->tokens = ft_take_last_pipe(data->tokens_start);
		tmp->left->tokens = data->tokens_start;
		data->tokens = NULL;
		data->tokens_start = NULL;
	}
	data->tokens = NULL;
	data->tokens_start = NULL;
	return (start);
}
