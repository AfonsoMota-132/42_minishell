# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 20:41:21 by afogonca          #+#    #+#              #
#    Updated: 2025/01/29 10:28:18 by afogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBS = libs/libft/libft.a
CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f

OBJS = $(SRCS:.c=.o)

BUILTINS = srcs/ft_builtins/ft_echo.c

HEREDOC = srcs/ft_redirects/ft_heredoc/ft_heredoc.c

REDIRS = 	srcs/ft_redirects/ft_redirects.c \
			srcs/ft_redirects/ft_redir_short_out_single.c \
			srcs/ft_redirects/ft_redir_short_out_double.c \
			srcs/ft_redirects/ft_redir_short_out.c \
			srcs/ft_redirects/ft_redir_short_in_single.c \
			$(HEREDOC)

SRCS =	srcs/main.c srcs/ft_split_ms.c \
		srcs/ft_free.c srcs/ft_tokens.c srcs/ft_syntax.c \
		srcs/ft_data_init.c srcs/ft_expander.c \
		srcs/ft_rmv_quotes.c \
		srcs/ft_expander2.c	srcs/ft_syntax_tokens.c \
		srcs/ft_get_prompt.c \
		srcs/ft_getenv.c $(BUILTINS) $(REDIRS)
# srcs/ft_readline.c
#srcs/ft_execve.c

VAL_RULES = --leak-check=full --show-leak-kinds=all --suppressions=readline.supp
all: deps $(NAME)

libft:
	@if [ -d libs/libft ]; then \
		echo "Already cloned"; \
	else \
		git clone git@github.com:AfonsoMota-132/42_libft.git libs/libft; \
	fi

valgrind: all
	valgrind $(VAL_RULES) ./$(NAME)

deps: libft
	$(MAKE) -C libs/libft/

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) -lreadline

clean:
	$(RM) $(OBJS)
	$(MAKE) -C libs/libft/ clean

fclean: clean
	$(RM) $(NAME)
	$(RM) -Rf libs/libft

re: fclean all

.PHONY: all clean fclean re deps valgrind
