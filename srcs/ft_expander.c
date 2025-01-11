/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:05:09 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/03 14:31:03 by afogonca         ###   ########.fr       */
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
		, char *env, int start)
{
	char	*tmp;
	char	*new;
	char	*str;
	int		i;
	int		j;

	str = tokens->content;
	if (env[0] == '?')
	{
		i = start;
		j = 0;
		while (tokens->content[i] && tokens->content[i] != '$')
			i++;
		while (str[i + j] && str[i + j] != ' ' && str[i + j] != '\t'
			&& str[i + j] != '\n' && str[i + j] != '$'
			&& str[i + j] != '"' && str[i + j] != '\'')
			j++;
		tmp = ft_itoa(data->exit_status);
		new = ft_substr(tokens->content, 0, i);
		new = ft_strjoin_gnl(new, tmp);
		new = ft_strjoin_gnl(new, &tokens->content[i + j + 2]);
		free(tmp);
		free(tokens->content);
		tokens->content = new;
	}
}

void	ft_expander(t_token *tokens, t_data *data)
{
	size_t	i;
	char	*env;

	while (tokens && ft_strchr(tokens->content, '$'))
	{
		i = 0;
		while (tokens->content[i] != '\0')
		{
			if (ft_check_expander(tokens, &i) != 0)
			{
				env = ft_substr(tokens->content, i + 1, \
					ft_len_env(&tokens->content[i]));
				ft_expand_quest(tokens, data, env, i);
				if (getenv(env))
					tokens->content = ft_expander_replace(tokens->content, \
											getenv(env), i++);
				while (tokens->content[i] != '\0' && tokens->content[i] != '$'
					&& tokens->content[i] != '\'')
					i++;
				free(env);
			}
		}
		tokens = tokens->next;
	}
}
