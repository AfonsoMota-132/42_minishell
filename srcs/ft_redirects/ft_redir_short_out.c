/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_short_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:09:59 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:34:49 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_redirects.h"

t_token	*ft_take_ro_out(t_token *head, t_token *tokens, int i)
{
	t_token	*tmp;

	if (i == -1)
		return (tokens);
	tokens = head;
	while (tokens && tokens->type != PIPE)
	{
		tmp = tokens->next;
		if (tokens->next && (tokens->next->type == D_REDIRECT_OUT
				|| tokens->next->type == REDIRECT_OUT)
			&& tokens->next->next && i == 1)
		{
			tokens->next = tokens->next->next->next;
			ft_free_token(tmp);
			break ;
		}
		else if (tokens && (tokens->next->type == D_REDIRECT_OUT
				|| tokens->next->type == REDIRECT_OUT)
			&& tokens->next->next && !(++i))
			tokens = tokens->next;
		else
			tokens = tokens->next;
	}
	return (head);
}

int	ft_verify_redir_short(t_token *tokens)
{
	char	redirect_single;
	char	redirect_double;

	redirect_single = 0;
	redirect_double = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == D_REDIRECT_OUT && !redirect_single)
			redirect_single++;
		else if (tokens->type == REDIRECT_OUT && !redirect_double)
			redirect_double++;
		if (redirect_double && redirect_single)
			break ;
		tokens = tokens->next;
	}
	return ((redirect_double && redirect_single));
}

int	ft_verify_access_out(t_token *tokens)
{
	if (access(tokens->next->content, W_OK) == -1
		|| tokens->next->content[0] == '$')
		return (0);
	return (1);
}

void	ft_redir_short_out_2(t_token *tokens, int *i)
{
	while (tokens && tokens->type != PIPE)
	{
		if ((tokens->type == D_REDIRECT_OUT
				|| tokens->type == REDIRECT_OUT))
		{
			(*i) = ft_verify_access_out(tokens);
			break ;
		}
		else
			tokens = tokens->next;
	}
}

void	ft_redir_short_out(t_token *tokens)
{
	t_token	*head;
	int		i;

	while (tokens)
	{
		i = -1;
		head = tokens;
		if (tokens->type == PIPE)
			tokens = tokens->next;
		if (!ft_verify_redir_short(tokens))
			tokens = ft_skip_to_pipe(tokens);
		else
			ft_redir_short_out_2(tokens, &i);
		tokens = ft_take_ro_out(head, tokens, i);
		if (tokens && tokens->next)
			tokens = tokens->next;
	}
}
