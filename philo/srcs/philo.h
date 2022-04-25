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
# include <threads.h>// pthread_create pthread_detach pthread_join

# define ERR_ARGC "Usage : ./philo philosophers die eat sleep [times]\n"
# define ERR_UINT "All your arguments must be between 0 and 4294967295\n"

typedef struct s_philo
{
	thrd_t			thread;
	unsigned int	order;
	struct s_philo	*next;
}					t_philo;

// ft_is_uint.c	3 functions
int		ft_is_uint(int ac, char **av);

// ft_philo		2 functions
t_philo	*ft_philo_new(void);
void	ft_philo_free(t_philo *p);

// philo.c		1 functions
void	philo(int ac, unsigned int	*argv);

// main.c		5 functions

#endif
