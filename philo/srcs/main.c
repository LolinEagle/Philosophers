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

#include "philo.h"

int	ft_write_fd(char *str, int fd)
{
	size_t	i;

	i = ft_strlen(str);
	write(fd, str, i);
	return (EXIT_FAILURE);
}

unsigned int	ft_atou(char *str)
{
	int				i;
	unsigned int	res;

	res = 0;
	i = 0;
	while (ft_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res);
}

unsigned int	*ft_argv_init(int ac, char **av)
{
	int				i;
	unsigned int	*res;

	res = malloc(sizeof(unsigned int) * 5);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < ac - 1)
		res[i] = ft_atou(av[i + 1]);
	return (res);
}

int	ft_free_argv(unsigned int *argv)
{
	free(argv);
	return (ft_write_fd("Need at less one philosophers\n", 1));
}

int	main(int ac, char **av)
{
	unsigned int	*argv;

	if (ac < 5 || ac > 6)
		return (ft_write_fd(ERR_ARGC, 1));
	if (!ft_is_uint(ac, av))
		return (ft_write_fd(ERR_UINT, 1));
	argv = ft_argv_init(ac, av);
	if (!argv)
		return (ft_write_fd("Error : malloc in ft_argv_init\n", 2));
	if (argv[0] == 0)
		return (ft_free_argv(argv));
	philo(ac, argv);
	free(argv);
	return (EXIT_SUCCESS);
}
