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

t_data	*ft_data_new_free(int *die, t_data *res)
{
	free(die);
	free(res);
	ft_putstr_fd("Error : mutex init fail\n", 2);
	return (NULL);
}

t_data	*ft_data_new(int ac, unsigned int *argv)
{
	pthread_mutex_t	*log;
	int				*die;
	t_data			*res;

	res = malloc(sizeof(t_data));
	if (!res)
		return (NULL);
	die = malloc(sizeof(int));
	if (!die)
	{
		free(res);
		return (NULL);
	}
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
	t_philo				*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	if (pthread_mutex_init(&res->fork, NULL) != 0)
	{
		free(res);
		ft_putstr_fd("Error : mutex init fail\n", 2);
		return (NULL);
	}
	res->log = data->log;
	res->die = data->die;
	res->ac = data->ac;
	res->argv = data->argv;
	i++;
	res->order = i;
	res->prev = prev;
	res->next = NULL;
	return (res);
}

void	ft_philo_free(t_philo *p)
{
	t_philo	*tmp;

	pthread_mutex_destroy(p->log);
	free(p->log);
	free(p->die);
	tmp = p->next;
	while (tmp)
	{
		pthread_mutex_destroy(&p->fork);
		free(p);
		p = tmp;
		tmp = p->next;
	}
	pthread_mutex_destroy(&p->fork);
	free(p);
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
