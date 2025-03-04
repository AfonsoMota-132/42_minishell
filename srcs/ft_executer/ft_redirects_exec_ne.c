/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects_exec_ne.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:40:30 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/04 15:45:34 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executer.h"

int	ft_error_msg_redir_ne(int type, char *redir, char *path)
{
	if (path)
		free(path);
	if (type == 0)
	{
		ft_putstr_fd(redir, 2);
		ft_putstr_fd(" : Permission denied\n", 2);
	}
	else if (type == 1)
	{
		ft_putstr_fd(redir, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
	}
	return (1);
}

int	ft_handle_redirects_in_ne(t_bin_token *tokens, char *path)
{
	if (tokens->redir_in && tokens->redir_in->type == FILENAME)
	{
		if (access(tokens->redir_in->content, F_OK) == -1)
			return (ft_error_msg_redir_ne(1, tokens->redir_in->content, path), 1);
		if (access(tokens->redir_in->content, R_OK) == -1)
			return (ft_error_msg_redir_ne(0, tokens->redir_in->content, path), 1);
	}
	else if (tokens->redir_in && tokens->redir_in->type == HERE_DOC)
	{
		if (access(tokens->redir_in->heredoc, F_OK) == -1)
			return (ft_error_msg_redir_ne(1, tokens->redir_in->heredoc, path), 1);
		if (access(tokens->redir_in->heredoc, R_OK) == -1)
			return (ft_error_msg_redir_ne(0, tokens->redir_in->heredoc, path), 1);
	}
	return (0);
}

int	ft_handle_redirects_out_ne(t_bin_token *tokens, char *path)
{
	if (tokens->redir_out)
	{
		if (access(tokens->redir_out->content, F_OK | W_OK) == -1)
			return (ft_error_msg_redir_ne(0, tokens->redir_out->content, path));
	}
	return (0);
}

void treeprint(t_bin_token *cur, int depth);
int	ft_handle_redirects_ne(t_bin_token *tokens, char *path)
{
	if (tokens->first_redir == 1)
	{
		if (ft_handle_redirects_in_ne(tokens, path))
			return (1);
		if (ft_handle_redirects_out_ne(tokens, path))
			return (1);
	}
	else if (tokens->first_redir == 0)
	{
		if (ft_handle_redirects_out_ne(tokens, path))
			return (1);
		if (ft_handle_redirects_in_ne(tokens, path))
			return (1);
	}
	return (0);
}
