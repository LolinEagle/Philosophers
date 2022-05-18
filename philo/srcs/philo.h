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

# include <unistd.h>// usleep
# include <stdlib.h>// malloc free
# include <string.h>// memset
# include <stdio.h>// printf
# include <sys/time.h>// gettimeofday
# include <pthread.h>// pthread_create pthread_detach pthread_join
// pthread_mutex_init pthread_mutex_destroy
// pthread_mutex_lock pthread_mutex_unlock

# define ERR_ARGC "Usage : ./philo philosophers die eat sleep [times]\n"
# define ERR_UINT "All your arguments must be between 0 and 4294967295\n"

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*log;
	unsigned int	*die;
	int				ac;
	unsigned int	*argv;
	unsigned int	*lock;
	unsigned int	order;
	struct s_philo	*prev;
	struct s_philo	*next;
}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	*log;
	unsigned int	*die;
	int				ac;
	unsigned int	*argv;
}					t_data;

// libft.c		4 functions
int				ft_isdigit(int c);
int				ft_space(char c);
size_t			ft_strlen(const char *s);
void			ft_putstr_fd(char *s, int fd);

// libphilo.c	4 functions
int				ft_is_uint(int ac, char **av);
unsigned int	ft_get_time(struct timeval time);

// threads.c	5 functions
void			*ft_start_routine(void *arg);

// struct.c		5 functions
t_data			*ft_data_new(int ac, unsigned int *argv);
t_philo			*ft_philo_new(t_data *data, t_philo *prev);
void			ft_philo_free(t_philo *p);
int				ft_log(char *str, t_philo *phi, struct timeval time);

// philo.c		5 functions
void			philo(int ac, unsigned int	*argv);

// main.c		5 functions

#endif
