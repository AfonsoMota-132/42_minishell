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

extern int	g_signal_received;

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

void	ft_pseudo_heredoc_loop(t_token *tokens, t_data *data, t_token *str)
{
	while (1)
	{
		str->content = readline("heredoc>");
		if (!str->content && g_signal_received != 130)
			break ;
		if (!str->content && g_signal_received == 130)
		{
			if (str)
				free(str);
			ft_free(130, NULL, data, 1);
		}
		if (str && !ft_strcmp(str->content,
				tokens->next->content))
			break ;
		if (str->content)
			free(str->content);
		str->content = NULL;
	}
	if (str->content)
		free(str->content);
}

void	ft_pseudo_heredoc(t_token *tokens, t_data *data)
{
	t_token	*str;

	str = malloc(sizeof(t_token));
	str->content = NULL;
	str->type = CMD;
	str->next = NULL;
	ft_pseudo_heredoc_loop(tokens, data, str);
	free(str);
}
