/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:33:39 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/22 12:02:53 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;
	size_t	sum;

	i = 0;
	sum = 0;
	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (size > dlen)
		sum = dlen + slen;
	else
		sum = slen + size;
	while (src[i] && size > (dlen + 1))
	{
		dest[dlen] = src[i];
		i++;
		dlen++;
	}
	dest[dlen] = '\0';
	return (sum);
}
