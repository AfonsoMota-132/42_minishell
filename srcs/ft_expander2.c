/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:33:36 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/20 09:36:39 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_expander_reset(char *str, size_t *i)
{
	*i = 0;
	ft_skip_single_quote(str, i);
	while (str[(*i)] != '\0'
		&& str[(*i)] != '$'
		&& str[(*i)] != '"')
		(*i)++;
}

void	ft_skip_single_quote(char *str, size_t *i)
{
	while (str[(*i)] != '\0'
		&& str[(*i)] != '$'
		&& ft_strchr(&str[*i], '\''))
	{
		if (str[(*i)] == '"')
		{
			(*i)++;
			while (str[(*i)] && str[*i] != '$'
				&& str[*i] != '"' && ++(*i));
			if (str[(*i)] == '"')
				(*i)++;
			if (str[(*i)] == '$')
				break ;
		}
		else if (str[(*i)] == '\'')
		{
			(*i)++;
			while (str[(*i)] && str[*i] != '\'')
				(*i)++;
			(*i)++;
		}
		else
			(*i)++;
	}
}

int	ft_len_env(char *str)
{
	int	i;
	int	check;
	int	j;

	check = 0;
	i = 0;
	j = 0;
	if (str[i++] == '$')
		j += 1;
	while (str[i] != '\0' && str[i] != ' '
		&& str[i] != '\t' && str[i] != '\n'
		&& str[i] != '$' && str[i] != '"'
		&& str[i] != '\'')
	{
		if (str[i] == '\'' && !check)
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		i++;
	}
	return (i - j);
}

void	ft_expander(t_token *tokens, t_data *data)
{
	size_t	i;

	while (tokens)
	{
		i = 0;
		while (tokens->content[i] != '\0'
			&& ft_strchr(&tokens->content[i], '$'))
		{
			ft_expander2(tokens, &i, data);
		}
		tokens = tokens->next;
	}
}
