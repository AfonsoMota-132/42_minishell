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

#include "../incs/minishell.h"

int	ft_check_expander(t_token *tokens, size_t *i)
{
	if (tokens && tokens->content && ft_strlen(tokens->content) < (*i))
		return (0);
	while (tokens->content[*i] != '\0')
	{
		if (tokens->content[*i] == '$'
			&& tokens->content[*i + 1])
			return (1);
		if (tokens->content[*i] == '"')
		{
			(*i)++;
			while (tokens->content[(*i)] != '\0' &&
				tokens->content[(*i)] != '"')
			{
				if (tokens->content[(*i)] == '$')
					return (1);
				(*i)++;
			}
		}
		if (tokens->content[*i] == '\'')
		{
			(*i)++;
			while (tokens->content[(*i)] != '\''
				&& tokens->content[(*i)] != '\0')
				(*i)++;
		}
		if (tokens->content[(*i)])
			(*i)++;
	}
	return (0);
}

char	*ft_expander_replace(char *str, char *env, int start)
{
	int		i;
	int		j;
	char	*new;

	j = 0;
	i = start;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
		i++;
	while (str[i + j] && str[i + j] != ' '
		&& str[i + j] != '\t' && str[i + j] != '\n'
		&& str[i + j] != '$' && str[i + j] != '"'
		&& str[i + j] != '\'')
		j++;
	new = ft_substr(str, 0, i - 1);
	new = ft_strjoin_gnl(new, env);
	new = ft_strjoin_gnl(new, &str[i + j]);
	free(str);
	return (new);
}

void	ft_expand_quest(t_token *tokens, t_data *data
		, char *env, size_t *start)
{
	char	*tmp;
	char	*new;
	char	*str;
	int		i;
	int		j;

	str = tokens->content;
	if (env[0] == '?')
	{
		i = (*start);
		j = 0;
		while (tokens->content[i] && tokens->content[i] != '$')
			i++;
		if (str[i] == '$')
			i++;
		while (str[i + j] && str[i + j] != ' ' && str[i + j] != '\t'
			&& str[i + j] != '\n' && str[i + j] != '$'
			&& str[i + j] != '"' && str[i + j] != '\'' && ++j);
		tmp = ft_itoa(data->exit_status);
		new = ft_substr(tokens->content, 0, i - 1);
		new = ft_strjoin_gnl(ft_strjoin_gnl(new, tmp), &tokens->content[i + 1]);
		free(tmp);
		free(tokens->content);
		tokens->content = new;
		ft_expander2(tokens, start, data);
	}
}

char	*ft_expander_replace_null(char *str, int start)
{
	int		i;
	char	*new;

	i = start;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
		i++;
	start = i;
	if (str[i] && !ft_isdigit(str[i])
		&& str[i] != '$')
		while (str[i] && str[i] != ' '
			&& str[i] != '\t' && str[i] != '\n'
			&& str[i] != '$' && str[i] != '"'
			&& str[i] != '\'')
			i++;
	else
		i++;
	if (start != 1)
		new = ft_substr(str, 0, start - 1);
	else
		new = NULL;
	if (str[i] && str[i] != ' ')
		new = ft_strjoin_gnl(new, &str[i]);
	free(str);
	return (new);
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
			ft_expander2(tokens, start, data);
		}
		else if (ft_strchr(tokens->content, '$') != NULL)
		{
			if (tokens->content[i + 1] && tokens->content[i + 1] != ' '
				&& tokens->content[i + 1] != '"')
			{
				tokens->content = ft_expander_replace_null(tokens->content, i);
				i = 0;
			}
			else if (tokens->content[i + 1])
				i++;
		}
		free(env);
	}
	(*start) = i;
}
