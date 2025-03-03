/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:11:36 by palexand          #+#    #+#             */
/*   Updated: 2025/03/03 23:11:37 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
#define FT_BUILTINS_H

#ifndef MINISHELL_H
#include "../../incs/minishell.h"
# endif

void	ft_export(t_data *data, t_bin_token *token);
void	ft_sort_envp(t_data *data);
int		ft_size_struct(t_envp *envp);
void	ft_add_env(t_data	*data, char *key, char *value);
void	ft_change_env(t_data	*data, char *key, char *dir);
void	ft_print_export(t_data *data);
void	ft_swap_envp(t_envp *first, t_envp *second);
int	ft_replace_env(t_data	*data, char *value);
void ft_export_loop(t_data *data, t_bin_token *token);

#endif
