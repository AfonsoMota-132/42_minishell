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
#include <fcntl.h>

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

char	*ft_heredoc_path(t_data *data)
{
	data->heredoc_path = ft_strdup("/home/");
	data->heredoc_path = ft_strjoin_gnl(data->heredoc_path, data->user);
	data->heredoc_path = ft_strjoin_gnl(data->heredoc_path, "/");
	return (data->heredoc_path);
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
	data->ft_envp = ft_cpyenv(envp);
	data->user = getenv("USER");
	data->hostname = ft_get_hostname();
	data->path = ft_get_path(data);
	data->prompt = NULL;
	ft_prompt_init(data);
	data->heredoc_path = ft_heredoc_path(data);
	return (data);
}
