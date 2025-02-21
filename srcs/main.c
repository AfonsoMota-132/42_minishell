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

void	ft_print_tokens(t_token *tokens, t_data *data, int	tab)
{
	while (tokens)
	{
		for (int i = 0; i < tab; i++)
			printf("\t");
		printf("%s. ", tokens->content);
		if (tokens->type == PIPE)
			printf("Pipe");
		else if (tokens->type == CMD)
			printf("Command");
		else if (tokens->type == ARG)
			printf("Argument");
		else if (tokens->type == REDIRECT_IN)
			printf("Redirect In");
		else if (tokens->type == D_REDIRECT_IN)
			printf("Double Redirect In");
		else if (tokens->type == REDIRECT_OUT)
			printf("Redirect Out");
		else if (tokens->type == D_REDIRECT_OUT)
			printf("Double Redirect Out");
		else if (tokens->type == FILENAME)
			printf("Filename");
		else if (tokens->type == HERE_DOC)
			printf("Here Doc");
		if (tokens->heredoc)
			printf("\thmmm\t%s\n",tokens->heredoc);
		else
			printf("\n");
		if (!tokens->next)
			break ;
		tokens = tokens->next;
	}
	(void) data;
}


int	signal_idk;

char	**ft_command_init(t_data *data)
{
	char	*command_in;
	char	*command;
	char	**command_list;

	command_in = readline(data->prompt);
	if (!command_in)
		ft_free(130, NULL,data, 1);
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
		ft_free(0, command, data, 1);
	command_list = ft_split_cmds(command);
	free(command);
	return (command_list);
}

void treeprint(t_bin_token *cur, int depth)
{
    if(cur== 0)
    {
        return;
    }
    for(int i = 0; i <= depth; i++)
    {
        if(depth - i > 1)
        {
            printf("  ");
        }
        else if (depth - i == 1)
        {
            printf("|-");
        }
        else if (depth - i == 0)
        {
			if (cur->type == CMD_NODE)
				printf("0");
			else
				printf("1");
			if (cur->tokens)
			{
				ft_print_tokens(cur->tokens, NULL, depth);
			}
        }
    }
    treeprint(cur->left, depth + 1);
    treeprint(cur->right, depth + 1);
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
			ft_free_tokens(data->tokens_start, 1);
		data->tokens_start = ft_token_maker(commands);
		data->tokens = data->tokens_start;
		ft_tokens_cat(&data);
		ft_expander(data->tokens, data);
		ft_rmv_quotes(data->tokens);
		if (ft_syntax_tokens(data->tokens) || ft_redirects(data->tokens, &data))
			continue ;
		ft_echo(data->tokens);
		/*ft_print_tokens(data->tokens, data);*/
		data->bin_tokens = ft_bin_tokens(data);
		t_bin_token	*tmp;
		tmp = data->bin_tokens;
		treeprint(tmp, 0);
	}
}
