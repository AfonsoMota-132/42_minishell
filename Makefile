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

VAL_RULES = --leak-check=full --show-leak-kinds=all --suppressions=readline.supp
all: deps $(NAME)

libft:
	@if [ -d libs/libft ]; then \
		echo "Already cloned"; \
	else \
		git clone git@github.com:AfonsoMota-132/42_libft.git libs/libft; \
	fi

valgrind:
	valgrind $(VAL_RULES) ./$(NAME)

deps: libft
	$(MAKE) -C libs/libft/

$(NAME): $(OBJS)
	$(CC) -lreadline $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
