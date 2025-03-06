/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:21:40 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:38:22 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REDIRECTS_H
# define FT_REDIRECTS_H

# include "../../incs/minishell.h"
# include "ft_heredoc/ft_heredoc.h"

//		ft_redir_short_in_single		//

t_token	*ft_rmv_ris_before(t_token *tokens, t_token *head);
t_token	*ft_take_ris_out(t_token *tokens, t_token *tmp);
void	ft_redir_short_in_single(t_token *tokens);

//			ft_redir_short_out			//

t_token	*ft_take_ro_out(t_token *head, t_token *tokens, int i);
int		ft_verify_redir_short(t_token *tokens);
int		ft_verify_access_out(t_token *tokens);
void	ft_redir_short_out_2(t_token *tokens, int *i);
void	ft_redir_short_out(t_token *tokens);

//		ft_redir_short_out_double		//

t_token	*ft_rmv_rod_before(t_token *tokens, t_token *head);
t_token	*ft_take_rod_out(t_token *tokens, t_token *tmp);
void	ft_redir_short_out_double(t_token *tokens);

//		ft_redir_short_out_single		//

t_token	*ft_rmv_ros_before(t_token *tokens, t_token *head);
t_token	*ft_skip_to_pipe(t_token *tokens);
t_token	*ft_take_ros_out(t_token *tokens, t_token *tmp);
void	ft_redir_short_out_single(t_token *tokens);

//			ft_redirects			//

void	ft_free_token(t_token *tokens);
t_token	*ft_pcmdf_first(t_token *tokens);
t_token	*ft_put_cmd_first(t_token *tokens);
int		ft_redirects(t_token *tokens, t_data **data);

#endif
