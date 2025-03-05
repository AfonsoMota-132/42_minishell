/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:21:32 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/05 15:42:10 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

size_t	ft_count_file_matches(t_token *tokens, char **files, size_t pos)
{
	size_t	size;
	int		i;
	size_t	count;

	count = 0;
	if (tokens->content[pos - 1]
		&& tokens->content[pos - 1] == '*')
	{
		size = ft_strlen(&tokens->content[pos]);
		printf("%s\n", &tokens->content[pos]);
		i = 0;
		while (files[i])
		{
			if (ft_strlen(files[i]) > size
				&& ft_strcmp(&files[i][ft_strlen(files[i]) - size],
					&tokens->content[pos]) == 0)
				count++;
			i++;
		}
	}
	printf("count: %lu\tpos: %lu\n", count, pos);
	return (count);
}

char	**ft_matching_files(t_token *tokens, char **files, size_t count, size_t pos)
{
	char	**tmp;
	int		i;
	int		x;
	size_t	size;

	size = ft_strlen(&tokens->content[pos]);
	tmp = ft_calloc(sizeof(char *), count + 1);
	i = 0;
	x = 0;
	while (files[i])
	{
		if (ft_strlen(files[i]) > size
			&& ft_strcmp(&files[i][ft_strlen(files[i]) - size],
				&tokens->content[pos]) == 0)
			tmp[x++] = ft_strdup(files[i]);
		i++;
	}
	return (tmp);
}

t_token	*ft_substitution(t_token *tokens)
{
	char	**files;
	size_t	size;
	size_t	count;
	char	**tmp;
	t_token	*new;
	size_t	pos;


	files = ft_get_files();
	for (int i = 0; files[i]; i++)
		printf("files: %s\n", files[i]);
	count = 0;
	tmp = NULL;
	new = NULL;
	printf("wtf0\n");
	pos = 0;
	while (tokens->content[pos]
		&& tokens->content[pos] != '*')
		pos++;
	if (tokens && tokens->content
		&& tokens->content[pos]
		&& tokens->content[pos] == '*')
	{
		pos++;
		printf("count: %lu\tpos: %lu\n", count, pos);
		size = ft_strlen(tokens->content) - 1;
		count = ft_count_file_matches(tokens, files, pos);
		tmp = ft_matching_files(tokens, files, count, pos);
		count = -1;
		while (tmp[++count])
			printf("%s\n", tmp[count]);
	}
	if (tmp)
		new = ft_token_maker(tmp);
	ft_free_matrix(files);
	return (new);
}

void	ft_wildcards(t_data *data)
{
	t_token		*tmp;
	t_token		*prev;

	prev = NULL;
	data->tokens = data->tokens_start;
	while (data->tokens)
	{
		if (ft_strchr(data->tokens->content, '*'))
		{
				tmp = ft_substitution(data->tokens);
			ft_print_tokens(tmp, NULL, 0);
		}
		prev = data->tokens;
		data->tokens = data->tokens->next;
	}
	data->tokens = data->tokens_start;
}
