/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:29:05 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/20 16:25:36 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_eating(t_characters *philo)
{
	long	time;

	if (lock_fork(philo) == 1)
		return (1);
	print_action("is eating", philo);
	if (check_death(philo) == 1)
	{
		unlock_fork(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->table->mutex);
	time = philo->table->time_meal * 1000;
	if (check_nbr_meals(philo) == 1)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return (1);
	}
	philo->nbr_meals++;
	philo->last_meal = get_time(philo);
	pthread_mutex_unlock(&philo->table->mutex);
	ft_usleep(philo, time);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}

void	*routine_table(void *data)
{
	t_characters	*philo;
	int				i;

	i = 0;
	philo = (t_characters *)data;
	while (1)
	{
		if (philo->table->nbr_philo == 1)
		{
			pthread_mutex_lock(philo->l_fork);
			print_action("has taken a fork", philo);
			pthread_mutex_unlock(philo->l_fork);
			check_death(philo);
			break ;
		}
		if (philo->id_philo % 2 != 0)
			usleep(500);
		if (philo_eating(philo) == 1)
			break ;
		if (philo_sleeping(philo) == 1)
			break ;
		if (philo_thinking(philo) == 1)
			break ;
	}
	return (NULL);
}

void	thread_end(t_main *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->philo[i++].thread_id, NULL);
	}
	pthread_mutex_destroy(&table->mutex);
}

void	thread_creation(t_main *table, t_characters *philo)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_create(&philo[i].thread_id, NULL,
			&routine_table, (void *)&philo[i]);
		i++;
	}
}

void	ft_usleep(t_characters *philo, int time)
{
	const size_t	time_start = get_time(philo);

	while (1)
	{
		usleep(500);
		pthread_mutex_lock(&philo->table->mutex);
		if (philo->table->finished == true)
		{
			pthread_mutex_unlock(&philo->table->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->table->mutex);
		if (time_start + time / 1000 <= get_time(philo))
			return ;
	}
}
