/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:24 by tmaillar          #+#    #+#             */
/*   Updated: 2024/03/29 11:02:03 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


int     main(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return (error_msg(USAGE, NULL));
    else
    {
        if (philo(argv) == 1)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

