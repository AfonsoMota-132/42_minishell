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

#include "ft_executer.h"

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

void	ft_handle_builtins(t_bin_token *tokens, t_data *data, int i)
{
	if (ft_strncmp("echo", tokens->args[i], 5) == 0)
		ft_echo(data, tokens, 1);
	/*if (ft_strncmp("cd", tokens->args[i], 3) == 0))*/
	/*	ft_cd(data, tokens);*/
	/*if (ft_strncmp("exit", tokens->args[i], 5) == 0)*/
	/*	ft_exit(data, tokens);*/
	/*if (ft_strncmp("export", tokens->args[i], 7) == 0)*/
	/*	ft_export(data, tokens);*/
	/*if (ft_strncmp("unset", tokens->args[i], 6) == 0)*/
	/*	ft_unset(data, tokens);*/
	/*if (ft_strncmp("cd", tokens->args[i], 3) == 0)*/
	/*	ft_free(1, NULL, data, 0);*/
}

void	ft_execute_node(t_bin_token *tokens, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_handle_redirects(data, tokens, NULL);
		ft_handle_builtins(tokens, data, 0);
		ft_execve(tokens, data);
	}
}

char	**ft_envp_list2array(t_envp *env)
{
	char	**array;
	t_envp	*tmp;
	int		i;

	tmp = env;
	i = 0;
	if (!env)
		return (NULL);
	while (tmp && ++i)
		tmp = tmp->next;
	array = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	tmp = env;
	while (tmp)
	{
		array[i] = ft_strdup(tmp->key);
		if (tmp->value)
			array[i] = ft_strjoin_gnl(ft_strjoin_gnl(array[i]
						, "="), tmp->value);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	ft_execve(t_bin_token *tokens, t_data *data)
{
	char	*path;
	char	**envp;
	int		i;

	i = 0;
	ft_handle_redirects(data, tokens, NULL);
	while (!tokens->args[i] && i < tokens->nbr_args)
		i++;
	if (!tokens->args[i])
		ft_free(0, NULL, data, 0);
	ft_handle_builtins(tokens,data, i);
	path = ft_execve_get_path(tokens->args[i], data);
	if (!path && tokens->args[i])
		path = ft_strdup(tokens->args[i]);
	if (path)
	{
		envp = ft_envp_list2array(data->ft_envp);
		i = execve(path, tokens->args, envp);
		if (i == -1)
			ft_command_not_found(data, path, envp);
	}
	if (path)
		free(path);
}
