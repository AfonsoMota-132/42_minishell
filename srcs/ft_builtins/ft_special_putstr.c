/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_putstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:40:42 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/06 12:42:20 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtins.h"
#include <unistd.h>

int	ft_is_stdout_open(void)
{
	if (write(1, "", 0) == -1 && errno == EBADF)
		return (0);
	return (1);
}

void	ft_special_putstr(char *str)
{
	if (ft_is_stdout_open())
		write(STDOUT_FILENO, str, ft_strlen(str));
}
