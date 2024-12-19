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

#include "../libs/libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef enum e_token_type {
	CMD,
	ARG
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

//		ft_readline		//

char	*ft_readline(char *str);
char	*ft_rmv_nl(char *str);
char	*ft_addstr(char *s1, char *s2);

#endif
