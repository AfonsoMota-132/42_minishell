/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:27:51 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/26 13:48:19 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sbig;
	char	*slittle;

	if (!big && !len)
		return (0);
	i = 0;
	sbig = (char *) big;
	slittle = (char *) little;
	if (!slittle[0])
		return (sbig);
	while (i < len && sbig[i])
	{
		j = 0;
		if (sbig[i] == slittle[j])
		{
			while (sbig[i + j] == slittle[j] && sbig[i + j] && (i + j) < len)
				j++;
			if (slittle[j] == '\0')
				return (sbig + i);
		}
		i++;
	}
	return (0);
}
