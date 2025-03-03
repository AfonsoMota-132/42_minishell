/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:10:24 by palexand          #+#    #+#             */
/*   Updated: 2025/03/03 23:32:44 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../incs/minishell.h"
#include "ft_builtins.h"

int ft_check_key(char *key)
{
	int i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void ft_export_loop(t_data *data, t_bin_token *token)
{
	int i;
	
	i = 0;
	while (token->args[++i])
	{
		if (ft_check_key(token->args[i]))
		{
			if (ft_find_key(data, token->args[i]))
			{
				printf("found key\n data->envp->key: %s\n", data->envp->key);
				printf("token->args[i + 1]: %s\n", token->args[i + 1]);
				ft_replace_env(data, token->args[i + 1]);
			}
			else
				ft_add_env(data, token->args[i], NULL);
		}
		else
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(token->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		}
	}
}
