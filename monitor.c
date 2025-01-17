/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:51:47 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/17 15:45:11 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_death_true(t_characters *philo)
{
	size_t	time;
	size_t	l_meal;

	pthread_mutex_lock(&philo->table->mutex);
	l_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->table->mutex);
	time = get_time(philo) - l_meal;
	pthread_mutex_lock(&philo->table->mutex);
	if (time >= philo->table->time_die)
	{
		philo->dead = 1;
		philo->table->finished = true;
		pthread_mutex_unlock(&philo->table->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->mutex);
	return (0);
}

int	nbr_meals_reached(t_characters *philo)
{
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->nbr_meals >= philo->table->max_nbr_meals)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->mutex);
	return (0);
}

void	monitoring(t_main *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->mutex);
		pthread_mutex_unlock(&table->mutex);
		if (is_death_true(table->philo) == 1)
		{
			print_action("died", table->philo);
			break ;
		}
		if (table->loop_eat && nbr_meals_reached(table->philo) == 1)
		{
			print_action("all philosophers ate", table->philo);
			break ;
		}
		usleep(400);
	}
}
