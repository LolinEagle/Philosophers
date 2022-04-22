/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:04:59 by frrusso           #+#    #+#             */
/*   Updated: 2022/04/21 13:05:00 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"// UNISTD usleep
# include <string.h>// memset
# include <stdio.h>// printf
# include <sys/time.h>// gettimeofday
# include <pthread.h>// pthread_create pthread_detach pthread_join
# include <limits.h>

# define ERR_ARG "Usage : ./philo philosophers die eat sleep [times]\n"
# define ERR_INT "All your arguments must be between 0 and 4294967295\n"

// ft_is_uint.c	3 functions
int	ft_is_uint(int ac, char **av);

// philo.c		0 functions

// main.c		2 functions

#endif
