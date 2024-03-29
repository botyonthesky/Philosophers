/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:17 by tmaillar          #+#    #+#             */
/*   Updated: 2024/03/29 08:21:56 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    clean_fork_mutex(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nb_philo)
    {
        pthread_mutex_destroy(&table->fork_mutex[i].fork);
        i++;
    }
    free(table->fork_mutex);
}

int init_mutex(t_table *table)
{
    if (init_fork(table) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    if (init_write(table) == EXIT_FAILURE)
    {
        clean_fork_mutex(table);
        return (EXIT_FAILURE);
    }
    if (init_meal(table) == EXIT_FAILURE)
    {
        clean_fork_mutex(table);;
        pthread_mutex_destroy(&table->write_mutex);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int    init_fork(t_table *table)
{
    int i;

    i = 0;
    // table->fork_mutex = ft_calloc(table->nb_philo, (sizeof(t_fork)));
    // if (table->fork_mutex == NULL)
    //     return (EXIT_FAILURE);
    while(i < table->nb_philo)
    {
        if (pthread_mutex_init(&table->fork_mutex[i].fork, NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&table->fork_mutex[i].fork);
            error_msg(INIT_ERR, NULL);
            return (EXIT_FAILURE);
        }
        table->fork_mutex[i].fork_id = i;
        i++;
    }
    return (EXIT_SUCCESS);
}

// int init_death(t_table *table)
// {        
//     if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
//     {
//         error_msg(INIT_ERR, NULL);
//         return (EXIT_FAILURE);
//     }
//     return (EXIT_SUCCESS);
// }
int init_write(t_table *table)
{    
    if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
    {
        // pthread_mutex_destroy(&table->death_mutex);
        error_msg(INIT_ERR, NULL);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int init_meal(t_table *table)
{    
    if (pthread_mutex_init(&table->meal_mutex, NULL) != 0)
    {
        error_msg(INIT_ERR, NULL);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}



