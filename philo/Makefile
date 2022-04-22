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
LIBFT	= 	libft/libft.a
SRCS	= 	${addprefix srcs/, ft_is_uint.c philo.c main.c}
OBJS	= 	${SRCS:.c=.o}

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:${OBJS}
	${MAKE} -C libft
	${CC} ${FLAGS} ${OBJS} ${LIBFT} -o ${NAME}

all:${NAME}

clean:
	${MAKE} clean -C libft
	${RM} ${OBJS}

fclean:clean
	${MAKE} fclean -C libft
	${RM} ${NAME}

re:fclean all

.PHONY: all clean fclean re
