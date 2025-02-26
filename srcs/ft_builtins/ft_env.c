/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:01:09 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/28 14:03:32 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_envlist_init(t_data *data, char **env)
{
	t_envp	*envp;
	t_envp	*last;
	t_envp	*head;
	int		i;

	i = 0;
	while (env[i++])
	{
		envp = ft_new_env_node(data, env[i]);
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
	}
	data->envp = head;
}


t_envp	*ft_new_env_node(t_data *data, char *envp)
{
	t_envp	*new;
	char	*tmp;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	tmp = ft_strchr(envp, '=');
	if (tmp)
	{
		new->key = ft_substr(envp, 0, tmp - envp);
		new->value = ft_strdup(tmp + 1);
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
