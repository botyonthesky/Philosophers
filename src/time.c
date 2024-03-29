/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:14:26 by tmaillar          #+#    #+#             */
/*   Updated: 2024/03/28 11:06:16 by tmaillar         ###   ########.fr       */
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