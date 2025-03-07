/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:53:24 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/31 12:09:11 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc_gnl(size_t nbytes, size_t size)
{
	size_t			i;
	unsigned char	*str;

	str = malloc(nbytes * size);
	if (!str)
		return (0);
	i = 0;
	while (i < (nbytes * size))
		str[i++] = '\0';
	return (str);
}

char	*ft_strchr_gnl(char *s, int c)
{
	if (!s)
		return (0);
	while (*s != c)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *) s);
}

int	ft_strlen_gnl(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		s1 = (char *) ft_calloc_gnl(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	if (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) == 0)
	{
		free(s1);
		return (NULL);
	}
	str = ft_calloc_gnl((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1),
			sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	free(s1);
	return (str);
}

char	*ft_bufferupdt(char *buffer)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	temp = ft_calloc_gnl((ft_strlen_gnl(buffer) - i + 1), sizeof(char));
	if (!temp)
		return (NULL);
	j = 0;
	while (buffer[i++])
		temp[j++] = buffer[i];
	temp[j] = '\0';
	free (buffer);
	return (temp);
}
