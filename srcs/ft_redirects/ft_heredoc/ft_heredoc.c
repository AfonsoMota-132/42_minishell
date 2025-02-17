/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:21:20 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/11 09:33:47 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"
#include <readline/readline.h>

int		ft_verify_heredoc(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == D_REDIRECT_IN)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

t_token *ft_verify_heredoc_is_last(t_token *tokens)
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

void	ft_pseudo_heredoc(t_token *tokens)
{
	char	*str;
	t_token	*tmp;
	while (1)
	{
		str = readline("heredoc>");
		if (str && !ft_strncmp(str, tokens->next->next->content,
				ft_strlen(tokens->next->next->content) + 1))
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

void	ft_actual_heredoc(t_token *tokens, t_data *data)
{
	t_token	*str;
	char	*tmp;
	int		fd;

	tmp = ft_heredoc_name(tokens->next->next, data);
	fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	str = malloc(sizeof(t_token));
	str->content = NULL;
	str->type = CMD;
	str->next = NULL;
	while (1)
	{
		str->content = readline("heredoc>");
		if (str && !ft_strncmp(str->content,
				tokens->next->next->content,
				ft_strlen(tokens->next->next->content) + 1))
			break ;
		ft_expander(str, data);	
		ft_putstr_fd(str->content, fd);
		ft_putchar_fd('\n', fd);
		if (str->content)
			free(str->content);
		str->content = NULL;
	}
	close(fd);
	free(tokens->next->next->content);
	tokens->next->next->content = ft_strdup(tmp);
	free(str);
	free(tmp);
}

void	ft_heredoc(t_token *tokens, t_data *data)
{
	t_token	*tmp;

	while (tokens)
	{
		if (ft_verify_heredoc(tokens))
			tmp = ft_verify_heredoc_is_last(tokens);
		while (tokens && tokens->type != PIPE)
		{
			if (tokens->next && tokens->next->type == D_REDIRECT_IN)
			{
				if (tmp && tokens->next == tmp)
					ft_actual_heredoc(tokens, data);
				else
				{
					ft_pseudo_heredoc(tokens);
					continue;
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
