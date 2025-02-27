/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:07:23 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/24 05:57:55 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executer.h"

void	ft_pipe_child(t_bin_token *tokens, int *fd, t_data *data)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_execve(tokens, data);
}

void	ft_pipe_parent(t_bin_token *tokens, int *fd, t_data *data)
{
	pid_t	child_pid;
	int		status;

	close(fd[0]);
	child_pid = fork();
	if (child_pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		ft_create_pipe(tokens->left, data);
		close(fd[1]);
		ft_free(0, NULL, data, 0);
	}
	else
		close(fd[1]);
	waitpid(child_pid, &status, 0);
	data->exit_status = WIFEXITED(status);
}

void	ft_handle_pipe(t_bin_token *tokens, t_data *data, int fd[2])
{
	pid_t	child_pid;

	if (tokens->type == PIPE_NODE)
	{
		child_pid = fork();
		if (child_pid < 0)
			ft_putstr_fd("Bash: Failed creating fork.\n", 2);
		if (child_pid == 0)
			ft_pipe_child(tokens->right, fd, data);
		else
			ft_pipe_parent(tokens, fd, data);
	}
	else
		ft_execute_node(tokens, data);
}

void	ft_create_pipe(t_bin_token *tokens, t_data *data)
{
	int		status;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_putstr_fd("Bash: Failed creating pipe.\n", 1);
	else
		ft_handle_pipe(tokens, data, fd);
	waitpid(-1, &status, 0);
	data->exit_status = WEXITSTATUS(status);
	close(fd[0]);
	close(fd[1]);
}
