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
	while (tokens->content[*i] != '\0')
	{
		if (tokens->content[*i] == '$')
			return (1);
		if (tokens->content[*i] == '"')
		{
			(*i)++;
			while (tokens->content[(*i)] != '"'
				&& tokens->content[(*i)] != '\0')
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
			&& str[i + j] != '"' && str[i + j] != '\'')
			j++;
		tmp = ft_itoa(data->exit_status);
		new = ft_substr(tokens->content, 0, i - 1);
		new = ft_strjoin_gnl(new, tmp);
		new = ft_strjoin_gnl(new, &tokens->content[i + j]);
		free(tmp);
		free(tokens->content);
		tokens->content = new;
		ft_expander_reset(tokens->content, start);
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
		if (getenv(env))
		{
			tokens->content = ft_expander_replace(tokens->content, \
									getenv(env), i++);
			ft_expander_reset(tokens->content, &i);
		}
		else if (ft_strchr(env, '$') != NULL)
			while (tokens->content[++i] != '\0'
				&& tokens->content[i] != '$'
				&& tokens->content[i] != '\'');
		free(env);
	}
	(*start) = i;
}

void	ft_expander(t_token *tokens, t_data *data)
{
	size_t	i;

	while (tokens)
	{
		i = 0;
		while (tokens->content[i] != '\0'
			&& ft_strchr(&tokens->content[i], '$'))
			ft_expander2(tokens, &i, data);
		tokens = tokens->next;
	}
}
