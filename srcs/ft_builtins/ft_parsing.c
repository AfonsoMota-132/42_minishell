/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:45:31 by palexand          #+#    #+#             */
/*   Updated: 2025/02/24 18:23:31 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_is_command(t_data *data, t_bin_token *token)
{
	if (token->type == CMD_NODE)
		{
			ft_builtin_choice(data, token);
		}
	return (0);
}

void	ft_builtin_choice(t_data *data, t_bin_token *token)
{
	if (token->type == CMD_NODE)
	{
		if (ft_strncmp(token->args[0], "echo", 5) == 0)
			ft_echo(data, token);
		else if (ft_strncmp(token->args[0], "cd", 3) == 0)
			ft_cd(data, token);
		/*else if (ft_strcmp(token->args[0], "pwd") == 0)*/
		/*	ft_pwd(data, token);*/
		/*else if (ft_strcmp(token->args[0], "export") == 0)*/
		/*	ft_export(data, token);*/
		/*else if (ft_strcmp(token->args[0], "unset") == 0)*/
		/*	ft_unset(data, token);*/
		else if (ft_strcmp(token->args[0], "env") == 0)
			ft_print_envp(data);
		/*else if (ft_strcmp(token->args[0], "exit") == 0)*/
		/*	ft_exit(data, token);*/
	}
}

