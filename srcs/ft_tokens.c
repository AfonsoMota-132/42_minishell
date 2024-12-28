/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:23:50 by afogonca          #+#    #+#             */
/*   Updated: 2024/12/28 12:24:25 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_token	*ft_token_maker(char **commands)
{
	t_token	*token;
	t_token	*start;
	int		i;

	i = -1;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	start = token;
	while (commands[++i])
	{
		token->content = ft_strdup(commands[i]);
		token->type = CMD;
		if (!commands[i + 1])
			break ;
		token->next = malloc(sizeof(t_token));
		token = token->next;
	}
	token->next = NULL;
	ft_free_cmds(commands);
	return (start);
}

void	ft_tokens_cat(t_data **data)
{
	int	check;

	check = 0;
	(*data)->tokens = (*data)->tokens_start;
	while ((*data)->tokens)
	{
		if ((*data)->tokens->content[0] == '|' && !(--check))
			(*data)->tokens->type = PIPE;
		else if ((*data)->tokens->content[0] == '<')
			(*data)->tokens->type = REDIRECT_IN;
		else if ((*data)->tokens->content[0] == '<'
			&& (*data)->tokens->content[1] == '<')
			(*data)->tokens->type = D_REDIRECT_IN;
		else if ((*data)->tokens->content[0] == '>')
			(*data)->tokens->type = REDIRECT_OUT;
		else if ((*data)->tokens->content[0] == '>'
			&& (*data)->tokens->content[1] == '>')
			(*data)->tokens->type = D_REDIRECT_OUT;
		else if (check != 0)
			(*data)->tokens->type = ARG;
		else if (++check == 1)
			(*data)->tokens->type = CMD;
		(*data)->tokens = (*data)->tokens->next;
	}
}