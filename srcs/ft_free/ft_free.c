/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:50:55 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/28 15:13:20 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_free.h"

void	ft_free_matrix(char **matrix)
{
	int		i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

void	ft_free_env(t_envp *env)
{
	t_envp	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

void	ft_free_tokens(t_token *tokens, int del_heredoc)
{
	t_token	*tmp;

	while (tokens)
	{
		if (del_heredoc != 0 && tokens->type == D_REDIRECT_IN
			&& tokens->next && tokens->next->content
			&& tokens->next->type == HERE_DOC
			&& tokens->next->heredoc
			&& access(tokens->next->heredoc, F_OK) == 0)
			unlink(tokens->next->heredoc);
		if (tokens->heredoc)
			free(tokens->heredoc);
		if (tokens->next)
			tmp = tokens->next;
		else
			tmp = NULL;
		if (tokens->content)
			free(tokens->content);
		if (tokens)
			free(tokens);
		tokens = tmp;
		if (!tokens)
			break ;
	}
}

void	ft_free_tree(t_bin_token *tokens, int del_heredoc)
{
	if (tokens != NULL)
	{
		if (tokens->redir_in
			&& tokens->redir_in->type == HERE_DOC
			&& tokens->redir_in->heredoc)
			unlink(tokens->redir_in->heredoc);
		if (tokens->redir_in)
			ft_free_tokens(tokens->redir_in, del_heredoc);
		if (tokens->redir_out)
			ft_free_tokens(tokens->redir_out, del_heredoc);
		if (tokens->args)
			ft_free_matrix(tokens->args);
		ft_free_tree(tokens->right, del_heredoc);
		ft_free_tree(tokens->left, del_heredoc);
		free(tokens);
	}
}

int	ft_free(int i, char *command, t_data *data, int del_heredoc)
{
	if (command)
		free(command);
	if (data)
	{
		if (data->bin_tokens)
			ft_free_tree(data->bin_tokens, del_heredoc);
		if (data->tokens_start)
			ft_free_tokens(data->tokens_start, del_heredoc);
		if (data->path)
			free(data->path);
		if (data->prompt)
			free(data->prompt);
		if (data->ft_envp)
			ft_free_env(data->ft_envp);
		if (data->hostname)
			free(data->hostname);
		if (data->heredoc_path)
			free(data->heredoc_path);
		free(data);
	}
	if (i == -1)
		return (0);
	else
		exit(i);
}
