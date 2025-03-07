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
