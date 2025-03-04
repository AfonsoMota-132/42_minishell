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

#include "ft_builtins.h"

int	ft_replace_env(t_data	*data, char *key, char *value)
{
	int		i;
	t_envp	*tmp;

	i = 0;
	tmp = data->envp;
	while (tmp && ft_strcmp(tmp->key, key) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (0);
	if (value)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
		tmp->print = true;
	}
	else
	{
		free(tmp->value);
		tmp->value = NULL;
		tmp->print = true;
	}
	return (1);
}

void	ft_change_env(t_data	*data, char *key, char *dir)
{
	char	*new_value;

	new_value = ft_strdup(dir);
	if (!new_value)
	{
		ft_putstr_fd("Failed to allocate memory for new_value\n", 2);
		return ;
	}
	ft_replace_env(data, key, new_value);
	free(new_value);
}

void	ft_add_env(t_data	*data, char *key, char *value)
{
	t_envp	*new;
	t_envp	*tmp;

	tmp = data->envp;
	new = malloc(sizeof(t_envp));
	new->key = ft_strdup(key);
	if (!new)
	{
		ft_putstr_fd("Failed to allocate memory for new\n", 2);
		return ;
	}
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->print = true;

	while (!tmp)
	{
		new->next = NULL;
		data->envp = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}

int	ft_update_pwd(t_data *data, char *last_path)
{
	char	pwd[PATH_MAX];
	char	*current_pwd;
	t_envp	*found;
	
	current_pwd = getcwd(pwd, PATH_MAX);
	if (current_pwd == NULL)
		return (ft_putstr_fd("getcwd error\n", 2), -1);
	found = ft_find_key(data, "OLDPWD");
	if (found)
		ft_change_env(data, "OLDPWD", found->value);
	else
		ft_add_env(data, "OLDPWD", last_path);
	found = ft_find_key(data, "PWD");
	if (found)
		ft_change_env(data, "PWD", current_pwd);
	else
		ft_add_env(data, "PWD", current_pwd);
	return (1);
}


t_envp	*ft_find_key(t_data *data, char *key)
{
	t_envp	*envp;

	envp = data->envp;
	while (envp)
	{
		if (ft_strcmp(envp->key, key) == 0)
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}


int	ft_go_to_path(t_data *data, int option, char *last_path)
{
	char	*path;
	int	return_value;

	if (option == 0)
	{
		path = ft_getenv("HOME", data);
		return_value = chdir(path);
		ft_update_pwd(data, last_path);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		return (return_value);
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

int	ft_cd(t_data *data, t_bin_token *token, int exit)
{
	int		return_value;
	char	*last_path;
	char	cwd[PATH_MAX];

	last_path = getcwd(cwd, sizeof(cwd));
	if (token->args[1] && token->args[2])
	{
		ft_putstr_fd("cd : too many arguments\n", 2);
		if (exit == 1)
			ft_free(1, NULL, data, 0);
		return (1);
	}
	if (!token->args[1])	
	{
		return_value = ft_go_to_path(data, 0, last_path);
		if (exit == 1)
			ft_free(return_value, NULL, data, 0);
		return (return_value);
	}
	else if (ft_strcmp(token->args[1], "-") == 0)
		return_value = ft_go_to_path(data, 1, last_path);
	else
	{
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
	}
	if (exit == 1)
		ft_free(return_value, NULL, data, 0);
	return (return_value);
}
