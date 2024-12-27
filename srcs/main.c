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

void	ft_skip_sep(char *command, int *i)
{
	while (command[(*i)] == ' ' && command[(*i)] == '\t'
		&& command[(*i)])
		(*i)++;
}

void	ft_skip_non_seps(char *command, int *i)
{
	while (command[(*i)] != ' ' && command[(*i)] != '\t'
		&& command[(*i)] && command[(*i)] != '|' && command[(*i)] != '<'
		&& command[(*i)] != '>' && command[(*i)] != '\'' && command[(*i)] != '"')
		(*i)++;
}

int	ft_check_quote(char *command, int *i, int *j)
{
	char	quote;

	quote = 0;
	if (command[(*i)] == '"' || command[(*i)] == '\'')
	{
		(*j)++;
		while (command[(*i)] != ' ' && command[(*i)] != '\t'
			&& command[(*i)] && command[(*i)] != '|' && command[(*i)] != '<'
			&& command[(*i)] != '>')
		{
			quote = command[(*i)++];
			while (command[(*i)] != quote && command[(*i)])
				(*i)++;
			(*i)++;
			if (command[(*i)] == ' ' || !command[(*i)])
				break ;
		}
	}
	return (quote);
}

void	ft_first_check(char *command, int *i, int *j)
{
	if (!(*j) && command[*i] != ' ' && command[*i] != '\t')
	{
		ft_check_quote(command, i, j);
		ft_skip_non_seps(command, i);
		ft_check_quote(command, i, j);
		(*j) = 1;
		ft_skip_sep(command, i);
	}
}

void	ft_check_sep(char *command, int *i, int *j)
{
	if (command[(*i)] == '|' && ++(*i))
		(*j)++;
	if (command[(*i)] == '<' && ++(*i))
	{
		if (command[(*i)] == '<')
			(*i)++;
		(*j)++;
	}
	if (command[(*i)] == '>' && ++(*i))
	{
		if (command[(*i)] == '>')
			(*i)++;
		(*j)++;
	}
	if ((*j) && command[(*i)] != '\0' && command[(*i)] != ' ')
	{
		if (ft_check_quote(command, i, j))
			return ;
		(*j)++;
		ft_skip_non_seps(command, i);
		ft_skip_sep(command, i);
	}
}

int		ft_split_cmds_len(char *command)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (command[++i] != '\0')
	{
		ft_skip_sep(command, &i);
		ft_first_check(command, &i, &j);
		ft_check_sep(command, &i, &j);
		if (command[i] == '\0')
			break ;
	}
	return (j);
}

int		ft_seglen(char const *s)
{
	int	i;
	char	quote;

	i = 0;
	if (s[i] == '"' || s[i] == '\'')
	{
		while (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
			i++;
			if (s[i] == ' ' || !s[i])
				break ;
		}
		return (i);
	}
	if (s[i] == '<' || s[i] == '>')
	{
		quote = s[i];
		i++;
		if (s[i] == quote)
			return (2);
		return (1);
	}
	if (s[i] == '|')
		return (1);
	while (s[i] && s[i] != ' '
		&& s[i] != '\t' && s[i] != '|'
		&& s[i] != '<' && s[i] != '>')
		i++;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (i);
}

char	**ft_split_cmds(char *command)
{
	int		i;
	int		j;
	int		k;
	char	**commands;

	i = 0;
	k = -1;
	j = 0;
	commands = NULL;
	j = ft_split_cmds_len(command);
	printf("j: %d\n", j);
	commands = ft_calloc(j + 1, sizeof(char *));
	if (!commands)
		return (NULL);
	while (++k < j)
	{
		printf("seglen i: %i\n", ft_seglen(&command[i]));
		commands[k] = ft_substr(&command[i], 0, ft_seglen(&command[i]));
		i += ft_seglen(&command[i]);
		printf("i: %i\n", i);
	}
	commands[k] = NULL;
	return (commands);
}

void	ft_free_cmds(char **commands)
{
	int	i;

	i = -1;
	while (commands[++i])
		free(commands[i]);
	free(commands);
}

int main(void)
{
	char	*command;
	char	**commands;
	int		i;

	while (1)
	{
		command = readline("Minishell: ");
		i = 0;
		if (ft_strncmp(command, "exit", 4) == 0)
			return (0);
		commands = ft_split_cmds(command);
		while (commands[i])
		{
			ft_printf("%s	%i\n", commands[i], i);
			i++;
		}
		/*ft_free_cmds(commands);*/
		free (command);
	}
}
