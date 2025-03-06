/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:40:35 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/05 19:42:06 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WILDCARDS_H
# define FT_WILDCARDS_H

# include "../../incs/minishell.h"

t_token	*ft_wildcards_end(t_token *tokens, char **files, size_t pos);
t_token	*ft_wildcards_begin(t_token *tokens, char **files, size_t pos);
t_token	*ft_wildcards_mid(t_token *tokens, char **files);
size_t	ft_count_files(void);
char	**ft_get_files(void);
void	ft_replace_node(t_token **head, t_token *target, t_token *new_nodes);
void	ft_tokenadd_back(t_token **token, t_token *new_token);
t_token	*ft_token_new(char *str);
int		ft_wildcards(t_data *data);

#endif
