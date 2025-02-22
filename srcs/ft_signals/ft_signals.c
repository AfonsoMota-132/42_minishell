/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:09:56 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/18 12:18:00 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

extern int	signal_received;

void	ft_signals_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		signal_received = 130;
	}
}

void	ft_signals(void)
{
	signal(SIGINT, ft_signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
