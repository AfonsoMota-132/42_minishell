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

void	ft_command_not_found(t_data *data, char *path)
{
	if (ft_strlen(path) == 0)
		printf("\'\' : command not found\n");
	else
		printf("%s: command not found\n", path);
	free(path);
	ft_free(127, NULL, data, 1);
}

void	ft_error_msg_redir(t_data *data, int type, char *redir, char *path)
{
	if (path)
		free(path);
	if (type == 0)
		printf("bash: %s: permission denied\n", redir);
	else if (type == 1)
		printf("bash: %s: No such file or directory\n", redir);
	ft_free(1, NULL, data, 0);
}
