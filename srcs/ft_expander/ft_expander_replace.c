/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_replace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:05:49 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 15:06:32 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

int	ft_inside_quotes(char *str, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (i == c && count)
			return (1);
		if (i == c && !count)
			return (0);
		if (str[i] == '"' && !count)
			count++;
		else if (str[i] == '"' && count)
			count--;
		i++;
	}
	return (0);
}

char	*ft_env_rep_sq_special(char	*str, char *env, int i, int j)
{
	char	*new;
	char	*tmp;

	new = ft_substr(str, 0, i - 1);
	if (ft_strchr(env, '\'') != NULL
		&& !ft_inside_quotes(str, i))
	{
		tmp = ft_strjoin("\"", env);
		tmp = ft_strjoin_gnl(tmp, "\"");
		new = ft_strjoin_gnl(new, tmp);
		free(tmp);
	}
	else
		new = ft_strjoin_gnl(new, env);
	new = ft_strjoin_gnl(new, &str[i + j]);
	return (new);
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
		&& str[i + j] != '\'' && str[i + j] != '.'
		&& str[i + j] != '\\' && str[i] != '/'
		&& str[i + j] != '=')
		j++;
	new = ft_env_rep_sq_special(str, env, i, j);
	free(str);
	return (new);
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
	if (str[i] && !ft_isdigit(str[i]) && str[i] != '$')
		while (str[i] && str[i] != ' ' && str[i] != '\t'
			&& str[i] != '\n' && str[i] != '$'
			&& str[i] != '"' && str[i] != '\''
			&& str[i] != '.' && str[i] != '\\'
			&& str[i] != '/' && str[i] != '=' && i++);
	else
		i++;
	if (start != 1)
		new = ft_substr(str, 0, start - 1);
	else
		new = NULL;
	if (str[i] && str[i] != ' ')
		new = ft_strjoin_gnl(new, &str[i]);
	return (free(str), new);
}
