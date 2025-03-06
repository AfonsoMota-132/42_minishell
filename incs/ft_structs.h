/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:10:43 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/06 11:11:44 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCTS_H
# define FT_STRUCTS_H

# include "../libs/libft/libft.h"

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
	HERE_DOC,
	SEMI,
	AND,
	OR,
	NON
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
	t_token		*tokens_end;
	t_bin_token	*bin_tokens;
	char		*command;
	char		*heredoc_path;
	char		**args;
	t_envp		*envp;
	char		*path;
	char		*user;
	char		*hostname;
	char		*prompt;
	int			exit_status;
}	t_data;

#endif
