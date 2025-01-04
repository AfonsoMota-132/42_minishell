/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 09:07:39 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/04 10:42:08 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_free_matrix(char **matrix)
{
	int		i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

char	*ft_get_path(char *user)
{
	char	*path;
	char	**dirs;
	int		i;

	path = getcwd(NULL, 0);
	dirs = ft_split(path, '/');
	if (!dirs)
		return (NULL);
	free(path);
	i = 0;
	if (ft_strcmp(dirs[i], "home") == 0
		&& ft_strlen(dirs[i]) == 4 && ++i
		&& ft_strcmp(dirs[i], user) == 0
		&& ft_strlen(dirs[i]) == ft_strlen(user))
		path = ft_strdup("~");
	while (dirs[++i])
	{
		if (!path)
			path = ft_strjoin(path, "/");
		else
			path = ft_strjoin_gnl(path, "/");
		path = ft_strjoin_gnl(path, dirs[i]);
	}
	ft_free_matrix(dirs);
	return (path);
}

t_data	*ft_data_init(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->tokens = NULL;
	data->tokens_start = NULL;
	data->command = NULL;
	data->args = NULL;
	data->envp = NULL;
	data->user = getenv("USER");
	data->path = ft_get_path(data->user);
	data->prompt =	ft_strjoin_gnl(ft_strjoin_gnl(ft_strjoin(data->user, ":"),
						data->path), "$> "); 
	return (data);
}
