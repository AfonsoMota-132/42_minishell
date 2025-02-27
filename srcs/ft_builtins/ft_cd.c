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

int	ft_replace_env(t_data	*data, char *value)
{
	int		i;

	i = 0;
	while (value[i] != '=')
		i++;
	if (value[i] == '=' && value[i + 1] != '\0')
	{
		free(data->envp->value);
		data->envp->value = ft_strdup(value + i + 1);
		data->envp->print = true;
	}
	else
	{
		free(data->envp->value);
		data->envp->value = NULL;
		data->envp->print = true;
	}
	return (1);
}

void	ft_change_env(t_data	*data, char *key, char *dir)
{
	char	*new_value;

	if (dir)
		new_value = ft_strjoin(key, dir);
	else
		new_value = ft_strdup(key);
	if (!new_value)
	{
		ft_putstr_fd("Failed to allocate memory for new_value\n", 2);
		return ;
	}
	ft_replace_env(data, new_value);
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
	new->value = ft_strdup(value);
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
	if (found) {
		ft_change_env(data, "OLDPWD=", found->value);
	}
	else
		ft_add_env(data, "OLDPWD=", last_path);
	found = ft_find_key(data, "PWD");
	if (found)
		ft_change_env(data, "PWD=", current_pwd);
	else
		ft_add_env(data, "PWD=", current_pwd);
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
		ft_update_pwd(data, last_path);
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
	char	*last_path;
	char	cwd[PATH_MAX];

	last_path = getcwd(cwd, sizeof(cwd));
	if (!token->args[1])
		return(ft_go_to_path(data, 0, last_path));
	else if (ft_strcmp(token->args[1], "..") == 0)
		return_value = ft_go_to_path(data, 1, last_path);
	else
	{
		ft_update_pwd(data, last_path);
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
