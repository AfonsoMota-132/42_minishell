/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:22:21 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/25 11:35:24 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*temp;

	temp = (char *) s;
	while (*temp)
	{
		if (*temp == (unsigned char) c)
			return (temp);
		temp++;
	}
	if (*temp == (unsigned char) c)
		return (temp);
	if (c == 0)
		return (temp);
	return (NULL);
}
