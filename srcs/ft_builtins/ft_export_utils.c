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

#include "ft_builtins.h"

int	ft_check_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i])
			&& key[i] != '_' && key[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

int	ft_error_msg_export(char *args)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(args, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
}

void	ft_free_key_value(char **key, char **value)
{
	if (*key)
	{
		free(*key);
		*key = NULL;
	}
	if (*value)
	{
		free(*value);
		*value = NULL;
	}
}

char	*ft_export_get_value(t_bin_token *token, int i, size_t tmp)
{
	if (tmp != ft_strlen(token->args[i]))
		return (ft_substr(token->args[i],
				ft_strchr_len(token->args[i], '=') + 1,
				ft_strlen(token->args[i])));
	else
		return (NULL);
}

int	ft_export_loop(t_data *data, t_bin_token *token)
{
	int		i;
	int		status;
	size_t	tmp;
	int		tmp_status;

	i = 0;
	status = 0;
	while (token->args[++i])
	{
		tmp = ft_strchr_len(token->args[i], '=');
		if (token->args[i][tmp - 1] == '+')
		{
			tmp_status = ft_export_append(data, token, tmp, i);
			if (!status && tmp_status)
				status = tmp_status;
		}
		else
		{
			tmp_status = ft_export_simple(data, token, tmp, i);
			if (!status && tmp_status)
				status = tmp_status;
		}
	}
	return (status);
}
