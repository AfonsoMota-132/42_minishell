/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:39:29 by afogonca          #+#    #+#             */
/*   Updated: 2024/12/17 20:40:20 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_syntax(char *command)
{
	int		i;
	char	quote;

	i = -1;
	while (command[++i])
	{
		if (command[i] == '"' || command[i] == '\'')
		{
			quote = command[i++];
			while (command[i] && command[i] != quote)
				i++;
			if (command[i] != quote)
				return (printf("Syntax error\nUnclosed quotes\n"));
		}
		if (command[i] == '|' && command[i + 1] == '|')
			return (printf("Syntax error\nToo many pipes\n"));
		if ((command[i] == '<' && command[i + 1] == '<'
			&& command[i + 2] == '<')
			|| (command[i] == '>' && command[i + 1] == '>'
			&& command[i + 2] == '>'))
			return (printf("Syntax error\nToo many redirects\n"));
		if (command[i] == '\\' || command[i] == ';'
			|| (command[i] == '&' && command[i + 1] == '&'))
			return (printf("Syntax error\nUnrecognized intachter(s)\n"));
	}
	return (0);
}


t_data	*ft_data_init(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->tokens = NULL;
	data->tokens_start = NULL;
	return (data);
}

int	main(void)
{
	t_data	*data;
	char	*command;
	char	**commands;
	int		i;
	pid_t	pid;

	data = ft_data_init();
	printf("test\n");
	while (1)
	{
		command = readline("Minishell: ");
		i = 0;
		if (ft_syntax(command))
			continue ;
		if (ft_strncmp(command, "exit", 4) == 0)
			ft_free(0, command, data);
		if (ft_strncmp(command, "clear", 5) == 0)
		{
			printf("test1\n");
			/*printf("pid: %d\n", pid);*/
			pid = fork();
			if (pid == 0)
			{
				system("clear");
				exit(0);
			}
			else
				waitpid(-1, NULL, 0);
		}
		else
			printf("test2\n");
		commands = ft_split_cmds(command);
		if (data->tokens_start)
			ft_free_tokens(data->tokens_start);
		data->tokens_start = ft_token_maker(commands);
		data->tokens = data->tokens_start;
		ft_tokens_cat(&data);
		data->tokens = data->tokens_start;
		while (data->tokens)
		{
			printf("%s	", data->tokens->content);
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
			if (!data->tokens->next)
				break ;
			data->tokens = data->tokens->next;
		}
		/*while (commands[i])*/
		/*{*/
		/*	ft_printf("%s..	%d\n", commands[i], i);*/
		/*	i++;*/
		/*}*/
		free (command);
	}
}
