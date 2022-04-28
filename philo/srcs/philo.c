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
	unsigned int	i;
	t_philo			*phi;
	t_philo			*tmp;

	i = 0;
	while (i < (unsigned int)ac - 1)
		printf("[%u]\n", argv[i++]);
	phi = ft_philo_new(argv);
	if (!phi)
		ft_exit_philo(argv, phi);
	tmp = phi;
	i = 0;
	while (++i < argv[0])
	{
		tmp->next = ft_philo_new(argv);
		if (!tmp->next)
			ft_exit_philo(argv, phi);
		tmp = tmp->next;
	}
	philo_join(phi);
	ft_philo_free(phi);
}
