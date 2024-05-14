# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 12:11:59 by tkartasl          #+#    #+#              #
#    Updated: 2024/05/14 14:11:53 by tkartasl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c \
		philo_utils.c \
		philo_actions.c \
		init_functions.c \
		time_functions.c \
		monitor.c

OBJS = $(SRCS:.c=.o)

MAKE = make

FLAGS = -Wall -Wextra -Werror

CC = cc

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

${OBJS}: ${SRCS}
	${CC} ${FLAGS} -c ${SRCS}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re