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
	int	i;

	i = -1;
	if (!env || !env[0])
		return (NULL);
	while (data->ft_envp[++i])
	{
		if (ft_strncmp(data->ft_envp[i], env, ft_strlen(env)) == 0
			&& data->ft_envp[i][ft_strlen(env)] == '=')
			return (&data->ft_envp[i][ft_strlen(env) + 1]);
	}
	return (NULL);
}
