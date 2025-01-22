/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:15:51 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/20 16:05:22 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lock_fork(t_characters *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		if (check_death(philo) == 1)
		{
			pthread_mutex_unlock(philo->r_fork);
			return (1);
		}
		print_action("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		if (check_death(philo) == 1)
		{
			unlock_fork(philo);
			return (1);
		}
		print_action("has taken a fork", philo);
	}
	else
	{
		if (lock_fork2(philo) == 1)
			return (1);
	}
	return (0);
}

int	lock_fork2(t_characters *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (check_death(philo) == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	print_action("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	if (check_death(philo) == 1)
	{
		unlock_fork(philo);
		return (1);
	}
	print_action("has taken a fork", philo);
	return (0);
}

int	philo_sleeping(t_characters *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table->mutex);
	time = philo->table->time_sleep * 1000;
	pthread_mutex_unlock(&philo->table->mutex);
	if (check_death(philo) == 1)
		return (1);
	if (check_nbr_meals(philo) == 1)
		return (1);
	print_action("is sleeping", philo);
	ft_usleep(philo, time);
	return (0);
}

int	philo_thinking(t_characters *philo)
{
	if (check_death(philo) == 1)
		return (1);
	if (check_nbr_meals(philo) == 1)
		return (1);
	print_action("is thinking", philo);
	ft_usleep(philo, time_to_think(philo));
	return (0);
}

int	time_to_think(t_characters *philo)
{
	if (philo->table->time_meal <= philo->table->time_sleep)
		return (500);
	else
		return ((((philo->table->time_meal - 1)
					- philo->table->time_sleep) + 2) * 1000);
}
