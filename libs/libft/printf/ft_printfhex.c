/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:16:16 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/30 12:16:57 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printfhex(unsigned int nbr, int uporlow)
{
	int				len;

	len = 0;
	if (nbr < 16)
	{
		if (uporlow == 0)
			len += write(1, &"0123456789abcdef"[nbr], 1);
		if (uporlow == 1)
			len += write(1, &"0123456789ABCDEF"[nbr], 1);
	}
	if (nbr >= 16)
	{
		len += ft_printfhex(nbr / 16, uporlow);
		len += ft_printfhex(nbr % 16, uporlow);
	}
	return (len);
}
