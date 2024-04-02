/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:54:45 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 10:19:09 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_argv(char **av)
{
	int		i;
	long	nb;

	i = 1;
	while (av[i])
	{
		nb = ft_atol(av[i]);
		if (is_valid_digit(nb) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_int(char **argv)
{
	int		i;
	int		nb;
	long	int_max;

	i = 1;
	nb = 0;
	int_max = 2147483647;
	while (argv[i])
	{
		nb = ft_atol(argv[i]);
		if (nb > int_max || nb < 0)
			return (1);
		i++;
	}
	return (0);
}

long	check_data(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

bool	check_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}
