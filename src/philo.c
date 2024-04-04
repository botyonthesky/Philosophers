/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:30 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 13:44:11 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo(char **av)
{
	t_table	table;

	if (init_argv(&table, av) == 1)
		return (EXIT_FAILURE);
	if (ft_init(&table) == 1)
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
