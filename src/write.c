/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:55:55 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 09:01:58 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    lol(t_philo *philo, char *status, int i)
{
	pthread_mutex_lock(&philo->table->table_mutex);
	pthread_mutex_lock(&philo->table->write_mutex);
    printf("%ld %d %s\n", get_time() - philo->table->starting_time, i, status);
	pthread_mutex_unlock(&philo->table->write_mutex);
	pthread_mutex_unlock(&philo->table->table_mutex);
}

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
