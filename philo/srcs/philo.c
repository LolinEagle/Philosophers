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

t_philo	*philo_init(unsigned int *argv)
{
	unsigned int	i;
	t_philo			*phi;
	t_philo			*tmp;

	phi = ft_philo_new(argv, NULL);
	if (!phi)
		ft_exit_philo(argv, phi);
	tmp = phi;
	i = 1;
	while (++i < argv[0])
	{
		tmp->next = ft_philo_new(argv, &tmp->fork_r);
		if (!tmp->next)
			ft_exit_philo(argv, phi);
		tmp = tmp->next;
	}
	tmp->next = ft_philo_new_last(argv, tmp->fork_r, phi->fork_l);
	if (!tmp->next)
		ft_exit_philo(argv, phi);
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
	int		i;
	t_philo	*phi;

	i = 0;
	while (i < ac - 1)
		printf("[%u]\n", argv[i++]);
	phi = philo_init(argv);
	philo_create(phi);
	philo_join(phi);
	ft_philo_free(phi);
}
