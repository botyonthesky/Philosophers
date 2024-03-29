/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:30 by tmaillar          #+#    #+#             */
/*   Updated: 2024/03/29 09:40:57 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int    philo(char **av)
{
    t_table table;

    if (ft_init(&table, av) == 1)
        return (EXIT_FAILURE);
    start_simulation(&table);
    destroy_all(&table);
    return (EXIT_SUCCESS);
}




void    start_simulation(t_table *table)
{
    int i;
    
    i = 0;
    if (table->nb_meal == 0)
            return ;
    if (table->nb_philo == 1)
    {
        solo_routine(table);
        return ;
    }
    table->starting_time = get_time();
    while (i < table->nb_philo)
    {
        if (pthread_create(&table->philo[i].thread, NULL, thread_routine, &table->philo[i]) != 0)
        {
            destroy_all(table);
            error_msg(CREATE_ERR, NULL);
            return ;
        }
        i++;
    }
    pthread_create(&table->monitor, NULL, monitor, &table);
    assign_bool(&table->meal_mutex, &table->thread_ready, true);
    i = 0;
    while (i < table->nb_philo)
    {
        pthread_join(table->philo[i].thread, NULL);
        i++;
    }
    assign_bool(&table->meal_mutex, &table->is_finish, true);
    pthread_join(table->monitor, NULL);
    return ;
}


void    synchronize_thread(t_table *table)
{
    while(check_bool(&table->meal_mutex, &table->thread_ready) == false)
        ;
}

void    solo_routine(t_table *table)
{
    int i;
    pthread_t   *thread_id;

    i = 0;
    thread_id = ft_calloc(table->nb_philo, (sizeof(pthread_t)));
    if (pthread_create(&thread_id[i], NULL, thread_solo_routine, &table->philo[i]) != 0)
    {
        destroy_all(table);
        error_msg(CREATE_ERR, NULL);
        return ;
    }
    return ;
}


// void    start_simulation(t_table *table)
// {
//     int i;
    
//     i = 0;
//     if (table->nb_meal == 0)
//             return ;
//     if (table->nb_philo == 1)
//     {
//         solo_routine(table);
//         return ;
//     }
//     while (i < table->nb_philo)
//     {
//         if (pthread_create(&table->philo[i].thread_id, NULL, thread_routine, &table->philo[i]) != 0)
//         {
//             destroy_all(table);
//             error_msg(CREATE_ERR, NULL);
//             return ;
//         }
//         i++;
//     }
//     pthread_create(&table->monitor_mutex, NULL, monitor, &table);
//     table->starting_time = get_time();
//     assign_bool(&table->meal_mutex, &table->thread_ready, true);
//     i = 0;
//     while (i < table->nb_philo)
//     {
//         pthread_join(table->philo[i].thread_id, NULL);
//         i++;
//     }
//     assign_bool(&table->meal_mutex, &table->is_finish, true);
//     pthread_join(table->monitor_mutex, NULL);
//     return ;
// }
