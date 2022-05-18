/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:06:38 by frrusso           #+#    #+#             */
/*   Updated: 2022/04/25 13:06:52 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_data_new_free(void *ptr, void *res)
{
	if (ptr)
		free(ptr);
	free(res);
	ft_putstr_fd("Error : init fail\n", 2);
	return (NULL);
}

t_data	*ft_data_new(int ac, unsigned int *argv)
{
	pthread_mutex_t	*log;
	unsigned int	*die;
	t_data			*res;

	res = malloc(sizeof(t_data));
	if (!res)
		return (NULL);
	die = malloc(sizeof(int));
	if (!die)
		return (ft_data_new_free(NULL, res));
	*die = 0;
	log = malloc(sizeof(pthread_mutex_t));
	if (!log || pthread_mutex_init(log, NULL) != 0)
		return (ft_data_new_free(die, res));
	res->log = log;
	res->die = die;
	res->ac = ac;
	res->argv = argv;
	return (res);
}

t_philo	*ft_philo_new(t_data *data, t_philo *prev)
{
	static unsigned int	i = 0;
	unsigned int		*lock;
	t_philo				*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	lock = malloc(sizeof(unsigned int) * 2);
	if (!lock)
		return (ft_data_new_free(NULL, res));
	lock[0] = 0;
	lock[1] = 0;
	if (pthread_mutex_init(&res->fork, NULL) != 0)
		return (ft_data_new_free(lock, res));
	res->log = data->log;
	res->die = data->die;
	res->ac = data->ac;
	res->argv = data->argv;
	res->lock = lock;
	i++;
	res->order = i;
	res->prev = prev;
	res->next = NULL;
	return (res);
}

void	ft_philo_free(t_philo *phi)
{
	t_philo	*tmp;

	pthread_mutex_destroy(phi->log);
	free(phi->log);
	free(phi->die);
	tmp = phi->next;
	while (tmp)
	{
		free(phi->lock);
		pthread_mutex_destroy(&phi->fork);
		free(phi);
		phi = tmp;
		tmp = phi->next;
	}
	free(phi->lock);
	pthread_mutex_destroy(&phi->fork);
	free(phi);
}

int	ft_log(char *str, t_philo *phi, struct timeval time)
{
	pthread_mutex_lock(phi->log);
	if (*phi->die == 1)
	{
		pthread_mutex_unlock(phi->log);
		return (1);
	}
	printf(str, ft_get_time(time), phi->order);
	pthread_mutex_unlock(phi->log);
	return (0);
}
