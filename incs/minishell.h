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


# include "../libs/libft/libft.h"
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

typedef struct s_envp
{
	char				*key;
	char				*value;
	bool				print;
	struct s_envp		*next;
}	t_envp;

typedef enum e_token_type
{
	CMD,
	ARG,
	PIPE,
	REDIRECT_IN,
	D_REDIRECT_IN,
	REDIRECT_OUT,
	D_REDIRECT_OUT,
	FILENAME,
	HERE_DOC
}	t_token_type;

typedef enum e_bin_token_type
{
	CMD_NODE,
	PIPE_NODE
}	t_bin_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	char			*heredoc;
	int				quotes;
	size_t			len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_bin_token
{
	char				**args;
	int					nbr_args;
	t_token				*redir_in;
	t_token				*redir_out;
	t_bin_token_type	type;
	int					first_redir;
	struct s_bin_token	*right;
	struct s_bin_token	*left;
}	t_bin_token;

typedef struct s_redir
{
	char			*filename;
	int				fd;
	t_token_type	type;
}	t_redir;

typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	t_redir				*redir_in;
	t_redir				*redir_out;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	t_token		*tokens;
	t_token		*tokens_start;
	t_bin_token	*bin_tokens;
	char		*command;
	char		*heredoc_path;
	char		**args;
	t_envp	*envp;
	char		*path;
	char		*user;
	char		*hostname;
	char		*prompt;
	int			exit_status;
}	t_data;

# include "../srcs/ft_executer/ft_executer.h"
# include "../srcs/ft_bin_tokens/ft_bin_tokens.h"
# include "../srcs/ft_builtins/ft_builtins.h"
# include "../srcs/ft_redirects/ft_redirects.h"
# include "../srcs/ft_signals/ft_signals.h"
# include "../srcs/ft_syntax/ft_syntax.h"
# include "../srcs/ft_expander/ft_expander.h"
# include "../srcs/ft_rmv_quotes/ft_rmv_quotes.h"
# include "../srcs/ft_data_init/ft_data_init.h"
# include "../srcs/ft_free/ft_free.h"
# include "../srcs/ft_tokens/ft_tokens.h"

void		ft_print_tokens(t_token *tokens, t_data *data, int tab);

#endif
