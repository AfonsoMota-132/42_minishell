/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:23:50 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/23 11:17:45 by afogonca         ###   ########.fr       */
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
		/*token->has_quote = 0;*/
		/*if (ft_strchr(commands[i], '\'')*/
		/*	|| ft_strchr(commands[i], '"'))*/
		/*	token->has_quote = 1;*/
		if (!commands[i + 1])
			break ;
		token->next = malloc(sizeof(t_token));
		token = token->next;
	}
	token->next = NULL;
	ft_free_cmds(commands);
	return (start);
}

int	ft_tokens_cat2(t_data **data, int check)
{
	if ((*data)->tokens->content[0] == '<')
	{
		(*data)->tokens->type = REDIRECT_IN;
		if ((*data)->tokens->next)
			(*data)->tokens->next->type = FILENAME;
	}
	else if ((*data)->tokens->content[0] == '>'
		&& (*data)->tokens->content[1] == '>')
	{
		(*data)->tokens->type = D_REDIRECT_OUT;
		if ((*data)->tokens->next)
			(*data)->tokens->next->type = FILENAME;
	}
	else if ((*data)->tokens->content[0] == '>')
	{
		(*data)->tokens->type = REDIRECT_OUT;
		if ((*data)->tokens->next)
			(*data)->tokens->next->type = FILENAME;
	}
	else if ((*data)->tokens->type == CMD && check > 0)
		check--;
	else if ((*data)->tokens->type == CMD && check == 0)
		(*data)->tokens->type = ARG;
	return (check);
}
void	ft_tokens_cat(t_data **data)
{
	int	check;

	check = 1;
	(*data)->tokens = (*data)->tokens_start;
	while ((*data)->tokens)
	{
		if ((*data)->tokens->content[0] == '|' && ft_strlen((*data)->tokens->content) == 1 
			&& ++check)
			(*data)->tokens->type = PIPE;
		else if ((*data)->tokens->content[0] == '<'
			&& (*data)->tokens->content[1] == '<')
		{
			(*data)->tokens->type = D_REDIRECT_IN;
			if ((*data)->tokens->next)
				(*data)->tokens->next->type = HERE_DOC;
		}
		else
			check = ft_tokens_cat2(data, check);
		(*data)->tokens = (*data)->tokens->next;
	}
	(*data)->tokens = (*data)->tokens_start;
}
