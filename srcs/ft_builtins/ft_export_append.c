/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:33:15 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/06 11:43:56 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

void	ft_append_env(t_data	*data, char *key, char *dir)
{
	char	*new_value;

	new_value = ft_strdup(ft_getenv(key, data));
	new_value = ft_strjoin_gnl(new_value, dir);
	if (!new_value)
	{
		ft_putstr_fd("Failed to allocate memory for new_value\n", 2);
		return ;
	}
	ft_replace_env(data, key, new_value);
	free(new_value);
}

int	ft_export_append(t_data *data, t_bin_token *token,
		size_t tmp, int i)
{
	char	*key;
	char	*value;
	int		status;

	status = 0;
	key = ft_substr(token->args[i], 0, tmp - 1);
	value = ft_export_get_value(token, i, tmp);
	if (ft_check_key(key))
	{
		if (ft_find_key(data, key))
			ft_append_env(data, key, value);
		else
			ft_add_env(data, key, value);
	}
	else
		status = ft_error_msg_export(token->args[i]);
	ft_free_key_value(&key, &value);
	return (status);
}

int	ft_export_simple(t_data *data, t_bin_token *token,
		size_t tmp, int i)
{
	char	*key;
	char	*value;
	int		status;

	status = 0;
	key = ft_substr(token->args[i], 0, tmp);
	value = ft_export_get_value(token, i, tmp);
	if (ft_check_key(key))
	{
		if (ft_find_key(data, key))
			ft_replace_env(data, key, value);
		else
			ft_add_env(data, key, value);
	}
	else
		status = ft_error_msg_export(token->args[i]);
	ft_free_key_value(&key, &value);
	return (status);
}
