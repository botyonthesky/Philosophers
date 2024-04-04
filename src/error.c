/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:05 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 13:36:10 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_msg(char *str, char *str2)
{
	ft_putstr_fd("Philo : ", STDOUT_FILENO);
	if (str != NULL)
		ft_putendl_fd(str, STDOUT_FILENO);
	if (str2 != NULL)
		ft_putendl_fd(str2, STDOUT_FILENO);
	return (EXIT_FAILURE);
}

void	destroy_all(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->nb_philo)
	{
		philo = table->philo + i;
		pthread_mutex_destroy(&philo->philo_mutex);
		pthread_mutex_destroy(&table->fork_mutex[i].fork);
		i++;
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->death_mutex);
	free(table->fork_mutex);
	free(table->philo);
}

void	clean_fork_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->fork_mutex[i].fork);
		i++;
	}
	free(table->fork_mutex);
}
