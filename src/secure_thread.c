/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 08:38:54 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 09:20:24 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int     secure_create(pthread_t *thread, void *data, void *arg)
{
    if (pthread_create(thread, NULL, data, arg) != 0)
    {
        error_msg(CREATE_ERR, NULL);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int     secure_init(pthread_mutex_t *mutex)
{
    if (pthread_mutex_init(mutex, NULL) != 0)
    {
        error_msg(INIT_ERR, NULL);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}