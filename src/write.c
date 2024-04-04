/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:55:55 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/03 12:06:19 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_status(t_philo *philo, int status)
{
	long	time;
	bool	is_finish;

	pthread_mutex_lock(&philo->table->write_mutex);
	pthread_mutex_lock(&philo->table->table_mutex);
	is_finish = philo->table->is_finish;
	time = get_time() - philo->table->starting_time;
	pthread_mutex_unlock(&philo->table->table_mutex);
	if (status == FORK && !is_finish)
		printf("%ld %d has taken a fork\n", time, philo->philo_id);
	if (status == THINK && !is_finish)
		printf("%ld %d is thinking\n", time, philo->philo_id);
	if (status == EAT && !is_finish)
		printf("%ld %d is eating\n", time, philo->philo_id);
	if (status == SLEEP && !is_finish)
		printf("%ld %d is sleeping\n", time, philo->philo_id);
	if (status == DIED && !is_finish)
		printf("%ld %d died\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

// void	print_status(t_philo *philo, int status)
// {
// 	long	time;
// 	bool	is_finish;

// 	pthread_mutex_lock(&philo->table->write_mutex);
// 	pthread_mutex_lock(&philo->table->table_mutex);
// 	is_finish = philo->table->is_finish;
// 	time = get_time() - philo->table->starting_time;
// 	pthread_mutex_unlock(&philo->table->table_mutex);
// 	if (status == FORK && !is_finish)
// 		printf("%ld %d has taken a fork\n", time, philo->philo_id);
// 	if (status == THINK && !is_finish)
// 		printf("%ld %d is thinking\n", time, philo->philo_id);
// 	if (status == EAT && !is_finish)
// 		printf("%ld %d is eating his %ld meal\n", time, philo->philo_id
			// , philo->count_meal);
// 	if (status == SLEEP && !is_finish)
// 		printf("%ld %d is sleeping\n", time, philo->philo_id);
// 	if (status == DIED && !is_finish)
// 		printf("%ld %d died\n", time, philo->philo_id);
// 	pthread_mutex_unlock(&philo->table->write_mutex);
// }