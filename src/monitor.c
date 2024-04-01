/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:55:08 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/01 16:29:43 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    *monitor(void *data)
{
    t_table *table;

    table = (t_table *)data;
    if (table->nb_meal == 0)
        return (NULL);
    synchro_philo(table->starting_time);
    while (true)
    {
        if (simulation_end_bc_die(table) == true)
            return (NULL);
        usleep(1000);
    }
    return (NULL);
}
  
bool    simulation_end_bc_die(t_table *table)
{
    int i;
    bool    finish_meal;
    
    i = 0;
    finish_meal = true;
    while (i < table->nb_philo)
    {
        pthread_mutex_lock(&table->philo[i].philo_mutex);
        if (is_died(&table->philo[i]))
            return (true);
        if (table->nb_meal != -1)
        {
            if (table->philo[i].count_meal < table->nb_meal)
                finish_meal = false;       
        }
        pthread_mutex_unlock(&table->philo[i].philo_mutex);
        i++;        
    }
    if (table->nb_meal != -1 && finish_meal == true)
    {
        assign_bool(&table->table_mutex, &table->is_finish, true);
        return (true);
    }
    return (false);
}

bool    is_died(t_philo *philo)
{
    long time;

    time = get_time();
    if ((time - philo->last_meal_time) >= philo->table->time_to_die)
    {
        assign_bool(&philo->table->table_mutex, &philo->table->someone_died, true);
        assign_bool(&philo->table->table_mutex, &philo->table->is_finish, true);
        pthread_mutex_lock(&philo->table->write_mutex);
        printf("%ld %d died\n", (time - philo->table->starting_time), philo->philo_id);
        pthread_mutex_unlock(&philo->table->write_mutex);

        pthread_mutex_unlock(&philo->philo_mutex);
        return (true);
    }
    return (false);
}
