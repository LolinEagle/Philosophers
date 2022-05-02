/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:06:38 by frrusso           #+#    #+#             */
/*   Updated: 2022/04/25 13:06:52 by frrusso          ###   ########.fr       */
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

void	*ft_start_routine(void *arg)
{
	unsigned int	i;
	t_philo			*phi;
	struct timeval	time;
	struct timeval	last;

	phi = arg;
	gettimeofday(&time, NULL);
	gettimeofday(&last, NULL);
	while (1)
	{
		pthread_mutex_lock(&phi->fork_r);
		printf("%u %i has taken a fork\n", ft_get_time(time), phi->order);
		pthread_mutex_lock(&phi->fork_l);
		printf("%u %i has taken a fork\n", ft_get_time(time), phi->order);
		i = ft_get_time(last);
		if (i > phi->argv[2])
		{
			printf("%u %i died\n", ft_get_time(last), phi->order);
			return (EXIT_SUCCESS);
		}
		printf("%u %i is eating\n", ft_get_time(time), phi->order);
		usleep(phi->argv[2] * 1000);
		pthread_mutex_unlock(&phi->fork_r);
		pthread_mutex_unlock(&phi->fork_l);
		printf("%u %i is sleeping\n", ft_get_time(time), phi->order);
		usleep(phi->argv[3] * 1000);
		printf("%u %i is thinking\n", ft_get_time(time), phi->order);
	}
	return (EXIT_SUCCESS);
}

t_philo	*ft_philo_new(unsigned int *argv, pthread_mutex_t *fork_l)
{
	static unsigned int	i = 0;
	t_philo				*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	if (!fork_l && pthread_mutex_init(&res->fork_l, NULL) != 0)
	{
		free(res);
		ft_putstr_fd("Error : mutex init fail\n", 2);
		return (NULL);
	}
	// else
	// 	res->fork_l = *fork_l;
	if (pthread_mutex_init(&res->fork_r, NULL) != 0)
	{
		free(res);
		ft_putstr_fd("Error : mutex init fail\n", 2);
		return (NULL);
	}
	i++;
	res->order = i;
	res->argv = argv;
	res->next = NULL;
	return (res);
}

t_philo	*ft_philo_new_last(
	unsigned int *argv, pthread_mutex_t fork_l, pthread_mutex_t fork_r)
{
	t_philo	*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	res->fork_l = fork_l;
	res->fork_r = fork_r;
	res->order = argv[0];
	res->argv = argv;
	res->next = NULL;
	return (res);
}

void	ft_philo_free(t_philo *p)
{
	t_philo	*tmp;

	tmp = p->next;
	while (tmp)
	{
		free(p);
		p = tmp;
		tmp = p->next;
	}
	free(p);
}
