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

#include "ft_tokens.h"

t_token	*ft_token_maker(char **commands)
{
	t_token	*token;
	t_token	*start;
	int		i;

	i = -1;
	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	start = token;
	while (commands[++i])
	{
		token->content = ft_strdup(commands[i]);
		token->type = CMD;
		token->heredoc = NULL;
		if (ft_strchr(commands[i], '"') || ft_strchr(commands[i], '\''))
			token->quotes = 1;
		token->quotes = 0;
		if (!commands[i + 1])
			break ;
		token->next = ft_calloc(sizeof(t_token), 1);
		token = token->next;
	}
	token->next = NULL;
	ft_free_matrix(commands);
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

void	ft_tokens_cat3(t_data **data)
{
	if ((*data)->tokens->content[0] == ';'
		&& ft_strlen((*data)->tokens->content) == 1)
		(*data)->tokens->type = SEMI;
	if ((*data)->tokens->content[0] == '&'
		&& (*data)->tokens->content[1] == '&'
		&& ft_strlen((*data)->tokens->content) == 2)
		(*data)->tokens->type = AND;
	if ((*data)->tokens->content[0] == '|'
		&& (*data)->tokens->content[1] == '|'
		&& ft_strlen((*data)->tokens->content) == 2)
		(*data)->tokens->type = OR;
	if ((ft_strchr((*data)->tokens->content, '\'')
			|| ft_strchr((*data)->tokens->content, '"'))
		&& (*data)->tokens->type != CMD && (*data)->tokens->type != HERE_DOC
		&& (*data)->tokens->type != FILENAME)
		(*data)->tokens->type = ARG;
}

void	ft_tokens_cat(t_data **data)
{
	int	check;

	check = 1;
	(*data)->tokens = (*data)->tokens_start;
	while ((*data)->tokens)
	{
		if ((*data)->tokens->content[0] == '|'
			&& ft_strlen((*data)->tokens->content) == 1 && ++check)
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
		ft_tokens_cat3(data);
		(*data)->tokens = (*data)->tokens->next;
	}
	(*data)->tokens = (*data)->tokens_start;
}

void	ft_expander_plus(t_data *data);
int	ft_token_start(char **commands, t_data *data)
{
	if (data->tokens_start)
		ft_free_tokens(data->tokens_start, 1);
	data->tokens_start = ft_token_maker(commands);
	data->tokens = data->tokens_start;
	if (ft_syntax_tokens_quotes(data->tokens))
	{
		data->exit_status = 2;
		return (1);
	}
	ft_tokens_cat(&data);
	ft_expander(data->tokens, data);
	ft_rmv_quotes(data->tokens);
	ft_expander_plus(data);
	data->tokens = data->tokens_start;
	return (0);
}
