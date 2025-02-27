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

#include "../incs/minishell.h"

char	*ft_getenv(char *env, t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
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
