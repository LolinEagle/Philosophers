/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:20:44 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/03 12:20:47 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_get_time(struct timeval time)
{
	unsigned int	sec;
	int				usec;
	struct timeval	new;

	gettimeofday(&new, NULL);
	sec = new.tv_sec - time.tv_sec;
	usec = new.tv_usec - time.tv_usec;
	return (((sec * 1000000) + usec) / 1000);
}

int	ft_fork(t_philo *phi, struct timeval time)
{
	if (*phi->die == 1)
		return (1);
	printf("%u %i is thinking\n", ft_get_time(time), phi->order);
	if (phi->order % 2 == 1)
	{
		pthread_mutex_lock(&phi->fork);
		if (*phi->die == 1)
			return (1);
		printf("%u %i has taken a fork\n", ft_get_time(time), phi->order);
	}
	if (phi->prev == NULL)
		return (0);
	pthread_mutex_lock(&phi->prev->fork);
	if (*phi->die == 1)
		return (1);
	printf("%u %i has taken a fork\n", ft_get_time(time), phi->order);
	if (phi->order % 2 == 0)
	{
		pthread_mutex_lock(&phi->fork);
		if (*phi->die == 1)
			return (1);
		printf("%u %i has taken a fork\n", ft_get_time(time), phi->order);
	}
	return (0);
}

int	ft_eat(t_philo *phi, struct timeval time, struct timeval last)
{
	unsigned int	i;

	i = ft_get_time(last);
	if (i > phi->argv[1] || phi->prev == NULL)
	{
		*phi->die = 1;
		printf("%u %i died\n", i, phi->order);
		return (1);
	}
	if (*phi->die == 1)
		return (1);
	printf("%u %i is eating\n", ft_get_time(time), phi->order);
	usleep(phi->argv[2] * 1000);
	pthread_mutex_unlock(&phi->fork);
	pthread_mutex_unlock(&phi->prev->fork);
	return (0);
}

void	ft_philo_mutex_unlock(t_philo *p, unsigned int argv)
{
	unsigned int	i;
	static int		unloked = 0;
	t_philo			*tmp;

	if (unloked || p->prev == NULL)
		return ;
	tmp = p->prev;
	i = 0;
	while (i < argv)
	{
		pthread_mutex_unlock(&p->fork);
		p = tmp;
		tmp = p->prev;
		i++;
	}
	pthread_mutex_unlock(&p->fork);
	unloked = 1;
}

void	*ft_start_routine(void *arg)
{
	unsigned int	i;
	t_philo			*phi;
	struct timeval	time;
	struct timeval	last;

	phi = arg;
	gettimeofday(&time, NULL);
	gettimeofday(&last, NULL);
	i = 0;
	while (phi->ac == 5 || i < phi->argv[4])
	{
		if (ft_fork(phi, time))
			break ;
		if (ft_eat(phi, time, last))
			break ;
		gettimeofday(&last, NULL);
		if (*phi->die == 1)
			break ;
		printf("%u %i is sleeping\n", ft_get_time(time), phi->order);
		usleep(phi->argv[3] * 1000);
		i++;
	}
	ft_philo_mutex_unlock(phi, phi->argv[0]);
	return (EXIT_SUCCESS);
}
