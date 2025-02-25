/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 05:56:27 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/24 05:58:17 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_run_cmds(t_data *data)
{
	int	status;
	int	child_pid;
	int	fd[2];

	if (!data->bin_tokens->right && !data->bin_tokens->left)
	{
		if (pipe(fd) == -1)
			printf("error creating pipe\n");
		else
		{
			child_pid = fork();
			if (child_pid == 0)
				ft_execve(data->bin_tokens, data);
			waitpid(-1, &status, 0);
			data->exit_status = WEXITSTATUS(status);
			close(fd[0]);
			close(fd[1]);
		}
	}
	else
		ft_create_pipe(data->bin_tokens, data);
}

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

void	ft_error_exit(t_data * data, char *path);

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

void	ft_error_msg_redir(t_data *data, int type, char *redir, char *path)
{
	if (path)
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
	if (tokens->redir_in)
	{
		if (access(tokens->redir_in->content, F_OK) == -1)	
			ft_error_msg_redir(data, 1, tokens->redir_in->content, path);
		if (access(tokens->redir_in->content, R_OK) == -1)
			ft_error_msg_redir(data, 0, tokens->redir_in->content, path);
		fd = open(tokens->redir_in->content, O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
	}
}

void	ft_execve(t_bin_token *tokens, t_data *data)
{
	int		ex_code;
	char	*path;
	int		i;

	i = 0;
	ex_code = 0;
	while(!tokens->args[i] && i < tokens->nbr_args)
		i++;
	if (!tokens->args[i])
		ft_free(1, NULL, data, 0);
	path = ft_execve_get_path(tokens->args[i], data);
	if (!path && tokens->args[0])
		path = ft_strdup(tokens->args[0]);
	if (path && access(path, F_OK) != 0)
		ft_command_not_found(data, tokens, path);
	ft_handle_redirects(data, tokens, path);
	if (path)
	{
		ex_code= execve(path, tokens->args, NULL);
		if (ex_code == -1)
			ft_command_not_found(data, tokens, path);
	}
	if (path)
		free(path);
}
