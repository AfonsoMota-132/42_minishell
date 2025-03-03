/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:54:15 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/28 08:54:38 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

int	ft_verify_numeric_exit(t_bin_token *tokens, int print)
{
	int	i;

	if (tokens->args[1])
	{
		i = -1;
		while (tokens->args[1][++i])
		{
			if (!ft_isdigit(tokens->args[1][i])
				&& tokens->args[1][i] != '+'
				&& tokens->args[1][i] != '-')
			{
				if (print)
				{
					ft_putstr_fd("minishell : exit: ", 2);
					ft_putstr_fd(tokens->args[1], 2);
					ft_putstr_fd(": numeric argument required\n", 2);
				}
				return (2);
			}
		}
	}
	return (0);
}

int	ft_exit(t_data *data, t_bin_token *tokens, int exit)
{
	int	status;

	if (!ft_verify_numeric_exit(tokens, 1))
	{
		if (tokens->args[1] && tokens->args[2])
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			if (exit)
				ft_free(1, NULL, data, 0);
			return (1);
		}
		if (tokens->args[1])
			status = ft_atoi(tokens->args[1]);
		else
			status = data->exit_status;
	}
	else
		status = ft_verify_numeric_exit(tokens, 0);
	ft_free(status, NULL, data, 0);
	return (0);
}
