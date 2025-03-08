/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:59:45 by afogonca          #+#    #+#             */
/*   Updated: 2025/02/23 13:02:54 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include "ft_structs.h"
# include "../srcs/ft_bin_tokens/ft_bin_tokens.h"
# include "../srcs/ft_builtins/ft_builtins.h"
# include "../srcs/ft_data_init/ft_data_init.h"
# include "../srcs/ft_executer/ft_executer.h"
# include "../srcs/ft_redirects/ft_redirects.h"
# include "../srcs/ft_signals/ft_signals.h"
# include "../srcs/ft_syntax/ft_syntax.h"
# include "../srcs/ft_expander/ft_expander.h"
# include "../srcs/ft_rmv_quotes/ft_rmv_quotes.h"
# include "../srcs/ft_free/ft_free.h"
# include "../srcs/ft_tokens/ft_tokens.h"
# include "../srcs/ft_wildcards/ft_wildcards.h"

t_token			*ft_tokens_end(t_token_type type_tmp, t_data *data);
int				ft_get_run(t_data *data, t_token_type type_tmp);
t_token_type	ft_return_con_type(t_token *tokens);
t_token			*ft_return_after_con(t_token *tokens);
void			ft_free_loop3(t_data *data);
int				ft_skip_par2(t_token **tokens, t_token *head);
int				ft_skip_par(t_token **tokens);
void			ft_take_out_par(t_token **tokens, int run);

void			ft_print_tokens(t_token *tokens, t_data *data, int tab);
void			treeprint(t_bin_token *cur, int depth);

#endif
