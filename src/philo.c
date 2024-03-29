/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:30 by tmaillar          #+#    #+#             */
/*   Updated: 2024/03/29 16:54:34 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int    philo(char **av)
{
    t_table table;

    if (ft_init(&table, av) == 1)
        return (EXIT_FAILURE);
    if (start_simulation(&table) == 1)
        return (EXIT_FAILURE);
    monitor(&table);
    destroy_all(&table);
    return (EXIT_SUCCESS);
}

int    start_simulation(t_table *table)
{
    int i;
    
    i = 0;
    if (table->nb_meal == 0)
            return (EXIT_FAILURE);
    assign_data(&table->meal_mutex, &table->starting_time, get_time());
    assign_data(&table->philo->philo_mutex, &table->philo->last_meal, get_time());
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
    // pthread_create(&table->monitor, NULL, monitor, &table);
    assign_bool(&table->meal_mutex, &table->thread_ready, true);
    i = 0;
    while (i < table->nb_philo)
    {
        pthread_join(table->philo[i].thread, NULL);
        i++;
    }
    assign_bool(&table->meal_mutex, &table->is_finish, true);
    // pthread_join(table->monitor, NULL);
    return (EXIT_SUCCESS);
}


void    synchronize_thread(t_table *table)
{
    while(check_bool(&table->meal_mutex, &table->thread_ready) == false)
        ;
}

void    solo_routine(t_table *table)
{
    // assign_data(&table->meal_mutex, &table->starting_time, get_time());
    if (pthread_create(&table->philo[0].thread, NULL, thread_solo_routine, &table->philo[0]) != 0)
    {
        destroy_all(table);
        error_msg(CREATE_ERR, NULL);
        return ;
    }
    pthread_join(table->philo[0].thread, NULL);
    assign_bool(&table->meal_mutex, &table->is_finish, true);
    return ;
}
void    *thread_solo_routine(void *data)
{
    t_philo *philo;
    
    philo = (t_philo *)data;
    // synchronize_thread(philo->table);
    // if (check_bool(&philo->philo_mutex, &philo->is_full) == true)
    //     return (NULL);
    // pthread_mutex_lock(&philo->left_fork->fork);
    print_status(philo, FORK, LEFT, 1);
    wait_die(philo->table);
    // print_status(philo, DIED, -1, 1);
// e    pthread_mutex_unlock(&philo->left_fork->fork);
    return (NULL);
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
