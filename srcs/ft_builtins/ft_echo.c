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

void	ft_echo(t_data *data, t_bin_token *token)
{
	int	n;
(void)data;

	n = 1;
	if (token->args[1] && ft_strcmp(token->args[1], "-n") == 0)
		n = 2;
	while (token->args[n])
	{
		ft_putstr_fd(token->args[n], 1);
		if (token->args[n + 1])
			ft_putstr_fd(" ", 1);
		n++;
	}
	if (n == 1)
		ft_putstr_fd("\n", 1);
}
