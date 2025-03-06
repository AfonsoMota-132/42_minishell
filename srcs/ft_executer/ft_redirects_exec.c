/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:23:31 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/25 22:27:39 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executer.h"

void	ft_handle_redirects_in2(t_data *data, t_bin_token *tokens, char *path)
{
	int	fd;

	if (tokens->redir_in && tokens->redir_in->type == HERE_DOC)
	{
		if (ft_strchr(tokens->redir_in->content, '*') != NULL
			&& !tokens->redir_in->quotes)
			ft_error_msg_redir(data, 2, tokens->redir_in->content, path);
		if (access(tokens->redir_in->heredoc, F_OK) == -1)
			ft_error_msg_redir(data, 1, tokens->redir_in->heredoc, path);
		if (access(tokens->redir_in->heredoc, R_OK) == -1)
			ft_error_msg_redir(data, 0, tokens->redir_in->heredoc, path);
		fd = open(tokens->redir_in->heredoc, O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
	}
}

void	ft_handle_redirects_in(t_data *data, t_bin_token *tokens, char *path)
{
	int	fd;

	if (tokens->redir_in && tokens->redir_in->type == FILENAME)
	{
		if ((tokens->redir_in->content[0] == '$'
				|| ft_strchr(tokens->redir_in->content, '*') != NULL)
			&& !tokens->redir_in->quotes)
			ft_error_msg_redir(data, 2, tokens->redir_in->content, path);
		if (access(tokens->redir_in->content, F_OK) == -1)
			ft_error_msg_redir(data, 1, tokens->redir_in->content, path);
		if (access(tokens->redir_in->content, R_OK) == -1)
			ft_error_msg_redir(data, 0, tokens->redir_in->content, path);
		fd = open(tokens->redir_in->content, O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
	}
}

void	ft_handle_redirects_out(t_data *data, t_bin_token *tokens, char *path)
{
	int		fd;

	if (tokens->redir_out)
	{
		if ((tokens->redir_out->content[0] == '$'
				||ft_strchr(tokens->redir_out->content, '*') != NULL)
			&& !tokens->redir_out->quotes)
			ft_error_msg_redir(data, 2, tokens->redir_out->content, path);
		if (access(tokens->redir_out->content, F_OK | W_OK) == -1)
			ft_error_msg_redir(data, 0, tokens->redir_out->content, path);
		fd = open(tokens->redir_out->content, O_WRONLY | O_APPEND, 0);
		dup2(fd, STDOUT_FILENO);
	}
}

void	ft_handle_redirects(t_data *data, t_bin_token *tokens, char *path)
{
	if (tokens->first_redir == 1)
	{
		ft_handle_redirects_in(data, tokens, path);
		ft_handle_redirects_out(data, tokens, path);
	}
	else if (tokens->first_redir == 0)
	{
		ft_handle_redirects_out(data, tokens, path);
		ft_handle_redirects_in(data, tokens, path);
	}
}
