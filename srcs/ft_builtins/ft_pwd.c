/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:49:07 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/28 11:07:59 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

int	ft_verify_pwd(t_bin_token *tokens, int print)
{
	int	i;

	i = 0;
	while (tokens->args[++i])
	{
		if (tokens->args[1][0] == '-' && print)
			return (ft_putstr_fd("Minishell: pwd: illegal option\n", 2), 1);
	}
	return (0);
}

int	ft_pwd2(t_data *data, char *path, int exit)
{
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	free(path);
	if (exit)
		ft_free(0, NULL, data, 0);
	return (0);
}

int	ft_pwd(t_data *data, t_bin_token *tokens, int exit)
{
	char	*path;

	path = ft_calloc(sizeof(char), 4096);
	if (ft_verify_pwd(tokens, 1))
	{
		free(path);
		if (exit)
			ft_free(exit, NULL, data, 0);
		return (1);
	}
	if (getcwd(path, 4096) && !ft_pwd2(data, path, exit))
		return (0);
	else
	{
		free(path);
		if (exit)
			ft_free(1, NULL, data, 0);
		return (ft_putstr_fd("Minishell: pwd error\n", 2), 1);
	}
}
