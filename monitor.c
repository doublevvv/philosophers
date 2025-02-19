/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:51:47 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/20 16:24:53 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_death_true(t_characters *philo)
{
	size_t	time;
	size_t	l_meal;
	int		i;

	i = 0;
	while (i < philo->table->nbr_philo)
	{
		pthread_mutex_lock(&philo->table->mutex);
		l_meal = philo[i].last_meal;
		pthread_mutex_unlock(&philo->table->mutex);
		time = get_time(philo) - l_meal;
		pthread_mutex_lock(&philo->table->mutex);
		if (time >= philo->table->time_die)
		{
			philo[i].dead = 1;
			philo[i].table->finished = true;
			pthread_mutex_unlock(&philo->table->mutex);
			return (1);
		}
		i++;
		pthread_mutex_unlock(&philo->table->mutex);
	}
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
