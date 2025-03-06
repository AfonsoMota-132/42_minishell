/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:40:19 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/05 19:40:30 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcards.h"

size_t	ft_count_files(void)
{
	DIR				*dir;
	size_t			i;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
		return (0);
	entry = readdir(dir);
	i = 0;
	while (entry)
	{
		entry = readdir(dir);
		i++;
	}
	closedir(dir);
	return (i);
}

char	**ft_get_files(void)
{
	DIR				*dir;
	int				i;
	char			**files;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	files = ft_calloc(sizeof(char *), (ft_count_files() + 1));
	entry = readdir(dir);
	files[0] = ft_strdup(entry->d_name);
	i = 1;
	while (entry)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		files[i] = ft_strdup(entry->d_name);
		i++;
	}
	closedir(dir);
	return (files);
}

void	ft_replace_node(t_token **head, t_token *target, t_token *new_nodes)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = (*head);
	while (curr && curr != target)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	if (prev)
		prev->next = new_nodes;
	else
		(*head) = new_nodes;
	while (new_nodes->next)
		new_nodes = new_nodes->next;
	new_nodes->next = curr->next;
	target->next = NULL;
	if (target)
		ft_free_tokens(target, 0);
}

void	ft_tokenadd_back(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!*token)
		*token = new;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_token	*ft_token_new(char *str)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	new->type = CMD;
	new->content = ft_strdup(str);
	if (str)
		free(str);
	new->heredoc = NULL;
	new->quotes = 0;
	new->len = 0;
	new->next = NULL;
	return (new);
}
