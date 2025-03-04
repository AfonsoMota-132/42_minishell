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

int	ft_export_loop(t_data *data, t_bin_token *token)
{
	int i;
	int		status;
	size_t tmp;
	char	*key;
	char	*value;
	
	i = 0;
	status = 0;
	while (token->args[++i])
	{
		tmp = ft_strchr_len(token->args[i], '=');
		key = ft_substr(token->args[i], 0, tmp);
		if (tmp != ft_strlen(token->args[i]))
			value = ft_substr(token->args[i], ft_strchr_len(token->args[i], '=') + 1, ft_strlen(token->args[i]));
		else
			value = NULL;
		if (ft_check_key(key))
		{
			if (ft_find_key(data, key))
			{
				ft_replace_env(data, key, value);
			}
			else
				ft_add_env(data, key, value);
		}
		else
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(token->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			status = 1;
		}
		if (key)
			free(key);
		if (value)
			free(value); 
	}
	return (status);
}
