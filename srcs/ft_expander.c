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

char	*ft_check_expander(t_token *tokens)
{
	size_t	i;

	i = -1;
	while (tokens->content[++i] != '\0')
	{
		if (tokens->content[i] == '$')
			return (tokens->content + i);
		if (tokens->content[i] == '\'')
		{
			i++;
			while (tokens->content[i] != '\'')
				i++;
		}
	}
	return (tokens->content + i);
}

void	ft_expander(t_token *tokens)
{
	while (tokens)
	{
		if (*ft_check_expander(tokens) != '\0')
			printf("ft_expander: %s\n",getenv(ft_strchr(tokens->content, '$') + 1));
		tokens = tokens->next;
	}
}
