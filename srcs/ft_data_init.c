/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 09:07:39 by afogonca          #+#    #+#             */
/*   Updated: 2025/01/02 09:08:22 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_data	*ft_data_init(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->tokens = NULL;
	data->tokens_start = NULL;
	data->command = NULL;
	data->args = NULL;
	data->envp = NULL;
	return (data);
}
