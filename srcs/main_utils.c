/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:06:57 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/06 13:07:24 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_token	*ft_tokens_end(t_token_type type_tmp, t_data *data)
{
	if (type_tmp != NON)
		return (ft_return_after_con(data->tokens));
	if (type_tmp == NON)
		return (NULL);
	return (NULL);
}

int	ft_get_run(t_data *data, t_token_type type_tmp)
{
	int		run;

	run = 0;
	if (data->exit_status)
	{
		if (type_tmp == AND)
			run = 0;
		if (type_tmp == OR)
			run = 1;
	}
	else if (!data->exit_status)
	{
		if (type_tmp == AND)
			run = 1;
		if (type_tmp == OR)
			run = 0;
	}
	if (type_tmp == SEMI)
		run = 1;
	return (run);
}

t_token_type	ft_return_con_type(t_token *tokens)
{
	t_token	*now;

	now = tokens;
	while (now)
	{
		if (now->type == SEMI)
			return (SEMI);
		if (now->type == AND)
			return (AND);
		if (now->type == OR)
			return (OR);
		now = now->next;
	}
	return (NON);
}

t_token	*ft_return_after_con(t_token *tokens)
{
	t_token	*prev;
	t_token	*now;
	t_token	*tmp;

	now = tokens;
	prev = NULL;
	while (now)
	{
		if (now->type == SEMI || now->type == AND
			|| now->type == OR)
		{
			prev->next = NULL;
			tmp = now->next;
			free(now->content);
			free(now);
			return (tmp);
		}
		prev = now;
		now = now->next;
	}
	return (now);
}
