/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:07:46 by afogonca          #+#    #+#             */
/*   Updated: 2024/11/17 11:07:48 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_chrjoin(char const *str, char const chr)
{
	size_t	size;
	size_t	i;
	char	*dstr;

	i = 0;
	if (!str && !chr)
		return (NULL);
	size = ft_strlen(str) + 1;
	dstr = (char *) malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	while (*str != '\0')
		dstr[i++] = *(str++);
	dstr[i++] = chr;
	dstr[i] = '\0';
	return (dstr);
}
