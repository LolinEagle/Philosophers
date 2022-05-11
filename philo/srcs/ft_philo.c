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

t_philo	*ft_philo_new(int ac, unsigned int *argv, t_philo *prev, int *die)
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
	i++;
	res->order = i;
	res->die = die;
	res->ac = ac;
	res->argv = argv;
	res->prev = prev;
	res->next = NULL;
	return (res);
}

void	ft_philo_free(t_philo *p)
{
	t_philo	*tmp;

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
