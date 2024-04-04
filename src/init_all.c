/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:28:10 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 13:36:34 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_init(t_table *table)
{
	if (init_alloc(table) == 1)
		return (EXIT_FAILURE);
	if (init_mutex(table) == 1)
		return (EXIT_FAILURE);
	if (init_philo(table) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_argv(t_table *table, char **av)
{
	if (check_argv(av) == 1)
		return (error_msg(NB_ARGV, NULL));
	table->nb_philo = ft_atol(av[1]);
	table->nb_fork = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (av[5] != NULL)
		table->nb_meal = ft_atol(av[5]);
	else
		table->nb_meal = -1;
	if (table->nb_philo % 2 == 0)
		table->time_to_think = table->time_to_eat
			- table->time_to_sleep - 10;
	else
		table->time_to_think = (table->time_to_eat * 2)
			- table->time_to_sleep - 10;
	table->someone_died = false;
	table->thread_ready = false;
	table->is_finish = false;
	table->starting_time = 0;
	table->nb_thread = 0;
	return (EXIT_SUCCESS);
}

int	init_alloc(t_table *table)
{
	table->philo = ft_calloc(table->nb_philo, (sizeof(t_philo)));
	if (table->philo == NULL)
		return (EXIT_FAILURE);
	table->fork_mutex = ft_calloc(table->nb_philo, (sizeof(t_fork)));
	if (table->fork_mutex == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->nb_philo)
	{
		philo = table->philo + i;
		philo->philo_id = i + 1;
		philo->count_meal = 0;
		philo->is_full = false;
		if (secure_init(&philo->philo_mutex) == 1)
			return (EXIT_FAILURE);
		philo->table = table;
		manage_fork(philo, table->fork_mutex, i);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	manage_fork(t_philo *philo, t_fork *forks, int i)
{
	int	nb_philo;

	nb_philo = philo->table->nb_philo;
	philo->left_fork = &forks[(i + 1) % nb_philo];
	philo->right_fork = &forks[i];
	if (philo->philo_id % 2 == 0)
	{
		philo->left_fork = &forks[i];
		philo->right_fork = &forks[(i + 1) % nb_philo];
	}
}
