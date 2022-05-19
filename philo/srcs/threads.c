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

int	ft_fork_deadlock(t_philo *phi, struct timeval time, int bol)
{
	if (phi->order % 2 == bol)
	{
		pthread_mutex_lock(&phi->fork);
		pthread_mutex_lock(phi->log);
		if (*phi->die == 1)
		{
			pthread_mutex_unlock(phi->log);
			pthread_mutex_unlock(&phi->fork);
			return (1);
		}
		phi->lock[0] = 1;
		pthread_mutex_unlock(phi->log);
		if (ft_log("%u %i has taken a fork\n", phi, time))
			return (1);
	}
	return (0);
}

int	ft_fork(t_philo *phi, struct timeval time)
{
	if (phi->prev == NULL)
		return (0);
	if (ft_log("%u %i is thinking\n", phi, time))
		return (1);
	if (ft_fork_deadlock(phi, time, 1))
		return (1);
	pthread_mutex_lock(&phi->prev->fork);
	pthread_mutex_lock(phi->log);
	if (*phi->die == 1)
	{
		pthread_mutex_unlock(phi->log);
		pthread_mutex_unlock(&phi->prev->fork);
		return (1);
	}
	phi->lock[1] = 1;
	pthread_mutex_unlock(phi->log);
	if (ft_log("%u %i has taken a fork\n", phi, time))
		return (1);
	if (ft_fork_deadlock(phi, time, 0))
		return (1);
	return (0);
}

int	ft_eat(t_philo *phi, struct timeval time, struct timeval last)
{
	unsigned int	i;

	i = ft_get_time(last);
	pthread_mutex_lock(phi->log);
	if ((i > phi->argv[1] || phi->prev == NULL) && *phi->die == 0)
	{
		*phi->die = 1;
		printf("%u %i died\n", i, phi->order);
		pthread_mutex_unlock(phi->log);
		return (1);
	}
	pthread_mutex_unlock(phi->log);
	if (ft_log("%u %i is eating\n", phi, time))
		return (1);
	usleep(phi->argv[2] * 1000);
	pthread_mutex_lock(phi->log);
	phi->lock[0] = 0;
	phi->lock[1] = 0;
	pthread_mutex_unlock(phi->log);
	pthread_mutex_unlock(&phi->fork);
	pthread_mutex_unlock(&phi->prev->fork);
	return (0);
}

void	ft_philo_mutex_unlock(t_philo *phi)
{
	pthread_mutex_lock(phi->log);
	if (phi->prev == NULL)
	{
		pthread_mutex_unlock(phi->log);
		return ;
	}
	if (phi->lock[0] == 1)
		pthread_mutex_unlock(&phi->fork);
	if (phi->lock[1] == 1)
		pthread_mutex_unlock(&phi->prev->fork);
	pthread_mutex_unlock(phi->log);
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
	i = -1;
	while (phi->ac == 5 || ++i < phi->argv[4])
	{
		if (ft_fork(phi, time))
			break ;
		if (ft_eat(phi, time, last))
			break ;
		gettimeofday(&last, NULL);
		if (ft_log("%u %i is sleeping\n", phi, time))
			break ;
		usleep(phi->argv[3] * 1000);
	}
	ft_philo_mutex_unlock(phi);
	return (EXIT_SUCCESS);
}
