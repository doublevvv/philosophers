/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:31:03 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/17 15:31:16 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(char **argv, char *str)
{
	int		i;
	long	res;
	int		sign;

	(void)argv;
	i = 0;
	res = 0;
	sign = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res * sign > INT_MAX || res * sign < INT_MIN)
			return ((long)(INT_MAX) + 1);
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (sign * res);
}

int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

int	free_simulation(t_main *table)
{
	int i;

	i = 0;
	while (i < table->nbr_philo)
    {
		free(table->philo[i].r_fork);
        i++;
    }
	free(table->philo);
	return (0);
}
