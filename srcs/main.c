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

int main(void)
{
	char	*command;

	while (1)
	{
		command = ft_readline("Minishell:	");
		ft_printf("%s\n", command);
		if (ft_strncmp(command, "no", 2) == 0)
		{
			free(command);
			break ;
		}
		free(command);
	}
}
