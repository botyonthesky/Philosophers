/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:55:08 by tmaillar          #+#    #+#             */
/*   Updated: 2024/03/29 09:10:47 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void    *monitor(void *data)
{
    int i;
    t_table *table;

    table = (t_table *)data;
    while (is_all_thread(&table->meal_mutex, &table->nb_thread, table->nb_philo) == false)
        ;
    while (check_bool(&table->meal_mutex, &table->is_finish) == false)
    {
        i = 0;
        while (i < table->nb_philo)
        {
            if (philo_died(&table->philo[i]) == true)
            {
                assign_bool(&table->meal_mutex, &table->is_finish, true);
                print_status(table->philo, DIED, -1, 1);
            }
            i++;
        }
    }
    return (NULL);
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

bool    philo_died(t_philo *philo)
{
    long    time;
    long    remain;

    time = philo->table->time_to_die;
    remain = get_time() - (check_data(&philo->table->meal_mutex, &philo->last_meal));
    if (remain > time)
        return (true);
    else
        return (false);
}