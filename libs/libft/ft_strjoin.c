/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:49:15 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/23 09:59:26 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	char	*str;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	while (*s1 != '\0')
		str[i++] = *(s1++);
	while (*s2 != '\0')
		str[i++] = *(s2++);
	str[i] = '\0';
	return (str);
}
/*
int main(int argc, char **argv)
{
	if (argc >= 3)
		printf("%s\n", ft_strjoin(argv[1],argv[2]));
	else
		printf("Not enough arguments\n");
}
*/
