/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 17:08:48 by frrusso           #+#    #+#             */
/*   Updated: 2022/04/22 17:08:51 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_uint_digit(char *av)
{
	int	i;

	i = 0;
	if (av[i] == '+' && ft_isdigit(av[i + 1]))
		i++;
	while (av[i])
	{
		if (ft_isdigit(av[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_is_uint_toobig(char *av)
{
	int		i;
	char	*max;

	i = ft_strlen(av);
	if (i < 10 || (i == 10 && av[0] == '+'))
		return (0);
	if (i > 11 || (i == 11 && ft_isdigit(av[0])))
		return (1);
	max = "4294967295";
	if (av[0] == '+')
		av++;
	i = 10;
	while (i && *av >= *max)
	{
		if (*av > *max)
			return (1);
		av++;
		max++;
		i--;
	}
	return (0);
}

int	ft_is_uint(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!ft_is_uint_digit(av[i]))
			return (0);
		if (ft_is_uint_toobig(av[i]))
			return (0);
	}
	return (1);
}

unsigned int	ft_get_time(struct timeval time)
{
	unsigned int	sec;
	int				usec;
	struct timeval	new;

	gettimeofday(&new, NULL);
	sec = new.tv_sec - time.tv_sec;
	usec = new.tv_usec - time.tv_usec;
	return (((sec * 1000000) + usec) / 1000);
}
