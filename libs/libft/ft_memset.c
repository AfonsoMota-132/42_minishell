/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:14:38 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/23 08:57:31 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*idk;

	idk = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		idk[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
