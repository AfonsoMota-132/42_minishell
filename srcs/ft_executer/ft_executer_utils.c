/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:38:05 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/07 09:38:58 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executer.h"

char	**ft_envp_list2array(t_envp *env)
{
	char	**array;
	t_envp	*tmp;
	int		i;

	tmp = env;
	i = 0;
	if (!env)
		return (NULL);
	while (tmp && ++i)
		tmp = tmp->next;
	array = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	tmp = env;
	while (tmp)
	{
		array[i] = ft_strdup(tmp->key);
		if (tmp->value)
			array[i] = ft_strjoin_gnl(ft_strjoin_gnl(array[i],
						"="), tmp->value);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	*ft_execve_get_path(char *cmd, t_data *data)
{
	int		i;
	char	**paths;
	char	*tmp;

	tmp = ft_getenv("PATH", data);
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	i = -1;
	while (ft_strlen(cmd) && paths[++i])
	{
		paths[i] = ft_strjoin_gnl(paths[i], "/");
		paths[i] = ft_strjoin_gnl(paths[i], cmd);
		if (access(paths[i], F_OK) != -1)
		{
			tmp = ft_strdup(paths[i]);
			ft_free_matrix(paths);
			return (tmp);
		}
	}
	ft_free_matrix(paths);
	return (NULL);
}
