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

#include "../../incs/minishell.h"

void	ft_error_exit(t_data * data, char *exact_path)
{
	ft_putstr_fd("Bash: ", 1);
	ft_putstr_fd(exact_path, 1);
	ft_putstr_fd(" command not found\n", 1);
	ft_free(127, NULL, data, 0);
}

char	*ft_exact_path(char *cmd, char **paths_array)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!cmd)
		return (NULL);
	while (paths_array[i])
	{
		tmp = ft_strjoin(paths_array[i], cmd);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

void	ft_execution(t_bin_token *tokens, t_data *data, char **paths_array)
{
	int		result;
	char	*exact_path;

	result = 0;
	exact_path = ft_exact_path(tokens->args[0], paths_array);
	if (!exact_path && tokens->args[0])
		exact_path = ft_strdup(tokens->args[0]);
	if (exact_path && access(exact_path, F_OK) != 0)
		ft_error_exit(data, exact_path);
	if (exact_path)
	{
		result = execve(exact_path, tokens->args, NULL);
		if (result == -1)
		{
			ft_putstr_fd(exact_path, 2);
			perror(": Minishell");
			free(exact_path);
			exit(126);
		}
	}
	if (exact_path)
		free(exact_path);
}

void	ft_execve(t_bin_token *tokens, t_data *data)
{
	char	*paths_str;
	char	**paths_array;
	int		i;
	char	*tmp;

	i = 0;
	paths_array = NULL;
	paths_str = ft_getenv("PATH", data);
	if (paths_str)
	{
		paths_array = ft_split(paths_str, ':');
		while (paths_array[i])
		{
			tmp = paths_array[i];
			paths_array[i] = ft_strjoin(paths_array[i], "/");
			free(tmp);
			i++;
		}
	}
	else
		ft_error_exit(data, data->args[0]);
	ft_execution(tokens, data,paths_array);
}

void	ft_pipe_child(t_bin_token *tokens, int *fd, t_data *data)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_execve(tokens, data);
}

void	ft_pipe_parent(t_bin_token *tokens, int *fd, t_data *data)
{
	pid_t	pid;
	int		status;

	close(fd[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		ft_create_pipe(tokens->left, data);
		close(fd[1]);
		ft_free(0, NULL, data, 0);
	}
	else
		close(fd[1]);
	waitpid(pid, &status, 0);
}

void	ft_execute_node(t_bin_token *tree, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		// handle builtins
		ft_execve(tree, data);
	}
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
	data->exit_status = WIFEXITED(status);
	close(fd[0]);
	close(fd[1]);
}
