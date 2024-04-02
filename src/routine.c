/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:57:05 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 08:56:50 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat_sleep_routine(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->left_fork->fork);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->right_fork->fork);
	print_status(philo, FORK);
	if (simulation_ended(philo->table) == false)
		increase_data(&philo->philo_mutex, &philo->count_meal);
	print_status(philo, EAT);
	time = get_time();
	assign_data(&philo->philo_mutex, &philo->last_meal_time, time);
	wait_eat(philo->table, philo->table->time_to_eat);
	print_status(philo, SLEEP);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	wait_sleep(philo->table, philo->table->time_to_sleep);
}

void	think_routine(t_philo *philo)
{
	if (check_bool(&philo->table->table_mutex,
			&philo->table->someone_died) == true)
		return ;
	if (check_bool(&philo->table->table_mutex,
			&philo->table->is_finish) == true)
		return ;
	wait_think(philo->table, philo);
}

// int	solo_routine(t_table *table)
// {
// 	long	time;

// 	time = get_time() + (table->nb_philo * 2 * 10);
// 	assign_data(&table->table_mutex, &table->starting_time, time);
// 	synchro_philo(table->starting_time);
// 	if (pthread_create(&table->philo[0].thread, NULL,
// 			thread_solo_routine, &table->philo[0]) != 0)
// 	{
// 		destroy_all(table);
// 		error_msg(CREATE_ERR, NULL);
// 		return (EXIT_FAILURE);
// 	}
// 	pthread_join(table->philo[0].thread, NULL);
// 	assign_bool(&table->table_mutex, &table->is_finish, true);
// 	return (EXIT_SUCCESS);
// }

int	solo_routine(t_table *table)
{
	long	time;

	time = get_time() + (table->nb_philo * 2 * 10);
	assign_data(&table->table_mutex, &table->starting_time, time);
	synchro_philo(table->starting_time);
	if (secure_create(&table->philo[0].thread, thread_solo_routine, &table->philo[0]) == 1)
		return (EXIT_FAILURE);
	pthread_join(table->philo[0].thread, NULL);
	assign_bool(&table->table_mutex, &table->is_finish, true);
	return (EXIT_SUCCESS);
}
