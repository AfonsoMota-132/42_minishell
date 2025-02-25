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
			ft_putstr_fd("Bash: Failed creating pipe.\n", 1);
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
	int		i;
	char	**paths;
	char	*tmp;

	tmp = ft_getenv("PATH", data);
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
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

void	ft_execve(t_bin_token *tokens, t_data *data)
{
	int		ex_code;
	char	*path;
	int		i;

	i = 0;
	ex_code = 0;
	while (!tokens->args[i] && i < tokens->nbr_args)
		i++;
	if (!tokens->args[i])
		ft_free(1, NULL, data, 0);
	path = ft_execve_get_path(tokens->args[i], data);
	if (!path && tokens->args[0])
		path = ft_strdup(tokens->args[0]);
	if (path && access(path, F_OK) != 0)
		ft_command_not_found(data, path);
	ft_handle_redirects(data, tokens, path);
	if (path)
	{
		ex_code = execve(path, tokens->args, NULL);
		if (ex_code == -1)
			ft_command_not_found(data, path);
	}
	if (path)
		free(path);
}
