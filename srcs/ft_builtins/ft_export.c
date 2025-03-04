/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:10:25 by palexand          #+#    #+#             */
/*   Updated: 2025/03/03 23:15:29 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

int	ft_export(t_data *data, t_bin_token *token, int	exit)
{
	int		status;	
	if (!token->args[1])
	{
		if (!exit)
			return (-1);
		ft_sort_envp(data);
		ft_print_export(data);
		if (exit)
			ft_free(0, NULL, data, 0);
		return (0);
	}
	if (token->args[1][0] == '-' && token->args[1][1])
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(token->args[1], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		if (exit)
			ft_free(1, NULL, data, 0);
		return (1);
	}
	status = ft_export_loop(data, token);
	if (exit)
		ft_free(status, NULL, data, 0);
	return (status);
}

void	ft_print_export(t_data *data)
{
	t_envp	*envp;

	envp = data->ft_envp;
	while (envp)
	{
		if (envp->key)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(envp->key, STDOUT_FILENO);
			if (envp->value)
			{
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putchar_fd('"', STDOUT_FILENO);
				ft_putstr_fd(envp->value, STDOUT_FILENO);
				ft_putchar_fd('"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		envp = envp->next;
	}
	
}

int	ft_size_struct(t_envp *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		i++;
		envp = envp->next;
	}
	return (i);
}

void	ft_sort_envp(t_data *data)
{
	int	length;
	int	i;
	t_envp	*tmp;

	length = ft_size_struct(data->ft_envp);
	
	while(length > 0)
	{
		tmp = data->ft_envp;
		i = 0;
		while (i < length - 1)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				ft_swap_envp(tmp, tmp->next);
			}
			tmp = tmp->next;
			i++;
		}
		length--;
	}
}

void	ft_swap_envp(t_envp *first, t_envp *second)
{
	char	*key;
	char	*value;

	key = first->key;
	value = first->value;
	first->key = second->key;
	first->value = second->value;
	second->key = key;
	second->value = value;

}
