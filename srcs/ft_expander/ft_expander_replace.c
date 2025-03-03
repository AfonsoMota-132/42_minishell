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
			&& str[i] != '\'' && i++);
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
