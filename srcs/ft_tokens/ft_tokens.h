/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:35:33 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 15:36:05 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKENS_H
# define FT_TOKENS_H

# ifndef MINISHELL_H
#  include "../../incs/minishell.h"
# endif

//		ft_split_ms		//

int		ft_quote_len(char const *s);
int		ft_seglen(char const *s);
int		ft_count_parts(char const *s);
char	**ft_split_cmds(char *command);

//		ft_tokens		//

t_token	*ft_token_maker(char **commands);
int		ft_tokens_cat2(t_data **data, int check);
void	ft_tokens_cat3(t_data **data);
void	ft_tokens_cat(t_data **data);
void	ft_token_start(char **commands, t_data *data);

#endif
