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

#include "ft_data_init.h"

char	*ft_get_hostname(void)
{
	char	*hostname;
	char	*tmp;
	int		fd;
	int		i;

	fd = open("/etc/hostname", O_RDONLY);
	tmp = get_next_line(fd);
	get_next_line(fd);
	if (!tmp)
		return (NULL);
	close(fd);
	i = 0;
	while (tmp[i] != '\0' && tmp[i] != '.')
		i++;
	hostname = ft_substr(tmp, 0, i);
	free(tmp);
	return (hostname);
}

char	*ft_heredoc_path(t_data *data)
{
	if (data->user)
	{
		data->heredoc_path = ft_strdup("/home/");
		data->heredoc_path = ft_strjoin_gnl(data->heredoc_path, data->user);
		data->heredoc_path = ft_strjoin_gnl(data->heredoc_path, "/");
	}
	else
		data->heredoc_path = ft_strdup("/.tmp");
	return (data->heredoc_path);
}

t_envp	*ft_new_env_node(char *envp)
{
	t_envp	*new;
	size_t	tmp;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	tmp = ft_strchr_len(envp, '=');
	if (tmp)
	{
		new->key = ft_substr(envp, 0, tmp);
		new->value = ft_strdup(&envp[tmp + 1]);
		new->print = true;
	}
	else
	{
		new->key = ft_strdup(envp);
		new->value = NULL;
		new->print = false;
	}
	new->next = NULL;
	return (new);
}

void	ft_envlist_init(t_data *data, char **env)
{
	t_envp	*envp;
	t_envp	*head;
	t_envp	*last;
	int		i;

	i = 0;
	head = NULL;
	last = NULL;
	while (env[i])
	{
		envp = ft_new_env_node(env[i++]);
		if (!envp) 
		{
			perror("Failed to allocate memory for envp");
			//free
			//data->envp = NULL;
			exit(EXIT_FAILURE);
		}
		if (!head)
			head = envp;
		else
			last->next = envp;
		last = envp;
		envp->next = ft_new_env_node(data, env[i]);
		envp = envp->next;
	}
	data->envp = head;
}

t_data	*ft_data_init(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->tokens = NULL;
	data->tokens_start = NULL;
	data->bin_tokens = NULL;
	data->command = NULL;
	data->args = NULL;
	data->prompt = NULL;
	data->ft_envp = NULL;
	data->user = NULL;
	data->exit_status = 0;
	data->user = getenv("USER");
	data->hostname = ft_get_hostname();
	data->path = ft_get_path(data);
	if (data->user && data->path && data->hostname)
	{
		ft_envlist_init(data, envp);
		ft_prompt_init(data);
	}
	else
		data->prompt = ft_strdup("minishell(prompt not found😡):");
	data->bin_tokens = NULL;
	data->heredoc_path = ft_heredoc_path(data);
	return (data);
}
