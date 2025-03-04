/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmv_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:43:14 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/10 08:43:36 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rmv_quotes.h"

int	ft_quote_rm_len(char const *s, char quote)
{
	int		i;

	i = 0;
	while (s[++i])
	{
		if (s[i] == quote)
			return (i - 1);
	}
	return (0);
}

char	*ft_rmv_single_quotes(char *str, int *start)
{
	int		i;
	char	*new;
	char	*quote;

	i = *start;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\'')
		i++;
	if (i != 1)
		new = ft_substr(str, 0, i - 1);
	else
		new = NULL;
	quote = ft_substr(str, (*start) + 1, ft_quote_rm_len(&str[i - 1], '\''));
	new = ft_strjoin_gnl(new, quote);
	new = ft_strjoin_gnl(new, &str[i + 1 + ft_quote_rm_len(&str[i - 1], '\'')]);
	*start = i + ft_quote_rm_len(&str[i - 1], '\'') - 1;
	free(str);
	free(quote);
	return (new);
}

char	*ft_rmv_double_quotes(char *str, int *start)
{
	int		i;
	char	*new;
	char	*quote;

	i = *start;
	while (str[i] && str[i] != '"')
		i++;
	if (str[i] == '"')
		i++;
	if (i != 1)
		new = ft_substr(str, 0, i - 1);
	else
		new = NULL;
	quote = ft_substr(str, (*start) + 1, ft_quote_rm_len(&str[i - 1], '"'));
	new = ft_strjoin_gnl(new, quote);
	new = ft_strjoin_gnl(new, &str[i + 1 + ft_quote_rm_len(&str[i - 1], '"')]);
	*start = i + ft_quote_rm_len(&str[i - 1], '"') - 1;
	free(str);
	free(quote);
	return (new);
}

void	ft_empty_quotes(t_token *tokens, int i)
{
	if (((tokens->content[i] == '"'
				&& tokens->content[i + 1] == '"')
			|| (tokens->content[i] == '\''
				&& tokens->content[i + 1] == '\''))
		&& ft_strlen(tokens->content) == 2)
	{
		free(tokens->content);
		tokens->content = ft_strdup("");
	}
}

void	ft_rmv_quotes(t_token *tokens)
{
	int		i;

	while (tokens)
	{
		i = 0;
		while (tokens->content && tokens->content[i] != '\0')
		{
			ft_empty_quotes(tokens, i);
			if (ft_strlen(tokens->content) == 0)
				break ;
			if (tokens->content[i] != '\''
				&& tokens->content[i] != '"')
				i++;
			if (tokens->content[i] == '"')
				tokens->content = ft_rmv_double_quotes(tokens->content, &i);
			if (tokens->content[i] == '\'')
				tokens->content = ft_rmv_single_quotes(tokens->content, &i);
		}
		tokens = tokens->next;
	}
}
