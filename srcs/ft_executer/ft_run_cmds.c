/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 05:56:27 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/06 10:31:48 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executer.h"

extern int	g_signal_received;

void	ft_run_cmds(t_data *data)
{
	if (!data->bin_tokens->right && !data->bin_tokens->left)
	{
		if (ft_run_single_builtins(data->bin_tokens, data)
			|| ft_run_single_builtins2(data->bin_tokens, data)
			|| ft_run_single_builtins3(data->bin_tokens, data))
			return ;
		ft_create_pipe(data->bin_tokens, data);
		return ;
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		ft_create_pipe(data->bin_tokens, data);
		signal(SIGINT, SIG_DFL);
	}
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

void	ft_signals_handler_exec(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = sig;
		close(STDIN_FILENO);
	}
}

void	ft_execve2(t_bin_token *tokens, t_data *data, char *path, int i)
{
	char	**envp;

	if (path)
	{
		signal(SIGINT, &ft_signals_handler_exec);
		signal(SIGQUIT, SIG_DFL);
		envp = ft_envp_list2array(data->envp);
		if (ft_getenv("PATH", data) && !ft_strchr(path, '/'))
			i = -1;
		else
			i = execve(path, tokens->args, envp);
		if (i == -1)
			ft_command_not_found(data, path, envp);
		ft_free(0, NULL, data, 0);
	}
}

void	ft_execve(t_bin_token *tokens, t_data *data)
{
	char	*path;
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
	ft_execve2(tokens, data, path, i);
	if (path)
		free(path);
}
