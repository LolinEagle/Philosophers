/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:04:50 by frrusso           #+#    #+#             */
/*   Updated: 2022/04/21 13:04:54 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit_philo(t_data *data, t_philo *phi)
{
	if (data)
	{
		pthread_mutex_destroy(data->log);
		free(data->argv);
		free(data->die);
		free(data);
	}
	if (phi)
		ft_philo_free(phi);
	ft_putstr_fd("Error : struct init fail\n", 2);
	exit(EXIT_FAILURE);
}

t_philo	*philo_init(int ac, unsigned int *argv)
{
	unsigned int	i;
	t_philo			*phi;
	t_philo			*tmp;
	t_data			*data;

	data = ft_data_new(ac, argv);
	if (!data)
		ft_exit_philo(data, NULL);
	phi = ft_philo_new(data, NULL);
	if (!phi)
		ft_exit_philo(data, phi);
	tmp = phi;
	i = 0;
	while (++i < argv[0])
	{
		tmp->next = ft_philo_new(data, tmp);
		if (!tmp->next)
			ft_exit_philo(data, phi);
		tmp = tmp->next;
	}
	if (argv[0] != 1)
		phi->prev = tmp;
	free(data);
	return (phi);
}

void	philo_create(t_philo *phi)
{
	t_philo	*tmp;

	tmp = phi->next;
	while (tmp)
	{
		pthread_create(&phi->thread, NULL, ft_start_routine, phi);
		phi = tmp;
		tmp = tmp->next;
	}
	pthread_create(&phi->thread, NULL, ft_start_routine, phi);
}

void	philo_join(t_philo *phi)
{
	t_philo	*tmp;

	tmp = phi->next;
	while (tmp)
	{
		pthread_join(phi->thread, NULL);
		phi = tmp;
		tmp = tmp->next;
	}
	pthread_join(phi->thread, NULL);
}

void	philo(int ac, unsigned int *argv)
{
	t_philo	*phi;

	phi = philo_init(ac, argv);
	philo_create(phi);
	philo_join(phi);
	ft_philo_free(phi);
}
