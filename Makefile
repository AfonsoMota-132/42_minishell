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

EXECUTER = srcs/ft_executer/ft_pipes.c \
		   srcs/ft_executer/ft_run_cmds.c \
		   srcs/ft_executer/ft_error_exec.c \
		   srcs/ft_executer/ft_redirects_exec.c

BIN_TOKENS = srcs/ft_bin_tokens/ft_bin_tokens.c \
			srcs/ft_bin_tokens/ft_update_bin_tokens.c \
			srcs/ft_bin_tokens/ft_bin_tokens_pipes.c

SIGNALS = srcs/ft_signals/ft_signals.c

BUILTINS = srcs/ft_builtins/ft_echo.c \
		   srcs/ft_builtins/ft_exit.c \
		   srcs/ft_builtins/ft_pwd.c \

HEREDOC = srcs/ft_redirects/ft_heredoc/ft_heredoc.c \
		  srcs/ft_redirects/ft_heredoc/ft_actual_heredoc.c \
		  srcs/ft_redirects/ft_heredoc/ft_pseudo_heredoc.c

REDIRS = 	srcs/ft_redirects/ft_redirects.c \
			srcs/ft_redirects/ft_redir_short_out_single.c \
			srcs/ft_redirects/ft_redir_short_out_double.c \
			srcs/ft_redirects/ft_redir_short_out.c \
			srcs/ft_redirects/ft_redir_short_in_single.c \
			$(HEREDOC)

SYNTAX = srcs/ft_syntax/ft_syntax.c \
		srcs/ft_syntax/ft_syntax_tokens.c

EXPANDER = srcs/ft_expander/ft_expander.c \
		srcs/ft_expander/ft_expander2.c \
		srcs/ft_expander/ft_expander_replace.c

RMV_QUOTES = srcs/ft_rmv_quotes/ft_rmv_quotes.c

DATA_INIT = srcs/ft_data_init/ft_data_init.c \
			srcs/ft_data_init/ft_getenv.c \
			srcs/ft_data_init/ft_get_prompt.c

FREE = srcs/ft_free/ft_free.c

TOKENS = srcs/ft_tokens/ft_split_ms.c \
		srcs/ft_tokens/ft_tokens.c

SRCS =	srcs/main.c $(DATA_INIT) $(FREE) $(TOKENS) \
		$(BUILTINS) $(REDIRS) $(SIGNALS) $(RMV_QUOTES) \
		$(BIN_TOKENS) $(EXECUTER) $(SYNTAX) $(EXPANDER)

VAL_RULES = --leak-check=full --show-leak-kinds=all --suppressions=readline.supp
#--trace-children=yes
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
	@if [ -d libs/libft ]; then \
		$(MAKE) -C libs/libft/ clean; fi;

fclean: clean
	$(RM) $(NAME)
	@if [ -d libs/libft ]; then \
		$(RM) -rf libs/libft; fi;

tester:
	@if [ -d minishell_tester ]; then \
		echo "Already cloned"; \
	else \
		git clone https://github.com/LucasKuhn/minishell_tester.git; \
	fi

rm_tester:
	rm -fr minishell_tester;

re: fclean all

.PHONY: all clean fclean re deps valgrind
