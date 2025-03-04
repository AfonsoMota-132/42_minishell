/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:24:14 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 12:26:43 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEREDOC_H
# define FT_HEREDOC_H

# ifndef FT_REDIRECTS_H
#  include "../ft_redirects.h"
# endif

//			ft_heredoc		//
int		ft_verify_heredoc(t_token *tokens);
t_token	*ft_verify_heredoc_is_last(t_token *tokens);
void	ft_heredoc_child_process(t_data *data, t_token *tokens, t_token *tmp);
int		ft_heredoc(t_token *tokens, t_data *data);

//		ft_pseudo_heredoc	//
void	ft_del_pseudo_heredocs(t_token *tokens);
void	ft_pseudo_heredoc(t_token *tokens, t_data *data);

//		ft_actual_heredoc	//

int		ft_strvalue(char *str);
char	*ft_heredoc_name(t_token *tokens, t_data *data);
void	ft_define_heredoc_paths(t_token *tokens, t_data *data);
void	ft_actual_heredoc_loop(t_token *tokens, t_data *data,
			t_token *str, int fd);
void	ft_actual_heredoc(t_token *tokens, t_data *data);

#endif
