/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:05 by tmaillar          #+#    #+#             */
/*   Updated: 2024/03/29 09:39:28 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/philo.h"

int    error_msg(char *str, char *str2)
{
    ft_putstr_fd("Philo : ", STDERR_FILENO);
    if (str != NULL)
        ft_putendl_fd(str, STDERR_FILENO);
    if (str2 != NULL)
        ft_putendl_fd(str2, STDERR_FILENO);
    return (EXIT_FAILURE);
}
void    destroy_all(t_table *table)
{
    int i;
    
    i = 0;
    while (i < table->nb_philo)
    {
        pthread_mutex_destroy(&table->philo[i].philo_mutex);
        pthread_mutex_destroy(&table->fork_mutex[i].fork);
        i++;
    }
    pthread_mutex_destroy(&table->meal_mutex);
    // pthread_mutex_destroy(&table->monitor_mutex);
    pthread_mutex_destroy(&table->write_mutex);
}

// void	ft_free(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	if (philo == NULL)
// 		return ;
// 	while (philo[i])
// 	{
// 		free(philo[i]);
//         philo[i] = NULL;
//     	i++;
// 	}
// 	free(philo);
//     philo = NULL;
// }