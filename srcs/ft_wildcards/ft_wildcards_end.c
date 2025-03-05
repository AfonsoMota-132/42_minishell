/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:09:39 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/05 19:16:30 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcards.h"

t_token	*ft_wildcards_end(t_token *tokens, char **files, size_t pos)
{
	size_t	i;
	size_t	size;
	t_token	*new;

	new = NULL;
	i = 0;
	size = ft_strlen(&tokens->content[pos + 1]);
	while (files[i])
	{
		if (ft_strlen(files[i]) > size
			&& ft_strncmp(&files[i][ft_strlen(files[i]) - size],
			&tokens->content[pos + 1], size) == 0)
			ft_tokenadd_back(&new, ft_token_new(ft_strdup(files[i])));
		i++;
	}
	return (new);
}
