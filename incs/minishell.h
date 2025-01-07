/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:56:43 by afogonca          #+#    #+#             */
/*   Updated: 2024/12/18 11:13:44 by afogonca         ###   ########.fr       */
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

typedef enum e_token_type {
	CMD,
	ARG,
	PIPE,
	REDIRECT_IN,
	D_REDIRECT_IN,
	REDIRECT_OUT,
	D_REDIRECT_OUT
}	t_token_type;

typedef	struct s_token {
	t_token_type	type;
	char			*content;
	size_t			len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef	struct s_command {
	void		*content;
	void		*flags;
	void		*argument;
}	t_command;

typedef	struct s_data
{
	t_token		*tokens;
	t_token		*tokens_start;
	char		*command;
	char		**args;
	char		**envp;
	char		*path;
	char		*user;
	char		*prompt;
}	t_data;

//		ft_readline		//

char	*ft_readline(char *str);
char	*ft_rmv_nl(char *str);
char	*ft_addstr(char *s1, char s2);

//		Ft_split_ms		//

int		ft_quote_len(char const *s);
int		ft_seglen(char const *s);
char	**ft_split_cmds(char *command);

//		Ft_free			//

void	ft_free_cmds(char **commands);
void	ft_free_tokens(t_token *tokens);
int		ft_free(int i, char *command, t_data *data);

//		Ft_tokens		//

t_token	*ft_token_maker(char **commands);
void	ft_tokens_cat(t_data **data);

//		FT_Syntax		//

int	ft_syntax(char *command);

//		FT_data_init	//

t_data	*ft_data_init(char **envp);


//		FT_execve		//

void	ft_execve(char *path, char **argv, char **envp);


//		FT_expander		//

void	ft_expander(t_token *tokens);

//		FT_Builtins		//

void	ft_cd(t_token * tokens);
void	ft_env(t_data *data);

#endif
