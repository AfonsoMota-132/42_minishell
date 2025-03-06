/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:11:12 by palexand          #+#    #+#             */
/*   Updated: 2025/03/03 23:11:13 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include <unistd.h>

void	ft_print_envp(t_data *data)
{
	t_envp	*envp;

	envp = data->envp;
	while (envp)
	{
		if (envp->key && envp->value)
		{
			ft_putstr_fd(envp->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(envp->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		envp = envp->next;
	}
}
