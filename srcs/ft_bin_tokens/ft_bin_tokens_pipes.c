/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_tokens_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:10:18 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:11:17 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bin_tokens.h"

t_bin_token	*ft_initialize_all_pipes(int pipe_count)
{
	t_bin_token	*start;
	t_bin_token	*tmp;

	start = ft_calloc_bin_token(PIPE_NODE);
	tmp = start;
	while (--pipe_count)
	{
		tmp->left = ft_calloc_bin_token(PIPE_NODE);
		tmp->right = ft_calloc_bin_token(CMD_NODE);
		tmp = tmp->left;
	}
	tmp->left = ft_calloc_bin_token(CMD_NODE);
	tmp->right = ft_calloc_bin_token(CMD_NODE);
	return (start);
}

t_token	*ft_take_last_pipe(t_token *tokens)
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

t_bin_token	*ft_bin_multi_pipe(t_data *data, int pipe_count)
{
	t_bin_token	*start;
	t_bin_token	*tmp;
	t_token		*tmp2;

	start = ft_initialize_all_pipes(pipe_count);
	tmp = start;
	while (pipe_count != 1)
	{
		tmp2 = ft_take_last_pipe(data->tokens_start);
		ft_update_bin_token(tmp->right, tmp2);
		tmp = tmp->left;
		pipe_count--;
	}
	tmp2 = ft_take_last_pipe(data->tokens_start);
	ft_update_bin_token(tmp->right, tmp2);
	ft_update_bin_token(tmp->left, data->tokens_start);
	data->tokens = NULL;
	data->tokens_start = NULL;
	return (start);
}
