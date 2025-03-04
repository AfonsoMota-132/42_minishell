/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_init.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:18:48 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 15:19:28 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DATA_INIT_H
# define FT_DATA_INIT_H

# ifndef MINISHELL_H
#  include "../../incs/minishell.h"
# endif

//		ft_getenv		//

char	*ft_getenv(char *env, t_data *data);
char	**ft_cpyenv(char **envp);

//		ft_get_prompt	//
char	*ft_get_path_with_til(char *path, char **dirs, int i);
char	*ft_get_path_without_til(char *path, char **dirs, int i);
char	*ft_get_path(t_data *data);
void	ft_prompt_init(t_data *data);

//		ft_data_init	//

char	*ft_get_hostname(void);
char	*ft_heredoc_path(t_data *data);
t_envp	*ft_new_env_node(char *envp);
void	ft_envlist_init(t_data *data, char **env);
t_data	*ft_data_init(char **envp);

#endif
