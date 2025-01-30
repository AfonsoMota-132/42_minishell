/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:24:30 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/29 10:27:37 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_verify_redir_out(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == REDIRECT_OUT)
		{
			if (open(tokens->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644) == -1)
			{
				if (access(tokens->next->content, W_OK) == -1)
					return (printf("minishell: %s: Permission denied\n", tokens->next->content));
				return printf("Could not create file\n");
			}
		}
		else if (tokens->type == D_REDIRECT_OUT)
		{
			if (open(tokens->next->content, O_WRONLY | O_CREAT, 0644) == -1)
			{
				if (access(tokens->next->content, W_OK) == -1)
					return (printf("minishell: %s: Permission denied\n", tokens->next->content));
				return printf("Could not create file\n");
			}

		}
		tokens = tokens->next;
	}
	return (0);
}

int	ft_verify_redir_in(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == REDIRECT_IN)
		{
			if (access(tokens->next->content, F_OK) == -1)
				return (printf("minishell: %s: No such file or directory\n", tokens->next->content));
			if (access(tokens->next->content, R_OK) == -1)
				return (printf("minishell: %s: Permission denied\n", tokens->next->content));
		}
		tokens = tokens->next;
	}
	return (0);
}

int	ft_verify_redir(t_token *tokens)
{
	if (ft_verify_redir_out(tokens))
		return (1);
	if (ft_verify_redir_in(tokens))
		return (1);
	return (0);
}
