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

void	ft_free_tokens(t_token *tokens)
{
	t_token	*tmp;
	
	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = tmp;
		if (!tokens)
			break ;
	}
}

int	ft_free(int i, char *command, t_data *data)
{
	if (command)
		free(command);
	if (data)
	{
		if (data->tokens_start)
			ft_free_tokens(data->tokens_start);
		if (data->path)
			free(data->path);
		if (data->prompt)
			free(data->prompt);
		if (data->ft_envp)
			ft_free_env(data->ft_envp);
		if (data->hostname)
			free(data->hostname);
		free(data);
	}
	exit(i);
}
