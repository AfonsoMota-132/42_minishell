/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:16:27 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/06 12:42:26 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

# include "../../incs/minishell.h"

int		ft_echo(t_data *data, t_bin_token *token, int exit);
int		ft_pwd(t_data *data, t_bin_token *tokens, int exit);
int		ft_exit(t_data *data, t_bin_token *tokens, int exit);
int		ft_cd(t_data *data, t_bin_token *token, int exit);
t_envp	*ft_find_key(t_data *data, char *key);
void	ft_print_export(t_data *data);
int		ft_export(t_data *data, t_bin_token *token, int exit);
int		ft_size_struct(t_envp *envp);
void	ft_sort_envp(t_data *data);
void	ft_swap_envp(t_envp *first, t_envp *second);
int		ft_export_loop(t_data *data, t_bin_token *token);
int		ft_replace_env(t_data	*data, char *key, char *value);
void	ft_change_env(t_data	*data, char *key, char *dir);
void	ft_add_env(t_data	*data, char *key, char *value);
void	ft_print_envp(t_data *data);
int		ft_update_pwd(t_data *data, char *last_path);
int		ft_go_to_path(t_data *data, int option, char *last_path,
			t_bin_token *token);
int		ft_cd_return_value(t_bin_token *token, t_data *data, char *last_path);
bool	ft_unsetenv(t_data *data, char *token);
int		ft_unset(t_data *data, t_bin_token *token, bool exit_nbr);
char	*ft_export_get_value(t_bin_token *token, int i, size_t tmp);
void	ft_free_key_value(char **key, char **value);
int		ft_error_msg_export(char *args);
int		ft_check_key(char *key);
int		ft_export_append(t_data *data, t_bin_token *token,
			size_t tmp, int i);
int		ft_export_simple(t_data *data, t_bin_token *token,
			size_t tmp, int i);
int		ft_run_single_builtins(t_bin_token *tokens, t_data *data);
int		ft_run_single_builtins2(t_bin_token *tokens, t_data *data);
int		ft_run_single_builtins3(t_bin_token *tokens, t_data *data);
void	ft_special_putstr(char *str);

#endif
