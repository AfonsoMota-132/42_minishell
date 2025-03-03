/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:28:26 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 15:29:46 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FREE_H
# define FT_FREE_H

# ifndef MINISHELL_H
#  include "../../incs/minishell.h"
# endif

//		ft_free		//

void	ft_free_matrix(char **matrix);
void	ft_free_env(t_envp *env);
void	ft_free_tokens(t_token *tokens, int del_heredoc);
void	ft_free_tree(t_bin_token *tokens, int del_heredoc);
int		ft_free(int i, char *command, t_data *data, int del_heredoc);

#endif
