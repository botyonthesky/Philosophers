/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:56:37 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/01 13:45:32 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


int    start_simulation(t_table *table)
{
    int i;
    long time;

    i = 0;
    time = (get_time() + (table->nb_philo * 2 * 10));
    table->starting_time = time;
    if (table->nb_philo == 1)
    {
        solo_routine(table);
        return (EXIT_SUCCESS);
    }
    while (i < table->nb_philo)
    {
        if (pthread_create(&table->philo[i].thread, NULL, thread_routine, &table->philo[i]) != 0)
        {
            destroy_all(table);
            error_msg(CREATE_ERR, NULL);
            return (EXIT_FAILURE);
        }
        i++;
    }
    if (pthread_create(&table->monitor, NULL, monitor, table) != 0)
    {
        destroy_all(table);
        error_msg(CREATE_ERR, NULL);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

void    join_and_finish(t_table *table)
{
    int i;
    
    i = 0;
    if (table->nb_fork > 1)
    {
        while (i < table->nb_philo)
        {
            pthread_join(table->philo[i].thread, NULL);
            i++;
        }
        pthread_join(table->monitor, NULL);
        assign_bool(&table->table_mutex, &table->is_finish, true);
    }
}

void    stop_simulation(t_table *table)
{
    destroy_all(table);
    return ;
}