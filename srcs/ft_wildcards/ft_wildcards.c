/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:21:32 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/05 20:21:34 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_wildcards.h"

void	ft_organize_files(char **files)
{
	char	*tmp;
	int		i;

	i = 0;
	while (files[i])
	{
		if (files[i] && files[i + 1]
			&& ft_strcmp(files[i], files[i + 1]) > 0)
		{
			tmp = ft_strdup(files[i]);
			free(files[i]);
			files[i] = ft_strdup(files[i + 1]);
			free(files[i + 1]);
			files[i + 1] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
}

int	ft_substitution(t_data *data, t_token **tokens)
{
	char	**files;
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	files = ft_get_files();
	ft_organize_files(files);
	if ((*tokens) && (*tokens)->content
		&& (*tokens)->content[0] == '*')
		new = ft_wildcards_end((*tokens), files, 0);
	else if ((*tokens) && (*tokens)->content
		&& (*tokens)->content[ft_strlen((*tokens)->content) - 1] == '*')
		new = ft_wildcards_begin((*tokens), files, 0);
	else if ((*tokens) && (*tokens)->content
		&& ft_strchr((*tokens)->content, '*'))
		new = ft_wildcards_mid((*tokens), files);
	ft_free_matrix(files);
	tmp = (*tokens)->next;
	ft_replace_node(&data->tokens_start, *tokens, new);
	*tokens = data->tokens_start;
	while ((*tokens) && (*tokens) != tmp)
		(*tokens) = (*tokens)->next;
	return (0);
}

int	ft_wildcards(t_data *data)
{
	data->tokens = data->tokens_start;
	while (data->tokens)
	{
		if (data->tokens->type != HERE_DOC
			&& data->tokens->type != FILENAME
			&& ft_strchr(data->tokens->content, '*'))
			ft_substitution(data, &data->tokens);
		if (data->tokens)
			data->tokens = data->tokens->next;
	}
	data->tokens = data->tokens_start;
	return (0);
}
