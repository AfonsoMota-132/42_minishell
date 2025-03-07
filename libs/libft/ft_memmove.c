/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:23:45 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/22 16:08:47 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*sdest;
	unsigned char	*ssrc;
	size_t			i;

	i = 0;
	sdest = (unsigned char *) dest;
	ssrc = (unsigned char *) src;
	if (sdest > ssrc)
	{
		while (i++ < n)
			sdest[n - i] = ssrc[n - i];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
