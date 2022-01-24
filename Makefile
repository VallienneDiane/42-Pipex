# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/13 15:49:10 by dvallien          #+#    #+#              #
#    Updated: 2022/01/19 17:53:46 by dvallien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

INCS = ./includes/pipex.h \

SRCS =		./srcs/main.c			\
			./srcs/ft_split.c		\
			./srcs/ft_utils.c		\
			./srcs/ft_pipex.c		\
			./srcs/ft_utils_bis.c	\
			./srcs/ft_access_path.c	\

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I ${INCS}

RM = rm -f

all : ${NAME}

%.o: %.c ${INCS}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re