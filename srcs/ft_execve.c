/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 09:55:15 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/02 09:57:24 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_exec_init(t_data **data)
{
	path = ft_get_path((*data)->envp);
	(*data)->args = ft_split((*data)->command, ' ');
	(*data)->envp = (*data)->envp, '\n');
	ft_execve((*data)->args[0], (*data)->args, (*data)->envp);
}

void	ft_execve(char *path, char **argv, char **envp)
{
	int idk = execve(path, argv, envp);
	printf("idk: %i\n", idk);
}
