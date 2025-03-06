/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:59:20 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/13 10:00:08 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_data_init.h"

char	*ft_get_path_with_til(char *path, char **dirs, int i)
{
	path = ft_strdup("~");
	while (dirs[++i])
	{
		if (!path)
			path = ft_strjoin(path, "/");
		else
			path = ft_strjoin_gnl(path, "/");
		path = ft_strjoin_gnl(path, dirs[i]);
	}
	return (path);
}

char	*ft_get_path_without_til(char *path, char **dirs, int i)
{
	i = -1;
	path = ft_strdup("/");
	while (dirs[++i])
	{
		if (!dirs)
			break ;
		path = ft_strjoin_gnl(path, dirs[i]);
		path = ft_strjoin_gnl(path, "/");
	}
	return (path);
}

char	*ft_get_path(t_data *data)
{
	char	*path;
	char	**dirs;
	int		i;

	path = getcwd(NULL, 0);
	if (!path)
		return (NULL);
	dirs = ft_split(path, '/');
	free(path);
	path = NULL;
	if (!dirs)
		return (NULL);
	i = 0;
	if (dirs[i] && data->user && ft_strncmp(dirs[i], "home", 4) == 0
		&& ft_strlen(dirs[i]) == 4 && ++i && dirs[i]
		&& ft_strncmp(dirs[i], data->user, ft_strlen(data->user)) == 0
		&& ft_strlen(dirs[i]) == ft_strlen(data->user))
		path = ft_get_path_with_til(path, dirs, i);
	else
		path = ft_get_path_without_til(path, dirs, i);
	ft_free_matrix(dirs);
	return (path);
}

void	ft_prompt_init(t_data *data)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->path)
	{
		free(data->path);
		data->path = ft_get_path(data);
		if (!data->path)
			data->path = ft_strdup("unknown_path");
		if (!data->user)
			data->user = ft_strdup("unknown_user");
		if (!data->hostname)
			data->hostname = ft_strdup("unknown_hostname");
		data->prompt = ft_strjoin(data->user, "@");
		data->prompt = ft_strjoin_gnl(data->prompt, data->hostname);
		data->prompt = ft_strjoin_gnl(data->prompt, ":");
		data->prompt = ft_strjoin_gnl(data->prompt, data->path);
		data->prompt = ft_strjoin_gnl(data->prompt, "$ ");
	}
}
