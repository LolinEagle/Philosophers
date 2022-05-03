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

t_philo	*ft_philo_new_first(int ac, unsigned int *argv)
{
	t_philo				*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	if (pthread_mutex_init(&res->fork_r, NULL) != 0)
	{
		free(res);
		ft_putstr_fd("Error : mutex init fail\n", 2);
		return (NULL);
	}
	res->order = 1;
	res->ac = ac;
	res->argv = argv;
	res->next = NULL;
	return (res);
}

t_philo	*ft_philo_new(int ac, unsigned int *argv, pthread_mutex_t fork_r)
{
	static unsigned int	i = 1;
	t_philo				*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	res->fork_l = fork_r;
	if (pthread_mutex_init(&res->fork_r, NULL) != 0)
	{
		free(res);
		ft_putstr_fd("Error : mutex init fail\n", 2);
		return (NULL);
	}
	i++;
	res->order = i;
	res->ac = ac;
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
