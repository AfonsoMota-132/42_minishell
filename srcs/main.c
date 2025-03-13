/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:39:29 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/05 19:56:51 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_signal_received = 0;

char	**ft_command_init(t_data *data)
{
	char	*command_in;
	char	*command;
	char	**command_list;

	ft_prompt_init(data);
	command_in = readline(data->prompt);
	if (!command_in)
		ft_free(data->exit_status, NULL, data, 1);
	command = ft_strtrim(command_in, " \t\n");
	if (!command || !ft_strlen(command))
	{
		if (command && ft_strlen(command))
			data->exit_status = 2;
		if (command)
			free (command);
		return (NULL);
	}
	add_history(command_in);
	command_list = ft_split_cmds(command);
	free(command);
	free(command_in);
	return (command_list);
}

int	ft_loop2(t_data *data)
{
	if (ft_wildcards(data) || ft_redirects(data->tokens, &data))
	{
		data->exit_status = 2;
		if (!data->tokens_start)
			return (1);
	}
	else
	{
		if (data->bin_tokens)
			ft_free_tree(data->bin_tokens, 1);
		data->bin_tokens = ft_bin_tokens(data);
		ft_run_cmds(data);
		ft_signals();
		dup2(1, STDOUT_FILENO);
		dup2(0, STDIN_FILENO);
	}
	return (0);
}

void	ft_loop3(t_data *data, int run)
{
	t_token_type	type_tmp;

	ft_take_out_par(&data->tokens, run);
	data->tokens_start = data->tokens;
	while (1)
	{
		if (data->tokens->type == IN_PAR && !run)
		{
			run = ft_skip_par(&data->tokens, data);
			data->tokens_start = data->tokens;
			if (run == -1 || !data->tokens)
				break ;
		}
		type_tmp = ft_return_con_type(data->tokens);
		data->tokens_end = ft_tokens_end(type_tmp, data);
		if (run == 1)
			if (ft_loop2(data))
				continue ;
		if (type_tmp == NON)
			break ;
		run = ft_get_run(data, type_tmp);
		ft_take_out_par(&data->tokens_end, run);
		ft_free_loop3(data);
	}
}

void	ft_loop(t_data *data)
{
	char			**commands;

	while (1)
	{
		commands = ft_command_init(data);
		if (g_signal_received)
		{
			data->exit_status = g_signal_received;
			g_signal_received = 0;
		}
		if (!commands)
			continue ;
		if (ft_token_start(commands, data))
			continue ;
		data->tokens_start = data->tokens;
		if (ft_syntax_con(data->tokens) || ft_syntax_par(data->tokens)
			|| ft_syntax_tokens(data->tokens))
		{
			data->exit_status = 2;
			continue ;
		}
		ft_loop3(data, 1);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void) ac;
	(void) av;
	data = ft_data_init(envp);
	ft_signals();
	ft_loop(data);
}
