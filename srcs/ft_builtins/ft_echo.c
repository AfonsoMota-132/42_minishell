/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:55:33 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/24 18:58:45 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <unistd.h>

static int	ft_flag_check( t_bin_token *token)
{
	int	n;
	int	i;

	n = 1;
	while (token->args[n])
	{
		i = 0;
		if (token->args[n][i] == '-' && i == 0)
		{
			i++;
			while (token->args[n][i] == 'n')
				i++;
			if (token->args[n][i] != '\0' && n != 1)
				return(n);
		}
		else
			break ;
		n++;
	}
		return(n);
}	
void	ft_echo(t_data *data, t_bin_token *token)
{
	int	n;
	int	flag;
(void)data;

	n = 1;
	flag = 1;
	if (ft_flag_check(token) != 1)
	{
		flag = ft_flag_check(token);
		n = flag;
	}
	while (token->args[n])
	{
		ft_putstr_fd(token->args[n], STDOUT_FILENO);
		if (token->args[n + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		n++;
	}
	if (flag == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	ft_free(0, NULL, data, 0);
}

