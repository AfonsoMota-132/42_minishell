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

	(void) ac;
	(void) av;
	command = NULL;
	data = ft_data_init(envp);
	while (1)
	{
		command2 = readline(data->prompt);
		add_history(command2);
		if (command)
			free(command);
		command = ft_strtrim(command2, " \t\n");
		if (!command || !ft_strlen(command)
			|| ft_syntax(command))
			continue ;
		if (ft_strncmp(command, "exit", 4) == 0)
			ft_free(0, command, data);
		commands = ft_split_cmds(command);
		if (data->tokens_start)
			ft_free_tokens(data->tokens_start);
		data->tokens_start = ft_token_maker(commands);
		data->tokens = data->tokens_start;
		ft_tokens_cat(&data);
		ft_env(data);
		ft_expander(data->tokens, data);
		ft_rmv_quotes(data->tokens);
		ft_tokens_cat(&data);
		if (ft_syntax_tokens(data->tokens))
			continue ;
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
			else if (data->tokens->type == HERE_DOC)
				printf("Here Doc\n");
			if (!data->tokens->next)
				break ;
			data->tokens = data->tokens->next;
		}
	}
}
