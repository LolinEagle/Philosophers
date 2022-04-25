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

void	philo(int ac, unsigned int	*argv)
{
	int		i;
	t_philo	*p;

	i = -1;
	while (++i < ac - 1)
		printf("[%u]\n", argv[i]);
	p = ft_philo_new();
	printf("%i - %p\n", p->order, p->next);
	ft_philo_free(p);
}
