/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:14:26 by tmaillar          #+#    #+#             */
/*   Updated: 2024/03/29 14:55:20 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long get_time(void)
{
    struct timeval start;

    if (gettimeofday(&start, NULL) == 0)
            return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
    else
    {
        printf(TIME);
        return (EXIT_FAILURE);
    }
}


void    wait_eat(t_table *table)
{
    long    time;
    long    eating_time;
    
    reassign_data(&table->meal_mutex, &table->time_to_eat, &eating_time);
    time = get_time() + eating_time;

    while (get_time() < time)
        usleep(100);
}

void    wait_sleep(t_table *table)
{
    long    time;
    long    sleeping_time;

    time = get_time();    
    reassign_data(&table->meal_mutex, &table->time_to_sleep, &sleeping_time);
    while (get_time() - time < sleeping_time)
        usleep(100);   
}

void    wait_think(t_table *table)
{
    long time;
    long thinking_time;

    time = get_time();
    reassign_data(&table->meal_mutex, &table->time_to_think, &thinking_time);
    if (thinking_time < 0)
        thinking_time = 0;
    while (get_time() - time < thinking_time)
        usleep(100);
}


void    wait_die(t_table *table)
{
    long    time;
    long    dying_time;
    
    reassign_data(&table->meal_mutex, &table->time_to_die, &dying_time);
    time = get_time() + dying_time;
    while(get_time() < time)
        usleep(100);
}

void    synchro_philo(t_philo *philo)
{
    if (philo->table->nb_philo % 2 == 0)
    {
        if (philo->philo_id % 2 == 0)
            usleep(3000);
    }
    else
    {
        if (philo->philo_id)
            think_routine(philo);
    }
}