/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards_begin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:39:09 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/05 19:46:43 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcards.h"

t_token	*ft_wildcards_begin(t_token *tokens, char **files, size_t pos)
{
	size_t	i;
	size_t	size;
	t_token	*new;

	new = NULL;
	i = 0;
	size = ft_strchr_len(&tokens->content[pos + 1], '*');
	while (files[i])
	{
		if (ft_strlen(files[i]) > size
			&& ft_strncmp(files[i],
				tokens->content, size) == 0)
			ft_tokenadd_back(&new, ft_token_new(ft_strdup(files[i])));
		i++;
	}
	return (new);
}
