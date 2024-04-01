/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_increase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:54:22 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/01 14:54:55 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    increase_data(pthread_mutex_t *mutex, long *data)
{
    pthread_mutex_lock(mutex);
    (*data) += 1;
    pthread_mutex_unlock(mutex);
}

void    assign_data(pthread_mutex_t *mutex, long *data, long value)
{
    pthread_mutex_lock(mutex);
    *data = value;
    pthread_mutex_unlock(mutex);   
}

void    assign_bool(pthread_mutex_t *mutex, bool *to_check, bool value)
{
    pthread_mutex_lock(mutex);
    *to_check = value;
    pthread_mutex_unlock(mutex);
}
