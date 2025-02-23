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
	size_t			len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_bin_token
{
	char				**args;
	t_token				*redir_in;
	t_token				*redir_out;
	t_bin_token_type	type;	
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
	char		**ft_envp;
	char		*path;
	char		*user;
	char		*hostname;
	char		*prompt;
	int			exit_status;
}	t_data;

void		ft_print_tokens(t_token *tokens, t_data *data, int tab);

//		FT_SIGNALS		//

void		ft_signals_handler(int sig);
void		ft_signals(void);
void		ft_heredoc_signal_handler(int sig);

//		ft_readline		//

char		*ft_readline(char *str);
char		*ft_rmv_nl(char *str);
char		*ft_addstr(char *s1, char s2);

//		Ft_split_ms		//

int			ft_quote_len(char const *s);
int			ft_seglen(char const *s);
int			ft_count_parts(char const *s);
char		**ft_split_cmds(char *command);

//		Ft_free			//

void		ft_free_env(char **envp);
void		ft_free_cmds(char **commands);
void		ft_free_tokens(t_token *tokens, int del_heredoc);
int			ft_free(int i, char *command, t_data *data, int del_heredoc);
void		ft_free_matrix(char **matrix);
void		ft_free_tree(t_bin_token *tokens, int del_heredoc);

//		Ft_tokens		//

t_token		*ft_token_maker(char **commands);
void		ft_tokens_cat(t_data **data);

//		FT_Syntax		//

int			ft_quote_syntax(char *command);
int			ft_pipe_syntax(char *command);
int			ft_redirect_syntax(char *command);
int			ft_syntax(char *command);

//		FT_data_init	//

char		*ft_get_path(t_data *data);
void		ft_prompt_init(t_data *data);
char		*ft_get_hostname(void);
char		**ft_cpyenv(char **envp);
t_data		*ft_data_init(char **envp);
char		*ft_get_path_with_til(char *path, char **dirs, int i);
char		*ft_get_path_without_til(char *path, char **dirs, int i);
char		*ft_get_path(t_data *data);

//		FT_expander		//

void		ft_expander(t_token *tokens, t_data *data);
int			ft_len_env(char *str);
char		*ft_expander_replace(char *str, char *env, int start);
int			ft_check_expander(t_token *tokens, size_t *i);
void		ft_expand_quest(t_token *tokens, t_data *data,
				char *env, size_t *start);
void		ft_expander_reset(char *str, size_t *i);
void		ft_skip_single_quote(char *str, size_t *i);
char		*ft_getenv(char *env, t_data *data);
void		ft_expander2(t_token *tokens, \
			size_t *start, t_data *data);

//		FT_Builtins		//

int			ft_echo(t_token *token);

//		FT_Rmv_quotes	//

int			ft_quote_rm_len(char const *s, char quote);
char		*ft_rmv_single_quotes(char *str, int *start);
char		*ft_rmv_double_quotes(char *str, int *start);
void		ft_rmv_quotes(t_token *tokens);

//		FT_Syntax_Tokens	//

int			ft_syntax_tokens(t_token *tokens);

//		FT_redirects		//

int			ft_redirects(t_token *tokens, t_data **data);
t_token		*ft_skip_to_pipe(t_token *tokens);

//		FT_redir_short__out__single		//

t_token		*ft_rmv_ros_before(t_token *tokens, t_token *head);
t_token		*ft_take_ros_out(t_token *tokens, t_token *tmp);
void		ft_redir_short_out_single(t_token *tokens);

//		FT_redir_short_out_double		//

t_token		*ft_rmv_rod_before(t_token *tokens, t_token *head);
t_token		*ft_take_rod_out(t_token *tokens, t_token *tmp);
void		ft_redir_short_out_double(t_token *tokens);

//		FT_redir_short_out		//

t_token		*ft_take_ro_out(t_token *head, t_token *tokens, int i);
void		ft_redir_short_out(t_token *tokens);

//		FT_redir_short_in		//

t_token		*ft_rmv_ris_before(t_token *tokens, t_token *head);
t_token		*ft_take_ris_out(t_token *tokens, t_token *tmp);
void		ft_redir_short_in_single(t_token *tokens);

//		FT_Heredoc		//

int			ft_heredoc(t_token *tokens, t_data *data);

void		ft_actual_heredoc_loop(t_token *tokens, t_data *data, t_token *str, int fd);
char		*ft_heredoc_name(t_token *tokens, t_data *data);
int			ft_strvalue(char *str);
void		ft_free_token(t_token *tokens);
void		ft_define_heredoc_paths(t_token *tokens, t_data *data);
t_token		*ft_verify_heredoc_is_last(t_token *tokens);
void		ft_actual_heredoc(t_token *tokens, t_data *data);
void		ft_pseudo_heredoc(t_token *tokens);
void		ft_del_pseudo_heredocs(t_token *tokens);

//	t_bin_tokens	//

t_bin_token	*ft_bin_tokens(t_data *data);

//		ft_executer	test		//

void		ft_pipes_creator(t_data *data, t_bin_token *tokens);
void		ft_handle_pipe(t_data *data, t_bin_token *tokens, int fd[2]);
void		ft_pipe_parent(t_data *data, t_bin_token *tokens, int fd[2]);

#endif
