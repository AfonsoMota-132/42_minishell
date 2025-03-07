/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:05:09 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/20 09:36:06 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

void	ft_check_expander2(t_token *tokens, size_t *i)
{
	if (tokens->content[*i] == '\'')
	{
		(*i)++;
		while (tokens->content[(*i)] != '\''
			&& tokens->content[(*i)] != '\0')
			(*i)++;
	}
}

void	ft_expand_quest(t_token *tokens, t_data *data
		, char *env, size_t *start)
{
	char	*tmp;
	char	*new;
	char	*str;
	int		i;

	str = tokens->content;
	if (env[0] == '?')
	{
		i = (*start);
		while (tokens->content[i] && tokens->content[i] != '$')
			i++;
		if (str[i] == '$')
			i++;
		tmp = ft_itoa(data->exit_status);
		new = ft_substr(tokens->content, 0, i - 1);
		new = ft_strjoin_gnl(ft_strjoin_gnl(new, tmp), &tokens->content[i + 1]);
		free(tmp);
		free(tokens->content);
		tokens->content = new;
		ft_expander2(tokens, start, data);
	}
}

void	ft_expander3(t_token *tokens, size_t *i)
{
	if (tokens->content[(*i) + 1] && tokens->content[(*i) + 1] != ' '
		&& tokens->content[(*i) + 1] != '"')
	{
		if ((tokens->type == FILENAME && tokens->content[0] == '$')
			|| !ft_isalnum(tokens->content[(*i) + 1]))
			(*i)++;
		else
		{
			tokens->content = ft_expander_replace_null(tokens->content, *i);
			(*i) = 0;
		}
	}
	else if (tokens->content[(*i) + 1])
		(*i)++;
}

void	ft_expander_plus(t_data *data)
{
	char	**split;
	t_token	*tmp;

	data->tokens = data->tokens_start;
	while (data->tokens)
	{
		if (data->tokens->quotes == 0
			&& data->tokens->content)
		{
			split = ft_split_multi(data->tokens->content, " \t");
			if (ft_count_split(split) > 1)
			{
				tmp = ft_token_maker_special(split, data->tokens->type);
				ft_replace_node(&data->tokens_start, data->tokens, tmp);
				data->tokens = data->tokens_start;
			}
			else
				ft_free_matrix(split);
		}
		data->tokens = data->tokens->next;
	}
}

void	ft_expander2(t_token *tokens, \
		size_t *start, t_data *data)
{
	size_t	i;
	char	*env;

	i = (*start);
	ft_skip_single_quote(tokens->content, &i);
	if (ft_check_expander(tokens, &i) != 0)
	{
		env = ft_substr(tokens->content, i + 1, \
			ft_len_env(&tokens->content[i]));
		ft_expand_quest(tokens, data, env, &i);
		if (ft_getenv(env, data) != NULL)
		{
			tokens->content = ft_expander_replace(tokens->content, \
									ft_getenv(env, data), i++);
			ft_expander_reset(tokens->content, &i);
			ft_expander2(tokens, start, data);
		}
		else if (ft_strchr(tokens->content, '$') != NULL)
			ft_expander3(tokens, &i);
		free(env);
	}
	(*start) = i;
}
