/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:08:50 by afogonca          #+#    #+#             */
/*   Updated: 2025/03/07 21:08:52 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_free_loop3(t_data *data)
{
	ft_free_tokens(data->tokens, 1);
	data->tokens_start = data->tokens_end;
	data->tokens = data->tokens_start;
}

int	ft_skip_par2(t_token **tokens, t_token *head)
{
	t_token	*tmp;
	int		ret;

	ret = -1;
	if ((*tokens)->next)
	{
		if ((*tokens)->next->type == AND)
			ret = 0;
		if ((*tokens)->next->type == AND)
			ret = 1;
		if ((*tokens)->next->type == AND)
			ret = 1;
		tmp = (*tokens)->next;
		(*tokens) = (*tokens)->next->next;
		ft_free_tokens(head, 1);
		tmp->next = NULL;
	}
	else
		(*tokens) = NULL;
	return (ret);
}

int	ft_skip_par(t_token **tokens)
{
	int		count;
	t_token	*head;

	count = 0;
	head = *tokens;
	while (*tokens)
	{
		if ((*tokens)->type == IN_PAR)
			count++;
		if ((*tokens)->type == OUT_PAR && count)
			count++;
		if ((*tokens)->type == OUT_PAR && !count)
			return (ft_skip_par2(tokens, head));
		(*tokens) = (*tokens)->next;
	}
	return (-1);
}

void	ft_take_out_par2(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	*tokens = (*tokens)->next;
	tmp->next = NULL;
	ft_free_tokens(tmp, 0);
}

void	ft_take_out_par(t_token **tokens, int run)
{
	t_token	*tmp2;
	int		count;
	t_token	*tmp;

	if (run == 1 && (*tokens) && (*tokens)->type == IN_PAR)
	{
		ft_take_out_par2(tokens);
		tmp = *tokens;
		count = 0;
		while (tmp)
		{
			if (tmp->next && tmp->next->type == IN_PAR)
				count++;
			if (tmp->next && tmp->next->type == OUT_PAR && count)
				count--;
			else if (tmp->next && tmp->next->type == OUT_PAR)
			{
				tmp2 = tmp->next;
				tmp->next = tmp->next->next;
				tmp2->next = NULL;
				ft_free_tokens(tmp2, 1);
			}
			tmp = tmp->next;
		}
	}
}
