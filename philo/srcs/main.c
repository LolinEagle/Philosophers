/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:04:39 by frrusso           #+#    #+#             */
/*   Updated: 2022/04/21 13:04:43 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philo.h"

int	ft_write_fd(char *str, int fd)
{
	size_t	i;

	i = ft_strlen(str);
	write(fd, str, i);
	return (EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (ft_write_fd(ERR_ARG, 1));
	if (!ft_is_uint(ac, av))
		return (ft_write_fd(ERR_INT, 1));
	i = 0;
	while (++i < ac)
		printf("%s\n", av[i]);
	return (EXIT_SUCCESS);
}
