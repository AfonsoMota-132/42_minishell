/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:55:33 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/28 13:22:46 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <unistd.h>

int	ft_verify_flag(t_token *token)
{
	int	i;

	if (token == NULL)
		return (0);
	if (token->content[0] != '-')
		return (0);
	i = 0;
	while (token->content[++i] != '\0')
		if (token->content[i] != 'n')
			return (0);
	return (1);
}

int	ft_echo(t_token *token)
{
	int	n;

	n = 0;
	if (token->type == CMD
		&& ft_strncmp(token->content, "echo", 4) == 0
		&& ft_strlen(token->content) == 4)
		n = ft_verify_flag(token->next);
	else
		return (-1);
	if (token->next)
		token = token->next;
	if (n == 1 && token->next)
		token = token->next;
	while (token && token->type == ARG)
	{
		ft_putstr_fd(token->content, STDOUT_FILENO);
		if (token->next && 
			token->next->type == ARG)
			write(STDOUT_FILENO, " ", 1);
		token = token->next;
	}
	if (n != 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
