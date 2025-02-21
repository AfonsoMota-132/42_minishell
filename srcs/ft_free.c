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

#include "../incs/minishell.h"

void	ft_free_matrix(char **matrix)
{
	int		i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

void	ft_free_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}

void	ft_free_cmds(char **commands)
{
	int	i;

	i = -1;
	while (commands[++i])
		free(commands[i]);
	free(commands);
}

void	ft_free_tokens(t_token *tokens, int	del_heredoc)
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
void treeprint(t_bin_token *cur, int depth);

void ft_free_tree(t_bin_token *tokens, int del_heredoc)
{
	if (tokens != NULL)
	{
		treeprint(tokens, 0);
		printf("\n\nwtf\n\n");
		ft_free_tree(tokens->right, del_heredoc);
		if (tokens->tokens)
			ft_free_tokens(tokens->tokens, del_heredoc);
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
	exit(i);
}
