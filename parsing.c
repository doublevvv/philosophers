/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:25:57 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/20 12:37:55 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fill_struct(char **arg, t_main *table)
{
	table->loop_eat = false;
	table->finished = false;
	table->nbr_philo = ft_atol(arg, arg[1]);
	table->time_die = ft_atol(arg, arg[2]);
	table->time_meal = ft_atol(arg, arg[3]);
	table->time_sleep = ft_atol(arg, arg[4]);
	if (arg[5])
	{
		table->loop_eat = true;
		table->max_nbr_meals = ft_atol(arg, arg[5]);
	}
}

int	give_fork(t_main *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		table->philo[i].r_fork = malloc(sizeof(pthread_mutex_t));
		if (!table->philo[i].r_fork)
		{
			free(&table->philo[i]);
			return (1);
		}
		pthread_mutex_init(table->philo[i].r_fork, NULL);
		i++;
	}
	i = 0;
	while (i < table->nbr_philo)
	{
		if (i == table->nbr_philo - 1)
			table->philo[i].l_fork = table->philo[0].r_fork;
		else
			table->philo[i].l_fork = table->philo[i + 1].r_fork;
		i++;
	}
	return (0);
}

int	initialize_data(t_main *table)
{
	int	i;

	i = 0;
	if (give_fork(table) == 1)
		return (1);
	if (pthread_mutex_init(&table->mutex, NULL) != 0)
		return (1);
	while (i < table->nbr_philo)
	{
		table->philo[i].id_philo = i + 1;
		table->philo[i].table = table;
		table->philo[i].dead = 0;
		table->philo[i].last_meal = 0;
		table->philo[i].nbr_meals = 0;
		i++;
	}
	return (0);
}

int	is_args_correct(char **arg, t_main *table)
{
	int		i;
	long	n;

	i = 1;
	while (arg[i])
	{
		if (arg[1] == 0)
			return (1);
		if (ft_is_numeric(arg[i]) == 1)
			return (1);
		n = ft_atol(arg, arg[i]);
		if (n < -2147483648 || n > 2147483647 || n < 1)
			return (1);
		i++;
	}
	fill_struct(arg, table);
	table->philo = malloc(sizeof(t_characters) * (table->nbr_philo));
	if (!table->philo)
		return (1);
	initialize_data(table);
	thread_creation(table, table->philo);
	return (0);
}
