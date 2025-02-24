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
#include <fcntl.h>

char	*ft_execve_get_path(char *cmd, t_data *data)
{
	int	i;
	char	*value;
	char	**paths;
	char	*tmp;

	value = ft_getenv("PATH", data);
	if (!value)
		return (NULL);
	paths = ft_split(value, ':');
	i = -1;
	while (ft_strlen(cmd) && paths[++i])
	{
		paths[i] = ft_strjoin_gnl(paths[i], "/");
		paths[i] = ft_strjoin_gnl(paths[i], cmd);
		if (access(paths[i], F_OK) != -1)
		{
			tmp = ft_strdup(paths[i]);
			ft_free_matrix(paths);
			return (tmp);
		}
	}
	ft_free_matrix(paths);
	return (NULL);
}

void	ft_error_msg_redir(t_data *data, int type, char *redir, char *path)
{
	free(path);
	if (type == 0)
		printf("bash: %s: permission denied\n", redir);
	else if (type == 1)
		printf("bash: %s: No such file or directory\n", redir);
	ft_free(1, NULL, data, 0);
}

void	ft_handle_redirects(t_data *data, t_bin_token *tokens, char *path)
{
	int		fd;

	if (tokens->redir_out)
	{
		if (access(tokens->redir_out->content, F_OK | W_OK) == -1)
			ft_error_msg_redir(data, 0, tokens->redir_out->content, path);
		fd = open(tokens->redir_out->content, O_WRONLY | O_APPEND, 0);
		dup2(fd, STDOUT_FILENO);
	}
	if (tokens->redir_in && tokens->redir_in->type == FILENAME)
	{
		if (access(tokens->redir_in->content, F_OK) == -1)	
			ft_error_msg_redir(data, 1, tokens->redir_in->content, path);
		if (access(tokens->redir_in->content, R_OK) == -1)
			ft_error_msg_redir(data, 0, tokens->redir_in->content, path);
		fd = open(tokens->redir_in->content, O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
	}
	else if (tokens->redir_in && tokens->redir_in->type == HERE_DOC)
	{
		if (access(tokens->redir_in->heredoc, F_OK) == -1)	
			ft_error_msg_redir(data, 1, tokens->redir_in->heredoc, path);
		if (access(tokens->redir_in->heredoc, R_OK) == -1)
			ft_error_msg_redir(data, 0, tokens->redir_in->heredoc, path);
		fd = open(tokens->redir_in->heredoc, O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
	}
}

void	ft_command_not_found(t_data *data, t_bin_token *tokens, char *path)
{
	if (ft_strlen(path) == 0)
		printf("\'\' : command not found\n");
	else
		printf("%s: command not found\n", path);
	free(path);
	ft_free(127, NULL, data, 1);
	(void) tokens;
}

void	ft_execve(t_data *data, t_bin_token *tokens)
{
	char	*path;
	int		result;

	path = ft_execve_get_path(tokens->args[0], data);
	if (!path && tokens->args[0])
		path = ft_strdup(tokens->args[0]);
	if (path && access(path, F_OK) == -1)
		ft_command_not_found(data, tokens, path);
	if (path)
	{
		ft_handle_redirects(data, tokens, path);
		free(tokens->args[0]);
		tokens->args[0] = ft_strdup(path);
		result = execve(path, tokens->args, NULL);
		if (result == -1)
		{
			printf("%s: command not found\n", tokens->args[0]);
			free(path);
			exit (127);
		}
	}
	if (path)
		free(path);
}

void	ft_pipe_child(t_data *data, t_bin_token *tokens, int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_execve(data, tokens);
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
		ft_free(0, NULL, data, 0);
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

	if (pipe(fd) == -1)
		printf("error creating pipe\n");
	else
	{
		if (tokens->type == PIPE_NODE)
			ft_handle_pipe(data, tokens, fd);
		else
			ft_execve(data, tokens);
	}
	waitpid(-1 , &exit_status, 0);
	data->exit_status = WEXITSTATUS(exit_status);
	close(fd[0]);
	close(fd[1]);
}
