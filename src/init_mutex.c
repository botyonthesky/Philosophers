/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:17 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 10:14:29 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutex(t_table *table)
{
	if (init_fork(table) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_write(table) == EXIT_FAILURE)
	{
		clean_fork_mutex(table);
		return (EXIT_FAILURE);
	}
	if (init_table(table) == EXIT_FAILURE)
	{
		clean_fork_mutex(table);
		pthread_mutex_destroy(&table->write_mutex);
		return (EXIT_FAILURE);
	}
	if (init_death(table) == EXIT_FAILURE)
	{
		clean_fork_mutex(table);
		pthread_mutex_destroy(&table->write_mutex);
		pthread_mutex_destroy(&table->table_mutex);
	}
	return (EXIT_SUCCESS);
}

int	init_fork(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork_mutex[i].fork, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->fork_mutex[i].fork);
			error_msg(INIT_ERR, NULL);
			return (EXIT_FAILURE);
		}
		table->fork_mutex[i].fork_id = i;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_write(t_table *table)
{
	if (secure_init(&table->write_mutex) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_table(t_table *table)
{
	if (secure_init(&table->table_mutex) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_death(t_table *table)
{
	if (secure_init(&table->death_mutex) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
