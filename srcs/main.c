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
#include "ft_data_init/ft_data_init.h"
#include "ft_free/ft_free.h"

int	g_signal_received = 0;

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
		else if (tokens->type == SEMI)
			printf("Semicolon");
		else if (tokens->type == AND)
			printf("And");
		else if (tokens->type == OR)
			printf("Or");
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
				printf("0\t");
			else
				printf("1\t");
			if (cur->args)
				for (int i = 0; cur->args[i]; i++)
					printf("%s\t", cur->args[i]);
			printf("\n");
			if (cur->redir_in)
				ft_print_tokens(cur->redir_in, NULL, depth + ((depth == 0) * 1));
			if (cur->redir_out)
				ft_print_tokens(cur->redir_out, NULL, depth + ((depth == 0) * 1));
        }
    }
    treeprint(cur->left, depth + 1);
    treeprint(cur->right, depth + 1);
}

char	**ft_command_init(t_data *data)
{
	char	*command_in;
	char	*command;
	char	**command_list;

	ft_prompt_init(data);
	command_in = readline(data->prompt);
	if (!command_in)
		ft_free(0, NULL, data, 1);
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

void	ft_add_quotes_to_files(t_token *tokens)
{
	char	*tmp;

	while (tokens)
	{
		if (tokens->type == FILENAME)
		{
			tmp = ft_strjoin("'", tokens->content);
			tmp = ft_strjoin_gnl(tmp, "'");
			free(tokens->content);
			tokens->content = ft_strdup(tmp);
			free(tmp);
		}
		tokens = tokens->next;
	}
}

void	ft_loop2(t_data *data)
{
	if (data->bin_tokens)
		ft_free_tree(data->bin_tokens, 1);
	data->bin_tokens = ft_bin_tokens(data);
	ft_run_cmds(data);
	/*treeprint(data->bin_tokens, 0);*/
	dup2(1, STDOUT_FILENO);
	dup2(0, STDIN_FILENO);
	(void)data;
}

t_token	*ft_return_after_con(t_token *tokens)
{
	t_token	*prev;
	t_token	*now;
	t_token	*tmp;

	now = tokens;
	prev = NULL;
	while (now)
	{
		if (now->type == SEMI || now->type == AND
			|| now->type == OR)
		{
			prev->next = NULL;
			tmp = now->next;
			free(now->content);
			free(now);
			return (tmp);
		}
		prev = now;
		now = now->next;
	}
	return (now);
}

t_token_type ft_return_con_type(t_token *tokens)
{
	t_token	*now;

	now = tokens;
	while (now)
	{
		if (now->type == SEMI)
			return (SEMI);
		if (now->type == AND)
			return (AND);
		if (now->type == OR)
			return (OR);
		now = now->next;
	}
	return (NON);
}

int		ft_syntax_con(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == SEMI && ((tokens->next
		&&	(tokens->next->type == SEMI || tokens->next->type == AND
			|| tokens->next->type == OR)) || tokens->next == NULL))
			return (ft_putstr_fd("minishell: syntax error ", 2),
				ft_putstr_fd("near unexpected token `;'\n", 2), 1);
		if (tokens->type == AND && ((tokens->next
		&&	(tokens->next->type == SEMI || tokens->next->type == AND
			|| tokens->next->type == OR)) || tokens->next == NULL))
			return (ft_putstr_fd("minishell: syntax error ", 2),
				ft_putstr_fd("near unexpected token `&&'\n", 2), 1);
		if (tokens->type == SEMI && ((tokens->next
		&&	(tokens->next->type == OR || tokens->next->type == AND
			|| tokens->next->type == OR)) || tokens->next == NULL))
			return (ft_putstr_fd("minishell: syntax error ", 2),
				ft_putstr_fd("near unexpected token `||'\n", 2), 1);
		tokens = tokens->next;
	}
	return (0);
}
void	ft_loop(t_data *data)
{
	char		**commands;
	t_token_type	type_tmp;
	int				run;

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
		ft_token_start(commands, data);
		run = 1;
		data->tokens_start = data->tokens;
		if (ft_syntax_con(data->tokens))
		{
			continue ;
		}
		data->tokens = data->tokens_start;
		while (1)
		{
			type_tmp = ft_return_con_type(data->tokens);
			if (type_tmp != NON)
				data->tokens_end = ft_return_after_con(data->tokens);
			if (type_tmp == NON)
				data->tokens_end = NULL;
			if (run == 1)
			{
				if (ft_syntax_tokens(data->tokens)
					|| ft_wildcards(data)
					|| ft_redirects(data->tokens, &data))
				{
					data->exit_status = 2;
				if (!data->tokens_start)
					continue ;
				}
				else
					ft_loop2(data);
			}
			if (type_tmp == NON)
				break ;
			if (data->exit_status)
			{
				if (type_tmp == AND)
					run = 0;
				if (type_tmp == OR)
					run = 1;
			}
			else if (!data->exit_status)
			{
				if (type_tmp == AND)
					run = 1;
				if (type_tmp == OR)
					run = 0;
			}
			if (type_tmp == SEMI)
				run = 1;
			data->tokens_start = data->tokens_end;
			data->tokens = data->tokens_start;
		}
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
