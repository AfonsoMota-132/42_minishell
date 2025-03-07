/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:32:32 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/24 10:41:08 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	**ft_matrixcopy(void **matrix)
{
	int		i;
	void	**cpy;

	i = 0;
	while (matrix[i])
		i++;
	cpy = ft_calloc(sizeof(void *), i + 1);
	i = -1;
	while (matrix[++i])
		cpy[i] = ft_strdup(matrix[i]);
	cpy[i] = NULL;
	return (cpy);
}
