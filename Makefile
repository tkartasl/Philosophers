# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 12:11:59 by tkartasl          #+#    #+#              #
#    Updated: 2024/05/10 16:47:56 by tkartasl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c \
		philo_utils.c \
		philo_actions.c \
		init_functions.c \
		time_functions.c

OBJS = $(SRCS:.c=.o)

MAKE = make

FLAGS = -Wall -Wextra -Werror -I includes #-fsanitize=thread -g

CC = cc #-g

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re