/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:39:29 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/29 10:43:34 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_print_tokens(t_token *tokens, t_data *data)
{
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
	(void) tokens;
}


int	signal_idk;

char	**ft_command_init(t_data *data)
{
	char	*command_in;
	char	*command;
	char	**command_list;

	command_in = readline(data->prompt);
	if (!command_in)
		ft_free(130, NULL,data);
	add_history(command_in);
	command = ft_strtrim(command_in, " \t\n");
	if (!command || !ft_strlen(command)
		|| ft_syntax(command))
	{
		if (command)
			free (command);
		return (NULL);
	}
	if (ft_strncmp(command, "exit", 4) == 0)
		ft_free(0, command, data);
	command_list = ft_split_cmds(command);
	free(command);
	return (command_list);
}
int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	char	**commands;

	(void) ac;
	(void) av;
	data = ft_data_init(envp);
	ft_signals();
	while (1)
	{
		commands = ft_command_init(data);
		if (!commands)
			continue ;
		if (data->tokens_start)
			ft_free_tokens(data->tokens_start);
		data->tokens_start = ft_token_maker(commands);
		data->tokens = data->tokens_start;
		ft_tokens_cat(&data);
		ft_expander(data->tokens, data);
		ft_rmv_quotes(data->tokens);
		if (ft_syntax_tokens(data->tokens) || ft_redirects(data->tokens, &data))
			continue ;
		ft_echo(data->tokens);
		ft_print_tokens(data->tokens, data);
	}
}
