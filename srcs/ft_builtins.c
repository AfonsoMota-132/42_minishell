/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 09:31:16 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/04 11:16:21 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_cd_check(t_token *tokens)
{
	if (ft_strncmp(tokens->content, "cd", 2) != 0
		|| tokens->type != CMD)
		return (1);
	if (tokens->next == NULL)
		return (0);
	if (tokens->next->type != ARG
		&& tokens->next->type != REDIRECT_IN)
		return (1);
	if (tokens->next->type == REDIRECT_IN
		&& tokens->next->next == NULL)
		return (ft_printf("minishell: cd: %s",
				"syntax error near unexpected token `newline'\n"));
	if (tokens->next->next != NULL
		&& tokens->next->next->type == ARG)
		return (printf("minishell: cd: Too many arguments\n"));
	return (0);
}

void	ft_cd(t_token *tokens)
{
	if (ft_cd_check(tokens))
		return ;
	else
		printf("Can run\n");
}

int	ft_env_check(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == CMD
			&& ft_strncmp(tokens->content, "env", 3) == 0
			&& !tokens->next)
			return (1);
		else if (tokens->type == CMD
			&& ft_strncmp(tokens->content, "env", 3) == 0
			&& tokens->next->type != ARG
			&& tokens->next->type != D_REDIRECT_IN
			&& tokens->next->type != PIPE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

void	ft_env(t_data *data)
{
	int	i;

	if (!ft_env_check(data->tokens))
		return ;
	i = 0;
	while (data->envp[i])
		i++;
}
