/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:14:26 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 09:16:32 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(void)
{
	struct timeval	start;

	if (gettimeofday(&start, NULL) == 0)
		return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
	else
	{
		printf(TIME);
		return (EXIT_FAILURE);
	}
}

void	wait_eat(t_table *table, long timing)
{
	long	time;

	time = get_time() + timing;
	while (get_time() < time)
	{
		if (simulation_ended(table))
			break ;
		usleep(100);
	}
}

void	wait_sleep(t_table *table, long timing)
{
	long	time;

	time = get_time() + timing;
	while (get_time() < time)
	{
		if (simulation_ended(table))
			break ;
		usleep(100);
	}
}

void	wait_think(t_table *table, t_philo *philo)
{
	long	time;
	long	think_time;
	long	last_meal;
	
	think_time = table->time_to_think;
	last_meal = philo->last_meal_time;
	time = get_time();
	if (time - last_meal + think_time >= table->time_to_die)
		think_time = 2;
	if (think_time < 0)
		think_time = 0;
	if (think_time > 0)
	{
		print_status(philo, THINK);
		wait_sleep(table, think_time);
	}
	// pthread_mutex_lock(&table->philo->philo_mutex);
	// thinking_time = (table->time_to_die
	// 		- (get_time() - table->philo->last_meal_time)
	// 		- table->time_to_eat) / 2;
	// pthread_mutex_unlock(&table->philo->philo_mutex);
	
	// if (thinking_time > 600)
	// 	thinking_time = 200;
	// if (time + thinking_time >= time - table->time_to_die)
	// 	thinking_time = 50;
	// if (philo->last_meal_time + table->time_to_die >= time + thinking_time)
	// 	thinking_time = (philo->last_meal_time + table->time_to_die - time) - 10;
	// lol(philo, "is thinking", philo->philo_id);
}

void	wait_die(t_table *table, long timing)
{
	long	time;

	time = get_time() + timing;
	while (get_time() < time)
	{
		if (simulation_ended(table))
			break ;
		usleep(100);
	}
}
