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

int	ft_replace_env(t_data *data, char *key, char *value)
{
	t_envp	*tmp;

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
		return ;
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

int	ft_cd(t_data *data, t_bin_token *token, int exit)
{
	int		return_value;
	char	*last_path;
	char	cwd[PATH_MAX];

	last_path = getcwd(cwd, sizeof(cwd));
	if (token->args[1] && token->args[2])
		return (ft_putstr_fd("cd : too many arguments\n", 2),
			(exit && ft_free(1, NULL, data, 0)), 1);
	if (!token->args[1])
		return ((exit && ft_free(ft_go_to_path(data, 0, last_path),
					NULL, data, 0)), ft_go_to_path(data, 0, last_path));
	else if (ft_strcmp(token->args[1], "-") == 0)
		return_value = ft_go_to_path(data, 1, last_path);
	else
		return_value = ft_cd_return_value(token, data, last_path);
	return ((exit && ft_free(return_value, NULL, data, 0)),
		return_value);
}
