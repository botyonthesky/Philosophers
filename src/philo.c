/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:30 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 10:16:33 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo(char **av)
{
	t_table	table;

	if (ft_init(&table, av) == 1)
	{
		destroy_all(&table);
		return (EXIT_FAILURE);
	}
	if (start_simulation(&table) == 1)
	{
		destroy_all(&table);
		return (EXIT_FAILURE);
	}
	join_and_finish(&table);
	destroy_all(&table);
	return (EXIT_SUCCESS);
}
