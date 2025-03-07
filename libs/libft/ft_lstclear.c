/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 09:07:46 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/27 09:07:49 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*idk;

	idk = *lst;
	while (idk)
	{
		temp = idk -> next;
		(*del)(idk -> content);
		free(idk);
		idk = temp;
	}
	*lst = NULL;
}
