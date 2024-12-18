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

char	*ft_split_commands(char *str)
{
	/*char	**commands;*/
	/*int		i;*/
	/*int		j;*/

	str = ft_strtrim(str, " \t");
	ft_printf("%s\n", str);
	return (NULL);
}

int	ft_check_quotes(char *str)
{
	size_t	i;
	size_t	found;
	char	type;

	i = -1;
	found = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			type = str[i];
			found = 1;
			while (str[++i] != '\0')
			{
				if (str[i] == type)
				{
					found = 0;
					break ;
				}
			}
			if (found == 1)
				return (1);
		}
	}
	return (0);
}

int main(void)
{
	char	*command;
	/*t_token	*token;*/

	while (1)
	{
		command = readline("Minishell: ");
		if (ft_check_quotes(command))
			ft_printf("Syntax error. Unbalanced quotes!\n");
		free(command);
	}
}
