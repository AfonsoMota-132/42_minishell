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
		if (tokens->content[*i] == '\'')
		{
			(*i)++;
			while (tokens->content[(*i)] != '\'')
				(*i)++;
		}
		(*i)++;
	}
	return (0);
}

int		ft_len_env(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i++] == '$')
		j += 1;
	while (str[i] != '\0' && str[i] != ' '
		&& str[i] != '\t' && str[i] != '\n'
		&& str[i] != '$')
		i++;
	return (i - j);
}

void	ft_expander(t_token *tokens)
{
	size_t	i;
	char	*env;

	while (tokens)
	{
		printf("token: %s\n", tokens->content);
		i = 0;
		while (tokens->content[i] != '\0')
		{
			if (ft_check_expander(tokens, &i) != 0)
			{
				env = ft_substr(tokens->content, i + 1
					, ft_len_env(&tokens->content[i]));
				printf("wtf: %s\n", env);
				if (tokens->content[i] == '$')
					i++;
				while (tokens->content[i] != '\0'
					&& tokens->content[i] != '$')
					i++;
			}
		}
		tokens = tokens->next;
	}
}
