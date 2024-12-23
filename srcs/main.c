/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:39:29 by afogonca          #+#    #+#             */
/*   Updated: 2024/12/17 20:40:20 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		ft_split_cmds_len(char *command)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (command[++i])
	{
		if (j == 0 && command[i] != ' ' && command[i] != '\t')
		{
			j = 1;
			i++;
		}
		while (command[i] != ' ' && command[i] != '\t'
			&& command[i] && command[i] != '|' && command[i] != '<'
			&& command[i] != '>')
			i++;
		if (command[i] == '|' && ++i)
			j++;
		if (command[i] == '<' && ++i)
		{
			if (command[i] == '<')
				i++;
			j++;
		}
		if (command[i] == '>' && ++i)
		{
			if (command[i] == '>')
				i++;
			j++;
		}
		if (j && command[i])
			j++;
	}
	return (j);
}

char	**ft_split_cmds(char *command)
{
	int		i;
	int		j;
	char	**commands;

	i = 0;
	j = 0;
	commands = NULL;	
	printf("size: %i\n", ft_split_cmds_len(command));
	/*commands = ft_calloc(j + 1, sizeof(char *));*/
	if (!commands)
		return (NULL);
	return (commands);
}

int main(void)
{
	char	*command;
	char	**commands;

	while (1)
	{
		command = readline("Minishell: ");
		if (ft_strncmp(command, "exit", 4) == 0)
			return (0);
		commands = ft_split_cmds(command);
		ft_printf("commands: %s\n", command);
	}
}
