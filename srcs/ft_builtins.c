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

int		ft_test_cd(t_token *tokens)
{
	if (ft_strncmp(tokens->content, "cd", 2) != 0
		||	tokens->type != CMD)
		return (1);
	if (tokens->next == NULL
		&& tokens->next->type != ARG)
		return (0);
	if(tokens->next->next == NULL)
		return (0);
	if (tokens->next->type == ARG
		&& tokens->next->next->type == ARG)
		return (printf("minishell: cd: too many arguments\n"));
	return (0);
}

void	ft_cd(t_token * tokens)
{
	if (ft_test_cd(tokens))
		printf("error\n");
}
