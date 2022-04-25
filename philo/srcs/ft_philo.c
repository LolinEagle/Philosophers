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

t_philo	*ft_philo_new(void)
{
	static int	i = 0;
	t_philo		*res;

	res = malloc(sizeof(t_philo));
	if (!res)
		return (NULL);
	i++;
	res->order = i;
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
