/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:57:05 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/01 14:18:36 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    sleep_routine(t_philo *philo)
{
    print_status(philo, SLEEP);
    wait_sleep(philo->table, philo->table->time_to_sleep);
}

void    think_routine(t_philo *philo)
{
    if (check_bool(&philo->table->table_mutex, &philo->table->someone_died) == true)
        return;
    if (check_bool(&philo->table->table_mutex, &philo->table->is_finish) == true)
        return;
    wait_think(philo->table);
    print_status(philo, THINK);
}

void    eat_routine(t_philo *philo)
{
    long time;

    pthread_mutex_lock(&philo->left_fork->fork);
    print_status(philo, FORK);
    pthread_mutex_lock(&philo->right_fork->fork);
    print_status(philo, FORK);
    print_status(philo, EAT);
    time = get_time();
    assign_data(&philo->philo_mutex, &philo->last_meal_time, time);
    wait_eat(philo->table, philo->table->time_to_eat);
    if (simulation_ended2(philo->table) == false)
    {
        increase_data(&philo->philo_mutex, &philo->count_meal);
    }
    print_status(philo, SLEEP);
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);
    wait_sleep(philo->table, philo->table->time_to_sleep);
}

// void    eat_routine(t_philo *philo)
// {
//     long time;

//     pthread_mutex_lock(&philo->table->fork_mutex[philo->philo_id].fork);
//     print_status(philo, FORK);
//     pthread_mutex_lock(&philo->table->fork_mutex[philo->philo_id].fork);
//     print_status(philo, FORK);
//     print_status(philo, EAT);
//     time = get_time();
//     assign_data(&philo->philo_mutex, &philo->last_meal_time, time);
//     wait_eat(philo->table, philo->table->time_to_eat);
//     if (simulation_ended2(philo->table) == false)
//     {
//         increase_data(&philo->philo_mutex, &philo->count_meal);
//     }
//     print_status(philo, SLEEP);
//     pthread_mutex_unlock(&philo->table->fork_mutex[philo->philo_id].fork);
//     pthread_mutex_unlock(&philo->table->fork_mutex[philo->philo_id].fork);

//     wait_sleep(philo->table, philo->table->time_to_sleep);
// }

void    solo_routine(t_table *table)
{
    long time;
    time = get_time() + (table->nb_philo * 2 * 10);
    assign_data(&table->table_mutex, &table->starting_time, time);
    synchro_philo2(table->starting_time);
    if (pthread_create(&table->philo[0].thread, NULL, thread_solo_routine, &table->philo[0]) != 0)
    {
        destroy_all(table);
        error_msg(CREATE_ERR, NULL);
        return ;
    }
    pthread_join(table->philo[0].thread, NULL);
    assign_bool(&table->table_mutex, &table->is_finish, true);
    return ;
}
