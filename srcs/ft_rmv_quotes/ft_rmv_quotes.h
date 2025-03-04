/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmv_quotes.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:13:30 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 15:14:11 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RMV_QUOTES_H
# define FT_RMV_QUOTES_H

# ifndef MINISHELL_H
#  include "../../incs/minishell.h"
# endif

int		ft_quote_rm_len(char const *s, char quote);
char	*ft_rmv_single_quotes(char *str, int *start);
char	*ft_rmv_double_quotes(char *str, int *start);
void	ft_empty_quotes(t_token *tokens, int i);
void	ft_rmv_quotes(t_token *tokens);

#endif
