/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:22:30 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 14:25:40 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNALS_H
# define FT_SIGNALS_H

# include "../../incs/minishell.h"

void	ft_signals_handler(int sig);
void	ft_signals(void);
void	ft_heredoc_signal_handler(int sig);

#endif
