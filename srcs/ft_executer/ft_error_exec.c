/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:21:10 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/25 22:22:23 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executer.h"

void	ft_command_not_found2(t_data *data, char *path)
{
	if (access(path, F_OK) == -1 && (path[0] == '/' || path [0] == '~'
			|| (path[0] == '.' && path[1] == '/')))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
	}
	if (access(path, X_OK) == -1 && (path[0] == '/' || path [0] == '~'
			|| (path[0] == '.' && path[1] == '/')))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" : Permission denied\n", 2);
		free(path);
		ft_free(126, NULL, data, 1);
	}
	if (ft_strlen(path) == 0)
	{
		ft_putstr_fd("\'\' : command not found\n", 2);
	}
	else
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" : command not found\n", 2);
	}
}

void	ft_command_not_found(t_data *data, char *path, char **array)
{
	DIR	*dir;

	dir = opendir(path);
	if (array)
		ft_free_matrix(array);
	if (dir)
	{
		closedir(dir);
		if (path[0] == '/' || path [0] == '~'
			|| (path[0] == '.' && path[1] == '/'))
		{
			ft_putstr_fd("\"", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd("\": Is a directory\n", 2);
			free(path);
			ft_free(126, NULL, data, 1);
		}
	}
	ft_command_not_found2(data, path);
	free(path);
	ft_free(127, NULL, data, 1);
}

void	ft_error_msg_redir(t_data *data, int type, char *redir, char *path)
{
	if (path)
		free(path);
	if (type == 0)
	{
		ft_putstr_fd(redir, 2);
		ft_putstr_fd(" : Permission denied\n", 2);
	}
	else if (type == 1)
	{
		ft_putstr_fd(redir, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
	}
	ft_free(1, NULL, data, 0);
}
