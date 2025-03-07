/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpoint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:18:32 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/30 12:18:52 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_printf_adress(unsigned long p)
{
	int				len;

	len = 0;
	if (p < 16)
		len += write(1, &"0123456789abcdef"[p], 1);
	if (p >= 16)
	{
		len += ft_printf_adress(p / 16);
		len += ft_printf_adress(p % 16);
	}
	return (len);
}

int	ft_printfpointer(void *pointer)
{
	int	len;

	len = 0;
	if (!pointer)
		return (ft_printfstr("(nil)"));
	else
		len += ft_printfstr("0x");
	len += ft_printf_adress((unsigned long) pointer);
	return (len);
}
