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

void	ft_exit_philo(unsigned int *argv, t_philo *phi)
{
	free(argv);
	ft_philo_free(phi);
	ft_putstr_fd("Error : struct init fail\n", 2);
	exit(EXIT_FAILURE);
}

t_philo	*philo_init(int ac, unsigned int *argv)
{
	unsigned int	i;
	t_philo			*phi;
	t_philo			*tmp;

	phi = ft_philo_new_first(ac, argv);
	if (!phi)
		ft_exit_philo(argv, phi);
	tmp = phi;
	i = 0;
	while (++i < argv[0])
	{
		tmp->next = ft_philo_new(ac, argv, tmp->fork_r);
		if (!tmp->next)
			ft_exit_philo(argv, phi);
		tmp = tmp->next;
	}
	phi->fork_l = tmp->fork_r;
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
