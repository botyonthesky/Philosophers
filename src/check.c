/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:54:45 by tmaillar          #+#    #+#             */
/*   Updated: 2024/03/29 14:53:58 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int check_argv(char **av)
{
    int i;
    long nb;

    i = 1;
    while (av[i])
    {
        nb = ft_atol(av[i]);
        if (is_valid_digit(nb) == 1)
            return (1);
        i++;
    }
    return (0);
}

int ft_check_int(char **argv)
{
    int i;
    i = 1;
    int nb;
    nb = 0;
    long    int_max;
    int_max = 2147483647;
    while (argv[i])
    {
        nb = ft_atol(argv[i]);
        if (nb > int_max || nb < 0)
            return (1);
        i++;
    }
    return (0);
}
void    increase_data(pthread_mutex_t *mutex, long *data)
{
    pthread_mutex_lock(mutex);
    (*data)++;
    pthread_mutex_unlock(mutex);
}
void    reassign_data(pthread_mutex_t *mutex, long *data, long *value)
{
    pthread_mutex_lock(mutex);
    *value = *data;
    pthread_mutex_unlock(mutex);
}

void    assign_data(pthread_mutex_t *mutex, long *data, long value)
{
    pthread_mutex_lock(mutex);
    *data = value;
    pthread_mutex_unlock(mutex);
    
}

long      check_data(pthread_mutex_t *mutex, long *value)
{
    long ret;
    
    pthread_mutex_lock(mutex);
    ret = *value;
    pthread_mutex_unlock(mutex);
    return (ret);
    
}
void    assign_bool(pthread_mutex_t *mutex, bool *to_check, bool value)
{
    pthread_mutex_lock(mutex);
    *to_check = value;
    pthread_mutex_unlock(mutex);
}

bool    check_bool(pthread_mutex_t *mutex, bool *value)
{
    bool ret;
    
    pthread_mutex_lock(mutex);
    ret = *value;
    pthread_mutex_unlock(mutex);
    return (ret);

}