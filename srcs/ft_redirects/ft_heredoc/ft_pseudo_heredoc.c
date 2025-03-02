/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:21:01 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/23 13:21:30 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heredoc.h"

void	ft_del_pseudo_heredocs(t_token *tokens)
{
	t_token	*tmp2;

	while (tokens)
	{
		if (tokens->next
			&& tokens->next->type == D_REDIRECT_IN
			&& tokens->next->next && !tokens->next->next->heredoc)
		{
			tmp2 = tokens->next;
			tokens->next = tokens->next->next->next;
			ft_free_token(tmp2);
		}
		tokens = tokens->next;
	}
}

void	ft_pseudo_heredoc(t_token *tokens)
{
	char	*str;
	t_token	*tmp;

	while (1)
	{
		str = readline("heredoc>");
		if ((!str) || (str && !ft_strncmp(str, tokens->next->next->content,
					ft_strlen(tokens->next->next->content) + 1)))
			break ;
		free(str);
		str = NULL;
	}
	if (str)
		free(str);
	tmp = tokens->next;
	tokens->next = tokens->next->next->next;
	ft_free_token(tmp);
}
