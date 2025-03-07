/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:51:04 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/28 14:51:39 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_segcount(char const *s, char sep);
static char		**ft_alloc(char **strs, char const *s, char sep, size_t segs);
static size_t	ft_seglen(char const *s, char sep);

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	segs;

	if (!s)
		return (NULL);
	segs = ft_segcount(s, c);
	strs = malloc((segs + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs[segs] = 0;
	if (segs > 0)
		strs = ft_alloc(strs, s, c, segs);
	return (strs);
}

static int	ft_segcount(char const *s, char sep)
{
	size_t	segs;
	size_t	i;
	int		counting;

	i = 0;
	segs = 0;
	counting = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != sep && !counting)
		{
			counting = 1;
			++segs;
		}
		if (s[i] == sep && counting)
			counting = 0;
		++i;
	}
	return (segs);
}

static char	**ft_alloc(char **strs, char const *s, char sep, size_t segs)
{
	size_t	i;
	size_t	j;
	size_t	seg;

	i = 0;
	seg = 0;
	while (seg < segs)
	{
		j = 0;
		while (s[i] && s[i] == sep)
			++i;
		strs[seg] = malloc(ft_seglen(&s[i], sep) + 1);
		if (!strs[seg])
			return (ft_free_split(strs, seg));
		while (s[i] && s[i] != sep)
		{
			strs[seg][j] = s[i];
			++i;
			++j;
		}
		strs[seg][j] = '\0';
		++seg;
	}
	return (strs);
}

static size_t	ft_seglen(char const *s, char sep)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != sep)
		++i;
	return (i);
}

char	**ft_free_split(char **strs, size_t seg)
{
	size_t	i;

	i = 0;
	while (i < seg)
	{
		free(strs[i]);
		++i;
	}
	free(strs);
	return (0);
}
