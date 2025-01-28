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

char	*ft_get_path(t_data *data)
{
	char	*path;
	char	**dirs;
	int		i;

	path = getcwd(NULL, 0);
	dirs = ft_split(path, '/');
	free(path);
	if (!dirs)
		return (NULL);
	i = 0;
	if (ft_strncmp(dirs[i], "home", 4) == 0
		&& ft_strlen(dirs[i]) == 4 && ++i
		&& ft_strncmp(dirs[i], data->user, ft_strlen(data->user)) == 0
		&& ft_strlen(dirs[i]) == ft_strlen(data->user))
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

void	ft_prompt_init(t_data *data)
{
	if (data->prompt)
		free(data->prompt);
	data->prompt = ft_strjoin_gnl(ft_strjoin_gnl(ft_strjoin_gnl(ft_strjoin_gnl(
		ft_strjoin(data->user, "@"), data->hostname), ":"), data->path), "$ ");
}

char	*ft_get_hostname(void)
{
	char	*hostname;
	char	*tmp;
	int		fd;
	int		i;

	fd = open("/etc/hostname", O_RDONLY);
	tmp = get_next_line(fd);
	get_next_line(fd);
	close(fd);
	i = 0;
	while (tmp[i] != '\0' && tmp[i] != '.')	
		i++;
	hostname = ft_substr(tmp, 0, i);
	free(tmp);
	return (hostname);
}

char	**ft_cpyenv(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		env[i] = ft_strdup(envp[i]);
	env[i] = NULL;
	return (env);
}

t_data	*ft_data_init(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->tokens = NULL;
	data->tokens_start = NULL;
	data->command = NULL;
	data->args = NULL;
	data->exit_status = 0;
	printf("before\n");
	data->ft_envp = ft_cpyenv(envp);
	data->user = getenv("USER");
	data->hostname = ft_get_hostname();
	data->path = ft_get_path(data);
	printf("after\n");
	data->prompt = NULL;
	ft_prompt_init(data);
	return (data);
}
