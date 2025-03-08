/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_bin_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:06:42 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:08:36 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bin_tokens.h"

t_bin_token	*ft_calloc_bin_token(t_bin_token_type type)
{
	t_bin_token	*new;

	new = malloc(sizeof(t_bin_token));
	new->nbr_args = 0;
	new->args = NULL;
	new->redir_in = NULL;
	new->redir_out = NULL;
	new->right = NULL;
	new->left = NULL;
	new->type = type;
	return (new);
}

t_token	*ft_bin_redir2_heredoc(t_token **tokens)
{
	t_token	*tmp;

	if ((*tokens)->type == D_REDIRECT_IN)
	{
		tmp = (*tokens);
		(*tokens) = (*tokens)->next;
		tmp->next = NULL;
		ft_free_tokens(tmp, 1);
	}
	return (*tokens);
}

t_token	*ft_bin_redir2(t_token **tokens, t_token_type redir_1
			, t_token_type redir_2)
{
	t_token	*tmp_token;
	t_token	*tmp;

	if ((*tokens) && ((*tokens)->type == redir_1
			|| (*tokens)->type == redir_2))
	{
		if ((*tokens)->type == D_REDIRECT_IN)
		{
			free((*tokens)->content);
			(*tokens)->content = NULL;
		}
		tmp_token = (*tokens);
		tmp = ((*tokens)->next);
		if ((*tokens)->next->next)
		{
			(*tokens) = (*tokens)->next->next;
			tmp->next = NULL;
		}
		else
			(*tokens) = NULL;
		free(tmp_token->content);
		free(tmp_token);
		return (tmp);
	}
	return (NULL);
}

t_token	*ft_bin_redir(t_token **tokens, t_token_type redir_1
			, t_token_type redir_2)
{
	t_token	*tmp_token;
	t_token	*tmp;
	t_token	*head;

	tmp = ft_bin_redir2(tokens, redir_1, redir_2);
	if (tmp)
		return (tmp);
	head = (*tokens);
	while (head)
	{
		tmp_token = head->next;
		if (head && head->next && (head->next->type == redir_1
				|| head->next->type == redir_2))
			break ;
		head = head->next;
	}
	if (!head)
		return (NULL);
	head->next = head->next->next->next;
	tmp_token->next->next = NULL;
	tmp = tmp_token->next;
	free(tmp_token->content);
	free(tmp_token);
	return (tmp);
}

void	ft_update_bin_token2(t_bin_token *bin_token, t_token *tokens)
{
	t_token	*tmp;
	int		arg_len;
	int		i;

	arg_len = ft_bin_count_args(tokens);
	bin_token->nbr_args = arg_len;
	bin_token->args = ft_calloc(sizeof(char *), arg_len + 1);
	i = 0;
	while (i < arg_len && tokens)
	{
		tmp = tokens->next;
		if (tokens->content)
			bin_token->args[i++] = ft_strdup(tokens->content);
		if (tokens->content)
			free(tokens->content);
		free(tokens);
		if (!tmp)
			break ;
		tokens = tmp;
	}
}

void	ft_update_bin_token(t_bin_token	*bin_token, t_token *tokens)
{
	bin_token->first_redir = ft_first_redir(tokens);
	bin_token->redir_in = ft_bin_redir(&tokens, REDIRECT_IN, D_REDIRECT_IN);
	bin_token->redir_out = ft_bin_redir(&tokens, REDIRECT_OUT, D_REDIRECT_OUT);
	if (tokens)
		ft_update_bin_token2(bin_token, tokens);
	else
		bin_token->args = ft_calloc(sizeof(char *), 2);
}
