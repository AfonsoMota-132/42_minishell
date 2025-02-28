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

#include "../../incs/minishell.h"

int		ft_verify_exit(t_bin_token *tokens, int print)
{
	int	i;

	if (tokens->args[1] && tokens->args[2])
	{
		if (print)
			ft_putstr_fd("minishell : too many arguments\n", 2);
		return (1);
	}
	if (tokens->args[1])
	{
		i = 0;
		while (tokens->args[1][i])
		{
			if (!ft_isdigit(tokens->args[1][i])
				&& tokens->args[1][i] != '+'
				&& tokens->args[1][i] != '-')
			{
				if (print)
					ft_putstr_fd("minishell : numeric argument required\n", 2);
				return (2);
			}
			i++;
		}
	}
	return (0);
}

void	ft_exit(t_data *data, t_bin_token *tokens, int	i)
{
	int	status;

	if (!ft_verify_exit(tokens, 1))
	{
		if (tokens->args[1])
		{
			status = ft_atoi(tokens->args[1]);
		}
		else
			status = 0;
	}
	else
		status = ft_verify_exit(tokens, 0);
	ft_free(status, NULL, data, i);
}
