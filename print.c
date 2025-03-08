/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:37:02 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/08 00:37:13 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

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
		else if (tokens->type == IN_PAR)
			printf("In Par");
		else if (tokens->type == OUT_PAR)
			printf("Out Par");
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
