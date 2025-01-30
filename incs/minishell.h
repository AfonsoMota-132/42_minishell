/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:56:43 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/29 10:44:27 by afogonca         ###   ########.fr       */
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

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	size_t			len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef	struct s_redir {
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

	char		*command;
	char		**args;
	char		**ft_envp;
	char		*path;
	char		*user;
	char		*hostname;
	char		*prompt;
	int			exit_status;
}	t_data;

//		ft_readline		//

char	*ft_readline(char *str);
char	*ft_rmv_nl(char *str);
char	*ft_addstr(char *s1, char s2);

//		Ft_split_ms		//

int		ft_quote_len(char const *s);
int		ft_seglen(char const *s);
int		ft_count_parts(char const *s);
char	**ft_split_cmds(char *command);


//		Ft_free			//

void	ft_free_env(char **envp);
void	ft_free_cmds(char **commands);
void	ft_free_tokens(t_token *tokens);
int		ft_free(int i, char *command, t_data *data);
void	ft_free_matrix(char **matrix);


//		Ft_tokens		//

t_token	*ft_token_maker(char **commands);
void	ft_tokens_cat(t_data **data);

//		FT_Syntax		//

int		ft_quote_syntax(char *command);
int		ft_pipe_syntax(char *command);
int		ft_redirect_syntax(char *command);
int		ft_syntax(char *command);

//		FT_data_init	//

char	*ft_get_path(t_data *data);
void	ft_prompt_init(t_data *data);
char	*ft_get_hostname(void);
char	**ft_cpyenv(char **envp);
t_data	*ft_data_init(char **envp);

//		FT_execve		//

void	ft_execve(char *path, char **argv, char **envp);

//		FT_expander		//

void	ft_expander(t_token *tokens, t_data *data);
int		ft_len_env(char *str);
char	*ft_expander_replace(char *str, char *env, int start);
int		ft_check_expander(t_token *tokens, size_t *i);
void	ft_expand_quest(t_token *tokens, t_data *data
		, char *env, size_t *start);
void	ft_expander_reset(char *str, size_t *i);
void	ft_skip_single_quote(char *str, size_t *i);
char	*ft_getenv(char *env, t_data *data);

//		FT_Builtins		//

int		ft_echo(t_token *token);

//		FT_Rmv_quotes	//

int		ft_quote_rm_len(char const *s, char quote);
char	*ft_rmv_single_quotes(char *str, int *start);
char	*ft_rmv_double_quotes(char *str, int *start);
void	ft_rmv_quotes(t_token *tokens);

//		FT_Syntax_Tokens	//

int	ft_syntax_tokens(t_token *tokens);

//		FT_redirects		//

int		ft_redirects(t_token *tokens, t_data **data);
void	ft_take_last_redir_out(t_token *tokens);
void	ft_take_last_redir_in(t_token *tokens);
int		ft_verify_redir_out(t_token *tokens);
int		ft_verify_redir(t_token *tokens);

#endif
