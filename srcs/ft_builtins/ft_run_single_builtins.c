/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_single_builtins.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:53:15 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/06 11:53:44 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executer.h"

int	ft_run_single_builtins3(t_bin_token *tokens, t_data *data)
{
	int	status;

	status = -1;
	if (ft_strcmp("unset", tokens->args[0]) == 0)
	{
		status = ft_handle_redirects_ne(tokens, NULL);
		if (status == 0)
			status = ft_unset(data, tokens, 0);
		else
			data->exit_status = 1;
	}
	return (status);
}

int	ft_run_single_builtins2(t_bin_token *tokens, t_data *data)
{
	int	status;

	status = -1;
	if (ft_strcmp("cd", tokens->args[0]) == 0)
	{
		status = ft_handle_redirects_ne(tokens, NULL);
		if (status == 0)
			status = ft_cd(data, tokens, 0);
		else
			data->exit_status = 1;
	}
	if (ft_strcmp("export", tokens->args[0]) == 0)
	{
		status = ft_handle_redirects_ne(tokens, NULL);
		if (status == 0)
			status = ft_export(data, tokens, 0);
		else
			data->exit_status = 1;
	}
	return (status);
}

int	ft_run_single_builtins(t_bin_token *tokens, t_data *data)
{
	int	status;

	status = -1;
	if (!tokens->args[0])
		return (0);
	if (ft_strcmp("exit", tokens->args[0]) == 0)
	{
		status = ft_handle_redirects_ne(tokens, NULL);
		if (status == 0)
			status = ft_exit(data, tokens, 0);
		else
			data->exit_status = 1;
	}
	status = ft_run_single_builtins2(tokens, data);
	status = ft_run_single_builtins3(tokens, data);
	if (status == -1)
		return (0);
	data->exit_status = status;
	return (1);
}
