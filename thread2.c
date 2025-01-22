/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:13:14 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/20 16:05:48 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlock_fork(t_characters *philo)
{
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

int	check_death(t_characters *philo)
{
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->finished || philo->dead == 1)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->mutex);
	return (0);
}

int	check_nbr_meals(t_characters *philo)
{
	if (philo->table->loop_eat
		&& philo->nbr_meals >= philo->table->max_nbr_meals)
		return (1);
	return (0);
}

size_t	get_time(t_characters *philo)
{
	struct timeval	end_struct;
	size_t			start;
	size_t			end;

	gettimeofday(&end_struct, NULL);
	start = ((philo->table->start.tv_sec * 1000000)
			+ philo->table->start.tv_usec) / 1000;
	end = ((end_struct.tv_sec * 1000000)
			+ end_struct.tv_usec) / 1000;
	return (end - start);
}

int	print_action(char *c, t_characters *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table->mutex);
	time = get_time(philo);
	printf("%ld %d %s\n", time, philo->id_philo, c);
	pthread_mutex_unlock(&philo->table->mutex);
	return (0);
}
