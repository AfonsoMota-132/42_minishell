/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:21:20 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:26:25 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heredoc.h"

extern int	g_signal_received;

int	ft_verify_heredoc(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == D_REDIRECT_IN)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

t_token	*ft_verify_heredoc_is_last(t_token *tokens)
{
	t_token	*tmp;

	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == D_REDIRECT_IN)
			tmp = tokens;
		else if (tokens->type == REDIRECT_IN
			&& (access(tokens->next->content, F_OK) == -1
				|| access(tokens->next->content, R_OK) == -1))
			return (NULL);
		else if (tokens->type == REDIRECT_IN)
			tmp = NULL;
		tokens = tokens->next;
	}
	return (tmp);
}

void	ft_heredoc_child_process(t_data *data, t_token *tokens, t_token *tmp)
{
	signal(SIGINT, &ft_heredoc_signal_handler);
	while (tokens)
	{
		tmp = ft_verify_heredoc_is_last(tokens);
		while (tokens && tokens->type != PIPE)
		{
			if ((tmp && tmp == tokens)
				|| (tokens && tokens->type == D_REDIRECT_IN))
			{
				if (tokens->next && tokens->next->heredoc)
					ft_actual_heredoc(tokens, data);
				else
					ft_pseudo_heredoc(tokens, data);
			}
			if (tokens)
				tokens = tokens->next;
		}
		tokens = ft_skip_to_pipe(tokens);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
}

int	ft_heredoc(t_token *tokens, t_data *data)
{
	pid_t	c_pid;
	t_token	*tmp;
	int		exit;

	exit = 0;
	if (!ft_verify_heredoc(tokens))
		return (0);
	ft_define_heredoc_paths(tokens, data);
	signal(SIGINT, SIG_IGN);
	signal(127, SIG_IGN);
	c_pid = fork();
	g_signal_received = 0;
	if (c_pid == 0)
	{
		tmp = ft_verify_heredoc_is_last(tokens);
		ft_heredoc_child_process(data, tokens, tmp);
		ft_free(0, NULL, data, 0);
	}
	else
		waitpid(-1, &exit, 0);
	ft_signals();
	ft_del_pseudo_heredocs(tokens);
	data->exit_status = WEXITSTATUS(exit);
	return ((data->exit_status == 130) * 130);
}
