/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:50:55 by afogonca          #+#    #+#             */
/*   Updated: 2024/12/27 11:51:02 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_free_cmds(char **commands)
{
	int	i;

	i = -1;
	while (commands[++i])
		free(commands[i]);
	free(commands);
}

void	ft_free_tokens(t_token *tokens)
{
	t_token	*tmp;
	
	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = tmp;
		if (!tokens)
			break ;
	}
}

int	ft_free(int i, char *command, t_data *data)
{
	if (command)
		free(command);
	if (data)
	{
		if (data->tokens_start)
			ft_free_tokens(data->tokens_start);
		free(data);
	}
	exit(i);
}
