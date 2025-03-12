# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 18:53:43 by afogonca          #+#    #+#              #
#    Updated: 2025/03/07 10:32:10 by afogonca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compile
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Files

BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	     ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

PRINTF = printf/ft_printf.c printf/ft_printfhex.c printf/ft_printfpointer.c \
		printf/ft_printfunbr.c printf/ft_printfnbr.c printf/ft_printfstr.c

GNL = gnl/get_next_line.c gnl/get_next_line_utils.c

EXTRA = extra/ft_chrjoin.c extra/ft_atol.c extra/ft_strcmp.c extra/ft_matrixcpy.c \
		extra/ft_matrix_free.c extra/ft_strchr_len.c extra/ft_split_multi.c

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
    	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_substr.c \
		ft_strjoin.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_atoi.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_itoa.c \
		ft_putnbr_fd.c ft_strncmp.c ft_strtrim.c ft_strdup.c ft_strchr.c \
		ft_calloc.c ft_memchr.c ft_strrchr.c ft_strmapi.c ft_striteri.c ft_memcmp.c \
		ft_strnstr.c ft_split.c $(PRINTF) $(GNL) $(EXTRA)

BONUS_OBJS = ${BONUS_SRCS:.c=.o}
OBJS = ${SRCS:.c=.o}
NAME = libft.a

# Rules

# Silent compilation
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: ${OBJS} ${BONUS_OBJS}
	@ar rc ${NAME} ${BONUS_OBJS} ${OBJS}

${NAME}: ${OBJS}
	@ar rc ${NAME} ${OBJS}	

clean:
	@${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
	@${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re
