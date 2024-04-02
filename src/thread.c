/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:35 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 08:59:46 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    *thread_routine(void *data)
{
    t_philo *philo;
    
    philo = (t_philo *)data;
    if (check_bool(&philo->table->table_mutex, &philo->table->someone_died) == true)
        return (NULL);
    if (check_bool(&philo->table->table_mutex, &philo->table->is_finish) == true)
        return (NULL);
    assign_data(&philo->philo_mutex, &philo->last_meal_time, philo->table->starting_time);
    synchro_philo(philo->table->starting_time);
    print_status(philo, THINK);
    if (philo->table->time_to_die == 0)
        return (NULL);
    if (philo->philo_id % 2 == 0)
        usleep(10000);
    while (simulation_ended(philo->table) == false)
    {
        eat_sleep_routine(philo);
        think_routine(philo);
    }
    return (NULL);
}

void    *thread_solo_routine(void *data)
{
    t_philo *philo;
    
    philo = (t_philo *)data;
    print_status(philo, FORK);
    wait_die(philo->table, philo->table->time_to_die);
    print_status(philo, DIED);
    return (NULL);
}