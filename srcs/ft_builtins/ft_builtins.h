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

int	ft_unset(t_data *data, t_bin_token *token, bool exit_nbr);

int		ft_cd(t_data *data, t_bin_token *token, int exit);
t_envp	*ft_find_key(t_data *data, char *key);

void	ft_print_export(t_data *data);
int	ft_export(t_data *data, t_bin_token *token, int	exit);
int	ft_size_struct(t_envp *envp);
void	ft_sort_envp(t_data *data);
void	ft_swap_envp(t_envp *first, t_envp *second);
int		ft_export_loop(t_data *data, t_bin_token *token);
int		ft_replace_env(t_data	*data, char *key, char *value);
void	ft_change_env(t_data	*data, char *key, char *dir);
void	ft_add_env(t_data	*data, char *key, char *value);
void	ft_print_envp(t_data *data);
bool	ft_unsetenv(t_data *data, char *token);
#endif
