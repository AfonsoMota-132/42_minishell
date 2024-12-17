# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 20:41:21 by afogonca          #+#    #+#              #
#    Updated: 2024/12/17 20:43:44 by afogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBS = libs/libft/libft.a
CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f

OBJS = $(SRCS:.c=.o)
SRCS = srcs/main.c srcs/ft_readline.c

all: deps $(NAME)

deps:
	$(MAKE) -C libs/libft/

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
