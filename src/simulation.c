/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:56:37 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 10:31:58 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	start_simulation(t_table *table)
{
	int		i;
	long	time;

	i = 0;
	time = (get_time() + (table->nb_philo * 2 * 10));
	table->starting_time = time;
	if (table->nb_philo == 1)
		return (solo_routine(table));
	while (i < table->nb_philo)
	{
		if (secure_create(&table->philo[i].thread,
				thread_routine, &table->philo[i]) == 1)
			return (EXIT_FAILURE);
		i++;
	}
	if (secure_create(&table->monitor, monitor, table) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	join_and_finish(t_table *table)
{
	int	i;

	i = 0;
	if (table->nb_fork > 1)
	{
		while (i < table->nb_philo)
		{
			pthread_join(table->philo[i].thread, NULL);
			i++;
		}
		pthread_join(table->monitor, NULL);
		assign_bool(&table->table_mutex, &table->is_finish, true);
	}
}

bool	simulation_ended(t_table *table)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&table->table_mutex);
	if (table->is_finish == true)
		ret = true;
	pthread_mutex_unlock(&table->table_mutex);
	return (ret);
}

void	synchro_philo(long time)
{
	while (get_time() < time)
		continue ;
}
