/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards_mid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:08:33 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/05 20:21:11 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcards.h"

t_token	*ft_wildcards_mid(t_token *tokens, char **files)
{
	size_t	i;
	size_t	pos;
	size_t	size1;
	size_t	size2;
	t_token	*new;

	new = NULL;
	i = 0;
	pos = 0;
	while (tokens->content[pos]
		&& tokens->content[pos] != '*')
		pos++;
	size1 = ft_strlen(&tokens->content[pos + 1]);
	size2 = ft_strchr_len(tokens->content, '*');
	while (files[i])
	{
		if (ft_strlen(files[i]) > size2 && ft_strncmp(files[i],
				tokens->content, size2) == 0 && ft_strlen(files[i]) > size1
			&& ft_strncmp(&files[i][ft_strlen(files[i]) - size1],
			&tokens->content[pos + 1], size1) == 0)
			ft_tokenadd_back(&new, ft_token_new(ft_strdup(files[i])));
		i++;
	}
	return (new);
}
