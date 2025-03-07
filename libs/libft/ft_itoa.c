/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:18:36 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/25 09:51:36 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbrlen(int n);
static void		ft_fill(int len, int offset, int n, char *str);

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		offset;

	offset = 0;
	len = ft_nbrlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		offset = 2;
		n = 147483648;
	}
	if (n < 0)
	{
		str[0] = '-';
		offset = 1;
		n *= -1;
	}
	ft_fill(len, offset, n, str);
	str[len] = '\0';
	return (str);
}

static	void	ft_fill(int len, int offset, int n, char *str)
{
	while (len > offset)
	{
		str[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
}

static int	ft_nbrlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
	{
		len += 2;
		n = 147483648;
	}
	else if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(-2147483647));
}*/
