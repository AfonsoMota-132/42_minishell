/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:27:02 by palexand          #+#    #+#             */
/*   Updated: 2025/02/24 20:18:32 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
static int	ft_update_pwd(t_data *data)
{
	(void)data;
	char	pwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (1);
	if (!(oldpwd = ft_strjoin("OLDPWD", pwd)))
		return (1);
	/*if (ft_is_in_env("OLDPWD", data))*/
	/*	ft_change_env("OLDPWD", oldpwd, data);*/
	/*else*/
	/*	ft_add_env("OLDPWD", oldpwd, data);*/
	// export oldpwd
	//
	return (0);
}

static int	ft_go_to_path(t_data *data, int option)
{
	char	*path;
	int	return_value;

	if (option == 0)
	{
		ft_update_pwd(data);
		path = ft_getenv("HOME", data);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	if (option == 1)
	{
		path = ft_getenv("OLDPWD", data);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
	}
	return_value = chdir(path);
	return (return_value);
}

int	ft_cd(t_data *data, t_bin_token *token)
{
	int		return_value;

	if (!token->args[1])
		return(ft_go_to_path(data, 0));
	else if (ft_strcmp(token->args[1], "-") == 0)
		return_value = ft_go_to_path(data, 1);
	else
	{
		ft_update_pwd(data);
		printf("pwd: %s\n", ft_getenv("PWD", data));
		return_value = chdir(token->args[1]);
		if (return_value < 0)
			return_value *= -1;	
		if (return_value != 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(token->args[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
	}
	return(ft_free(return_value, NULL, data, 0), 0);
}
