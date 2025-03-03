/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:36:33 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:10:55 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bin_tokens.h"

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

int	ft_bin_count_args(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->content || i == 0)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

int	ft_first_redir(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == REDIRECT_IN
			|| tokens->type == D_REDIRECT_IN)
			return (1);
		else if (tokens->type == REDIRECT_OUT
			|| tokens->type == D_REDIRECT_OUT)
			return (0);
		tokens = tokens->next;
	}
	return (0);
}

t_bin_token	*ft_bin_tokens(t_data *data)
{
	t_bin_token	*start;
	int			pipe_count;

	pipe_count = ft_has_pipes(data);
	if (pipe_count == 0)
	{
		start = ft_calloc_bin_token(CMD_NODE);
		ft_update_bin_token(start, data->tokens_start);
	}
	else
		start = ft_bin_multi_pipe(data, pipe_count);
	data->tokens = NULL;
	data->tokens_start = NULL;
	return (start);
}
