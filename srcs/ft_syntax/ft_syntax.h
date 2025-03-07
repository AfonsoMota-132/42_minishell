/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:30:01 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 14:30:37 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SYNTAX_H
# define FT_SYNTAX_H

# include "../../incs/minishell.h"

//	ft_syntanx_tokens	//
int	ft_syntax_tokens2(t_token *tokens);
int	ft_syntax_tokens3(t_token *tokens);
int	ft_syntax_tokens(t_token *tokens);
int	ft_syntax_tokens_quotes(t_token *tokens);

//		ft_syntanx		//

int	ft_quote_syntax(char *command);
int	ft_pipe_syntax(char *command);
int	ft_redirect_syntax(char *command);
int	ft_syntax(char *command);
#endif
