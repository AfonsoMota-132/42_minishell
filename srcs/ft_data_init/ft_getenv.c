/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:33:35 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/27 09:36:38 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_data_init.h"

char	*ft_getenv(char *env, t_data *data)
{
	t_envp	*tmp;

	tmp = data->ft_envp;
	if (!env || !env[0])
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, env, ft_strlen(env) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
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
