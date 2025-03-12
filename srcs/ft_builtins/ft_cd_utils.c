/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:53:53 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/06 09:54:38 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"

int	ft_update_pwd(t_data *data, char *last_path)
{
	char	pwd[PATH_MAX];
	char	*current_pwd;
	t_envp	*found;

	current_pwd = getcwd(pwd, PATH_MAX);
	if (current_pwd == NULL)
		return (-1);
	found = ft_find_key(data, "OLDPWD");
	if (found)
		ft_change_env(data, "OLDPWD", last_path);
	else
		ft_add_env(data, "OLDPWD", last_path);
	found = ft_find_key(data, "PWD");
	if (found)
		ft_change_env(data, "PWD", current_pwd);
	else
		ft_add_env(data, "PWD", current_pwd);
	return (1);
}

void	ft_print_path_minus(char *path, t_bin_token *tokens)
{
	int	fd;

	if (tokens->redir_out && tokens->redir_out->type == FILENAME)
	{
		fd = open(tokens->redir_out->content, O_WRONLY | O_APPEND, 0);
		ft_putstr_fd(path, fd);
		ft_putstr_fd("\n", fd);
		close (fd);
	}
	else
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
}

int	ft_go_to_path(t_data *data, int option, char *last_path, t_bin_token *token)
{
	char	*path;
	int		return_value;

	path = NULL;
	if (option == 0)
	{
		path = ft_strdup(ft_getenv("HOME", data));
		return_value = chdir(path);
		ft_update_pwd(data, last_path);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 2);
		return (free(path), return_value);
	}
	if (option == 1)
	{
		path = ft_strdup(ft_getenv("OLDPWD", data));
		ft_print_path_minus(path, token);
		ft_update_pwd(data, last_path);
		if (!path)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 2);
	}
	return_value = chdir(path);
	free (path);
	return (return_value);
}

int	ft_cd_return_value(t_bin_token *token, t_data *data, char *last_path)
{
	int	return_value;

	return_value = chdir(token->args[1]);
	ft_update_pwd(data, last_path);
	if (return_value < 0)
		return_value *= -1;
	if (return_value != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(token->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (return_value);
}
