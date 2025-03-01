/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actual_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:07:22 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/23 13:11:49 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

extern int	g_signal_received;

int	ft_strvalue(char *str)
{
	int	i;
	int	value;

	i = -1;
	value = 0;
	while (str && str[++i])
		value += str[i];
	return (value);
}

char	*ft_heredoc_name(t_token *tokens, t_data *data)
{
	char	*tmp;
	char	*tmp2;
	char	*number;
	int		value;

	value = 0;
	while (1)
	{
		tmp = ft_strdup(".temp_");
		if (!value)
			value = ft_strvalue(tokens->content);
		else
			value++;
		number = ft_itoa(value);
		tmp = ft_strjoin_gnl(tmp, number);
		tmp2 = ft_strjoin(data->heredoc_path, tmp);
		free(tmp);
		free(number);
		if (access(tmp2, F_OK) == -1)
			break ;
		free(tmp2);
	}
	return (tmp2);
}

void	ft_define_heredoc_paths(t_token *tokens, t_data *data)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = ft_verify_heredoc_is_last(tokens);
		while (tokens && tokens->type != PIPE)
		{
			if (tokens && tokens->type == D_REDIRECT_IN)
			{
				if (tmp && tokens == tmp)
				{
					tokens->next->heredoc = \
						ft_heredoc_name(tokens->next, data);
				}
			}
			if (tokens)
				tokens = tokens->next;
		}
		tokens = ft_skip_to_pipe(tokens);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
}

void	ft_actual_heredoc_loop(t_token *tokens, t_data *data
							, t_token *str, int fd)
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
			close (fd);
			ft_free(130, NULL, data, 1);
		}
		if (str && !ft_strncmp(str->content,
				tokens->next->content,
				ft_strlen(tokens->next->content) + 1))
			break ;
		ft_expander(str, data);
		ft_putstr_fd(str->content, fd);
		ft_putchar_fd('\n', fd);
		if (str->content)
			free(str->content);
		str->content = NULL;
	}
	if (str->content)
		free(str->content);
}

void	ft_actual_heredoc(t_token *tokens, t_data *data)
{
	t_token	*str;
	int		fd;

	fd = open(tokens->next->heredoc,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	str = malloc(sizeof(t_token));
	str->content = NULL;
	str->type = CMD;
	str->next = NULL;
	ft_actual_heredoc_loop(tokens, data, str, fd);
	close(fd);
	free(str);
}
