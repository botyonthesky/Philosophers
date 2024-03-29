/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:55:08 by tmaillar          #+#    #+#             */
/*   Updated: 2024/03/29 17:20:11 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void    monitor(t_table *table)
{
    int i;
    
    bool alive;

    alive = true;
    // while (is_all_thread(&table->meal_mutex, &table->nb_thread, table->nb_philo) == false)
    //   ;
    i = 0;
    // usleep(200);
    while (alive == true)
    {
        while (i < table->nb_philo)
        {
            if (simulation_end_bc_die(table) == true)
            {
                assign_bool(&table->meal_mutex, &table->is_finish, true);
                print_status(table->philo, DIED, -1, 1);
                stop_simulation(table);
                alive = false;
            }
            i++;
        }
    }
    return ;
}

// bool    simulation_ended(t_table *table)
// {
//     return (check_bool(&table->meal_mutex, &table->is_finish));
// }

bool    simulation_end_bc_die(t_table *table)
{
    int i;

    i = 0;
    // pthread_mutex_lock(&table->meal_mutex);


    while (i < table->nb_philo)
    {
        long time = get_time() - table->starting_time; 
        long die = table->time_to_die;
        long last = check_data(&table->philo->philo_mutex, &table->philo->last_meal);
        last = last - table->starting_time;
        pthread_mutex_lock(&table->meal_mutex);
        if ((time + die) <= last)
        {
            table->someone_died = true;
            table->is_finish = true;
            return (true);
        }
        pthread_mutex_unlock(&table->meal_mutex);
        i++;        
    }
    return (false);
}

bool    philo_died(t_philo *philo)
{
    long    time;
    long    remain;
    long    check;

    time = philo->table->time_to_die;
    check = check_data(&philo->table->meal_mutex, &philo->last_meal);
    remain = get_time() - check;
    if (remain > time)
        return (true);
    else
        return (false);
}

bool     is_all_thread(pthread_mutex_t *mutex, long *thread, long nb_philo)
{
    bool ret;

    ret = false;
    pthread_mutex_lock(mutex);
    if (*thread == nb_philo)
        ret = true;
    pthread_mutex_unlock(mutex);
    return (ret);
}


bool     philo_full(t_philo *philo)
{
    if (philo->table->nb_meal != -1)
    {
        if(philo->count_meal >= philo->table->nb_meal)
            return (true);
    }
    return (false);
}


