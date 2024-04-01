/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:35 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/01 14:19:14 by tmaillar         ###   ########.fr       */
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
    synchro_philo2(philo->table->starting_time);
    if (philo->table->time_to_die == 0)
        return (NULL);
    if (philo->philo_id % 2 == 0)
        think_routine(philo);
    while (simulation_ended2(philo->table) == false)
    {
        eat_routine(philo);
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