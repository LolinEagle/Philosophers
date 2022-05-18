# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frrusso <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 13:04:19 by frrusso           #+#    #+#              #
#    Updated: 2022/04/21 13:04:30 by frrusso          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
RM		=	rm -f
FLAGS	=	-Wall -Wextra -Werror
NAME	=	philo
SRCS	=	${addprefix srcs/, libft.c libphilo.c struct.c philo.c main.c threads.c}
OBJS	= 	${SRCS:.c=.o}

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:${OBJS}
	${CC} ${FLAGS} ${OBJS} ${LIBFT} -pthread -o ${NAME}

all:${NAME}

clean:
	${RM} ${OBJS}

fclean:clean
	${RM} ${NAME}

re:fclean all

.PHONY: all clean fclean re
