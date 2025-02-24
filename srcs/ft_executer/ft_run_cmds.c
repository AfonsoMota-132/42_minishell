/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 05:56:27 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/24 05:58:17 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_run_cmds(t_data *data)
{
	int	status;
	int	pid_c;

	if (!data->bin_tokens->right && !data->bin_tokens->left)
	{
		pid_c = fork();
		if (pid_c == 0)
		{
			raise(SIGINT);
			raise(127);
			ft_pipes_creator(data, data->bin_tokens);
			ft_execve(data, data->bin_tokens);
			exit(0);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(127, SIG_IGN);
			waitpid(-1, &status, 0);
			if (WIFEXITED(status))
			{
				data->exit_status = WEXITSTATUS(status);
				printf("data->exit_status: %i\n", data->exit_status);
			}
			ft_signals();
		}
	}
	else
		ft_pipes_creator(data, data->bin_tokens);

}
