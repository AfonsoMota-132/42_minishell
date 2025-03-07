/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:08:56 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/22 16:08:08 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str_store;
	size_t			i;

	i = 0;
	str_store = (unsigned char *) s;
	while (i < n)
	{
		str_store[i] = '\0';
		i++;
	}
}
