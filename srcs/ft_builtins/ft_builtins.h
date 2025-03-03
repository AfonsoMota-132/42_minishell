/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:16:27 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:19:01 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

# ifndef MINISHELL_H
#  include "../../incs/minishell.h"
# endif

int	ft_echo(t_data *data, t_bin_token *token, int exit);
int	ft_pwd(t_data *data, t_bin_token *tokens, int exit);
int	ft_exit(t_data *data, t_bin_token *tokens, int exit);

#endif
