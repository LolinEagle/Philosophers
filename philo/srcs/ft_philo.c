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

void	*ft_start_routine(void *arg)
{
	static unsigned int	i = 0;
	unsigned int		*argv;

	argv = (unsigned int *)arg;
	i++;
	printf("thread%i\n", i);
	return (EXIT_SUCCESS);
}

t_philo	*ft_philo_new(unsigned int *argv)
{
	static unsigned int	i = 0;
	t_philo				*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	i++;
	res->order = i;
	res->next = NULL;
	if (pthread_mutex_init(&res->fork_r, NULL) != 0)
	{
		free(res);
		ft_putstr_fd("Error : mutex init fail\n", 2);
		return (NULL);
	}
	pthread_create(&res->thread, NULL, ft_start_routine, &argv);
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
