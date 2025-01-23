/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:39:29 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/23 11:03:44 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	char	*command;
	char	*command2;
	char	**commands;
	char	*path = "/bin/clear";
	char	*idk[] = {path, "-T", "xterm-256color",NULL};

	(void) ac;
	(void) av;
	data = ft_data_init(envp);
	while (1)
	{
		command2 = readline(data->prompt);
		add_history(command2);
		command = ft_strtrim(command2, " \t\n");
		if (!command || ft_strlen(command) == 0)
			continue ;
		if (ft_syntax(command))
			continue ;
		if (ft_strncmp(command, "exit", 4) == 0)
			ft_free(0, command, data);
		commands = ft_split_cmds(command);
		if (data->tokens_start)
			ft_free_tokens(data->tokens_start);
		data->tokens_start = ft_token_maker(commands);
		data->tokens = data->tokens_start;
		ft_tokens_cat(&data);
		data->tokens = data->tokens_start;
		if (ft_syntax_tokens(data->tokens))
			continue ;
		if (data->tokens->type == CMD
			&& ft_strncmp(data->tokens->content, "clear", 5) == 0)
		{
			if (fork() == 0)
				execve(path, idk, NULL);
			else
			{
				waitpid(-1, &data->exit_status, 0);
				printf("test: %i\n", data->exit_status);
				rl_redisplay();
			}
		}
		ft_env(data);
		ft_expander(data->tokens, data);
		ft_rmv_quotes(data->tokens);
		while (data->tokens)
		{
			printf("%s. ", data->tokens->content);
			if (data->tokens->type == PIPE)
				printf("Pipe\n");
			else if (data->tokens->type == CMD)
				printf("Command\n");
			else if (data->tokens->type == ARG)
				printf("Argument\n");
			else if (data->tokens->type == REDIRECT_IN)
				printf("Redirect In\n");
			else if (data->tokens->type == D_REDIRECT_IN)
				printf("Double Redirect In\n");
			else if (data->tokens->type == REDIRECT_OUT)
				printf("Redirect Out\n");
			else if (data->tokens->type == D_REDIRECT_OUT)
				printf("Double Redirect Out\n");
			else if (data->tokens->type == FILENAME)
				printf("Filename\n");
			if (!data->tokens->next)
				break ;
			data->tokens = data->tokens->next;
		}
		ft_free_tokens(data->tokens_start);
		data->tokens_start = NULL;
		data->tokens = NULL;
		free (command);
	}
}
