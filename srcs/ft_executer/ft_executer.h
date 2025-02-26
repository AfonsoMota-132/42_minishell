/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:08:29 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/26 11:13:04 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTER_H
# define FT_EXECUTER_H

# ifndef MINiSHELL_H
#  include "../../incs/minishell.h"
# endif

//		ft_error_executer		//
void	ft_command_not_found(t_data *data, char *path);
void	ft_error_msg_redir(t_data *data, int type, char *redir, char *path);

//			ft_pipes			//
void	ft_pipe_parent(t_bin_token *tokens, int *fd, t_data *data);
void	ft_pipe_child(t_bin_token *tokens, int *fd, t_data *data);
void	ft_handle_pipe(t_bin_token *tokens, t_data *data, int fd[2]);
void	ft_create_pipe(t_bin_token *tokens, t_data *data);

#endif
