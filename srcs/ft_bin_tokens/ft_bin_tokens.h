/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_tokens.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:59:15 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:15:42 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BIN_TOKENS_H
# define FT_BIN_TOKENS_H

# ifndef MINISHELL_H
#  include "../../incs/minishell.h"
# endif

//		ft_update_bin_tokens	//

t_bin_token	*ft_calloc_bin_token(t_bin_token_type type);
t_token		*ft_bin_redir2(t_token **tokens, t_token_type redir_1,
				t_token_type redir_2);
t_token		*ft_bin_redir(t_token **tokens, t_token_type redir_1,
				t_token_type redir_2);
void		ft_update_bin_token2(t_bin_token *bin_token, t_token *tokens);
void		ft_update_bin_token(t_bin_token	*bin_token, t_token *tokens);

//		ft_bin_tokens_pipes		//

t_bin_token	*ft_bin_multi_pipe(t_data *data, int pipe_count);
t_token		*ft_take_last_pipe(t_token *tokens);
t_bin_token	*ft_initialize_all_pipes(int pipe_count);

//			ft_bin_token		//
int			ft_has_pipes(t_data *data);
int			ft_bin_count_args(t_token *tokens);
int			ft_first_redir(t_token *tokens);
t_bin_token	*ft_bin_tokens(t_data *data);

#endif
