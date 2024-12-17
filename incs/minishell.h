/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:56:43 by afogonca          #+#    #+#             */
/*   Updated: 2024/12/17 19:57:28 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libs/libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//		ft_readline		//

char	*ft_readline(char *str);
char	*ft_rmv_nl(char *str);
char	*ft_addstr(char *s1, char *s2);

#endif
