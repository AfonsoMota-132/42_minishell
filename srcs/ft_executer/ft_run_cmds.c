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
	int	child_pid;
	int	fd[2];

	if (!data->bin_tokens->right && !data->bin_tokens->left)
	{
		if (pipe(fd) == -1)
			printf("error creating pipe\n");
		else
		{
			child_pid = fork();
			if (child_pid == 0)
				ft_execve(data, data->bin_tokens);
			waitpid(-1, &status, 0);
			data->exit_status = WEXITSTATUS(status);
			close(fd[0]);
			close(fd[1]);
		}
	}
	else
		ft_pipes_creator(data, data->bin_tokens);

}
