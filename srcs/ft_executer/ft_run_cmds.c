/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 05:56:27 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/28 11:40:26 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executer.h"

int	ft_run_single_builtins(t_bin_token *tokens, t_data *data)
{
	if (!tokens->args[0])
		return (0);
	if (ft_strcmp("exit", tokens->args[0]) == 0)
	{
		data->exit_status = ft_exit(data, tokens, 0);
		return (1);
	}
	return (0);
}

void	ft_run_cmds(t_data *data)
{
	if (!data->bin_tokens->right && !data->bin_tokens->left)
	{
		if (ft_run_single_builtins(data->bin_tokens, data))
			return ;
		ft_create_pipe(data->bin_tokens, data);
		return ;
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

int	ft_handle_builtins(t_bin_token *tokens, t_data *data, int i, int exit)
{
	int	status;

	status = 0;
	if (!tokens->args[i])
		return (status);
	if (ft_strcmp("echo", tokens->args[0]) == 0)
		status = ft_echo(data, tokens, exit);
	if (ft_strcmp("pwd", tokens->args[0]) == 0)
		status = ft_pwd(data, tokens, exit);
	if (ft_strcmp("exit", tokens->args[0]) == 0)
		status = ft_exit(data, tokens, exit);
	return (status);
}

void	ft_execute_node(t_bin_token *tokens, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_handle_redirects(data, tokens, NULL);
		ft_handle_builtins(tokens, data, 0, 1);
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
			array[i] = ft_strjoin_gnl(ft_strjoin_gnl(array[i],
						"="), tmp->value);
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
	ft_handle_builtins(tokens, data, i, 1);
	path = ft_execve_get_path(tokens->args[i], data);
	if (!path && tokens->args[i])
		path = ft_strdup(tokens->args[i]);
	if (path)
	{
		envp = ft_envp_list2array(data->envp);
		printf("path: %s\n", path);
		i = execve(path, tokens->args, envp);
		if (i == -1)
			ft_command_not_found(data, path, envp);
	}
	if (path)
		free(path);
}
