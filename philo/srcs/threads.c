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

unsigned int	ft_get_time(struct timeval old)
{
	unsigned int	sec;
	int				usec;
	struct timeval	new;

	gettimeofday(&new, NULL);
	sec = new.tv_sec - old.tv_sec;
	usec = new.tv_usec - old.tv_usec;
	sec = (sec * 1000000) + usec;
	old = new;
	return (sec / 1000);
}

unsigned int	ft_eat(struct timeval last, t_philo *phi)
{
	unsigned int	i;

	i = ft_get_time(last);
	if (i > phi->argv[2])
	{
		printf("%u %i died\n", i, phi->order);
		return (1);
	}
	return (0);
}

void	*ft_start_routine(void *arg)
{
	t_philo			*phi;
	struct timeval	time;
	struct timeval	last;

	phi = arg;
	gettimeofday(&time, NULL);
	gettimeofday(&last, NULL);
	while (phi->ac == 5)
	{
		printf("%u %i is thinking\n", ft_get_time(time), phi->order);
		pthread_mutex_lock(&phi->fork_r);
		printf("%u %i has taken a fork\n", ft_get_time(time), phi->order);
		pthread_mutex_lock(&phi->fork_l);
		printf("%u %i has taken a fork\n", ft_get_time(time), phi->order);
		break ;
		if (ft_eat(last, phi))
			return (EXIT_SUCCESS);
		printf("%u %i is eating\n", ft_get_time(time), phi->order);
		usleep(phi->argv[2] * 1000);
		pthread_mutex_unlock(&phi->fork_r);
		pthread_mutex_unlock(&phi->fork_l);
		printf("%u %i is sleeping\n", ft_get_time(time), phi->order);
		usleep(phi->argv[3] * 1000);
	}
	return (EXIT_SUCCESS);
}
