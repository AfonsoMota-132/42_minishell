/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:28:29 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/06 10:28:31 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

int	ft_unset(t_data *data, t_bin_token *token, bool exit_nbr)
{
	int	i;

	i = 1;
	while (token->args[i])
	{
		if (ft_strcmp(data->envp->key, token->args[i]))
		{
			ft_unsetenv(data, token->args[i]);
		}
		if (ft_unsetenv(data, token->args[i]) == false)
			if (exit_nbr == true)
				exit(0);
		i++;
	}
	return (0);
}

int	ft_unsetenv_first(t_data *data, char *token)
{
	t_envp	*tmp;

	if (ft_strcmp(data->envp->key, token) == 0)
	{
		tmp = data->envp;
		data->envp = data->envp->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		return (1);
	}
	else
		return (0);
}

bool	ft_unsetenv(t_data *data, char *token)
{
	t_envp	*current;
	t_envp	*previous;

	if (!data || !data->envp || !token)
		return (false);
	if (ft_unsetenv_first(data, token) == 1)
		return (true);
	current = data->envp->next;
	previous = data->envp;
	while (current)
	{
		if (ft_strcmp(current->key, token) == 0)
		{
			previous->next = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return (true);
		}
		previous = current;
		current = current->next;
	}
	return (false);
}
