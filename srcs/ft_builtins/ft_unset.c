#include "ft_builtins.h"

int	ft_unset(t_data *data, t_bin_token *token, bool exit_nbr)
{
	int	i;

	i = 1;
	while (token->args[i])
	{
		if (ft_strcmp(data->envp->key, token->args[i]))
		{
			ft_unsetenv(data, token->args[i]);
		}
		if (ft_unsetenv(data, token->args[i]) == false)
		{
			ft_putstr_fd("unset: ", STDERR_FILENO);
			ft_putstr_fd(token->args[i], STDERR_FILENO);
			ft_putstr_fd(": not found\n", STDERR_FILENO);
			if (exit_nbr == true)
				exit(0);
		}
		i++;
	}
	return (0);
}

bool	ft_unsetenv(t_data *data, char *token)
{
	t_envp *current;
	t_envp *previous;
	t_envp *tmp;

	if (!data || !data->envp || !token)
		return (false);

	if (ft_strcmp(data->envp->key, token) == 0)
	{
		tmp = data->envp;
		data->envp = data->envp->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	current = data->envp->next;
	previous = data->envp;
	while(current)
	{
		if (ft_strcmp(current->key, token) == 0)
		{
			previous->next = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return (true);
		}
		previous = current;
		current = current->next;
	}
	return (false);
		
}
