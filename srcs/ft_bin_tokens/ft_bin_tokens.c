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
	new->nbr_args = 0;
	new->args = NULL;
	new->redir_in = NULL;
	new->redir_out = NULL;
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

t_token	*ft_bin_redir(t_token *tokens, t_token_type redir_1\
						, t_token_type redir_2)
{
	t_token	*tmp_token;
	t_token	*tmp;

	while (tokens)
	{
		tmp_token = tokens->next;
		if (tokens && tokens->next &&
			(tokens->next->type == redir_1
			|| tokens->next->type == redir_2))
			break ;
		tokens = tokens->next;
	}
	if (!tokens)
		return (NULL);
	tokens->next = tokens->next->next->next;
	tmp_token->next->next = NULL;
	tmp = tmp_token->next;
	free(tmp_token->content);
	free(tmp_token);
	return (tmp);
}

int			ft_bin_count_args(t_token *tokens)
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

int			ft_first_redir(t_token *tokens)
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

void		ft_update_bin_token(t_bin_token	*bin_token, t_token *tokens)
{
	t_token	*tmp;
	int	arg_len;
	int	i;

	bin_token->first_redir = ft_first_redir(tokens);
	bin_token->redir_in = ft_bin_redir(tokens, REDIRECT_IN, D_REDIRECT_IN);
	bin_token->redir_out = ft_bin_redir(tokens, REDIRECT_OUT, D_REDIRECT_OUT);
	arg_len = ft_bin_count_args(tokens);
	bin_token->nbr_args = arg_len;
	bin_token->args = ft_calloc(sizeof(char *), arg_len + 1);
	i = 0;
	while (i < arg_len && tokens)
	{
		tmp = tokens->next;
		if (tokens->content)
			bin_token->args[i++] = ft_strdup(tokens->content);
		free(tokens->content);
		free(tokens);
		if (!tmp)
			break ;
		tokens = tmp;
	}
}

t_bin_token		*ft_bin_multi_pipe(t_data *data, int pipe_count)
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
