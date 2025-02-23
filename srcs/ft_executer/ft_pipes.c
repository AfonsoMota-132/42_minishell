/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:07:23 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/23 10:37:17 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_pipe_child(t_data *data, t_bin_token *tokens, int fd[2])
{
	char	*path;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	path = ft_strjoin("/usr/bin/", tokens->args[0]);
	tokens->args[0] = ft_strdup(path);
	execve(path, tokens->args, NULL);
	(void) data;
}

void	ft_pipe_parent(t_data *data, t_bin_token *tokens, int fd[2])
{
	pid_t	pid;
	int		status;

	close(fd[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		ft_pipes_creator(data, tokens->left);
		close(fd[1]);
		exit(0);
	}
	else
		close(fd[1]);
	waitpid(pid, &status, 0);
}

void	ft_handle_pipe(t_data *data, t_bin_token *tokens, int fd[2])
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
		printf("error creating fork!");
	if (child_pid == 0)
		ft_pipe_child(data, tokens->right, fd);
	else
		ft_pipe_parent(data, tokens, fd);

}

void	ft_pipes_creator(t_data *data, t_bin_token *tokens)
{
	int		exit_status;
	int		fd[2];
	char	*path;

	if (pipe(fd) == -1)
		printf("error creating pipe\n");
	else
	{
		if (tokens->type == PIPE_NODE)
			ft_handle_pipe(data, tokens, fd);
		else
		{
			path = ft_strjoin("/usr/bin/", tokens->args[0]);
			tokens->args[0] = ft_strdup(path);
			execve("/usr/bin", tokens->args, NULL);
		}
	}
	waitpid(-1 , &exit_status, 0);
	data->exit_status = WEXITSTATUS(exit_status);
	close(fd[0]);
	close(fd[1]);
}
