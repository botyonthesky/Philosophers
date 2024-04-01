/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:33:53 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/01 14:46:20 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;
	size_t	i;
	size_t	l;

	i = 0;
	l = nmemb * size;
	if (nmemb != 0 && l / nmemb != size)
		return (NULL);
	new = malloc(l);
	if (!new)
		return (NULL);
	if (size == 0)
		return (new);
	while (i < l)
	{
		((unsigned char *)new)[i] = 0;
		i++;
	}
	return (new);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

long	ft_atol(char *str)
{
	long		result;
	int			sign;
	size_t		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	is_valid_digit(long nb)
{
	if (nb < 1 || nb > INT_MAX)
		return (1);
	return (0);
}
