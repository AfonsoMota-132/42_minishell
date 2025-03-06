/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:51:33 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/02 14:52:14 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPANDER_H
# define FT_EXPANDER_H

# include "../../incs/minishell.h"

//		ft_expander_replace		//
char	*ft_expander_replace(char *str, char *env, int start);
char	*ft_expander_replace_null(char *str, int start);

//			ft_expander			//
void	ft_check_expander2(t_token *tokens, size_t *i);
int		ft_check_expander(t_token *tokens, size_t *i);
void	ft_expand_quest(t_token *tokens, t_data *data,
			char *env, size_t *start);
void	ft_expander3(t_token *tokens, size_t *i);
void	ft_expander2(t_token *tokens, \
		size_t *start, t_data *data);

//			ft_expander2		//
void	ft_expander_reset(char *str, size_t *i);
void	ft_skip_single_quote(char *str, size_t *i);
int		ft_len_env(char *str);
void	ft_expander(t_token *tokens, t_data *data);
#endif
