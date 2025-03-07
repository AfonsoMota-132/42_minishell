/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:45:33 by afogonca          #+#    #+#             */
/*   Updated: 2024/10/28 15:52:48 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_makelst(t_list *list, void *(*f)(void *),
					void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_list;
	t_list	*list_start;
	void	*content;

	list_start = ft_makelst(lst, f, del);
	if (!list_start)
		return (NULL);
	n_list = list_start;
	lst = lst->next;
	while (lst)
	{
		content = f(lst->content);
		n_list->next = ft_lstnew(content);
		if (!n_list->next)
		{
			del(content);
			ft_lstclear(&list_start, del);
			return (NULL);
		}
		n_list = n_list->next;
		lst = lst->next;
	}
	return (list_start);
}

static t_list	*ft_makelst(t_list *list, void *(*f)(void *),
					void (*del)(void *))
{
	t_list	*n_list;
	void	*content;

	if (!list || !f || !del)
		return (NULL);
	content = f(list->content);
	n_list = ft_lstnew(content);
	if (!n_list)
	{
		del(content);
		return (NULL);
	}
	return (n_list);
}
