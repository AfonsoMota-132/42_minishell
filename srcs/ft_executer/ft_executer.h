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

# include "../../incs/minishell.h"

//		ft_error_executer		//
void	ft_command_not_found(t_data *data, char *path, char **array);
void	ft_error_msg_redir(t_data *data, int type, char *redir, char *path);

//			ft_pipes			//
void	ft_pipe_parent(t_bin_token *tokens, int *fd, t_data *data);
void	ft_pipe_child(t_bin_token *tokens, int *fd, t_data *data);
void	ft_handle_pipe(t_bin_token *tokens, t_data *data, int fd[2]);
void	ft_create_pipe(t_bin_token *tokens, t_data *data);

//			ft_run_cmds			//
void	ft_run_cmds(t_data *data);
char	*ft_execve_get_path(char *cmd, t_data *data);
int		ft_handle_builtins(t_bin_token *tokens, t_data *data, int i, int exit);
void	ft_execute_node(t_bin_token *tree, t_data *data);
void	ft_execve(t_bin_token *tokens, t_data *data);

//			ft_redirects_exec	//
void	ft_handle_redirects2(t_data *data, t_bin_token *tokens, char *path);
void	ft_handle_redirects(t_data *data, t_bin_token *tokens, char *path);
int		ft_handle_redirects_ne(t_bin_token *tokens, char *path);;
#endif
