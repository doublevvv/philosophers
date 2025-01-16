/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:51:47 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/16 15:54:57 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int    is_death_true(t_characters *philo)
{
    size_t time;
    size_t l_meal;
    
    pthread_mutex_lock(&philo->table->mutex);
    l_meal = philo->last_meal;
    pthread_mutex_unlock(&philo->table->mutex);
    time = get_time(philo) - l_meal;
    pthread_mutex_lock(&philo->table->mutex);
    // printf("TIME : %ld | LASTMEAL : %ld | TIMEDIE : %ld\n", time, philo->last_meal, philo->table->time_die);
    if (time >= philo->table->time_die)
    {
        // printf("HERE\n");
        philo->dead = 1;
        philo->table->finished = true;
        printf("DEAD : %d\n", philo->dead);
        pthread_mutex_unlock(&philo->table->mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->table->mutex);
    return (0);
}

int nbr_meals_reached(t_characters *philo)
{
    pthread_mutex_lock(&philo->table->mutex);
    if (philo->nbr_meals >= philo->table->max_nbr_meals)
    {
        printf("NBR MEALS : %d\n", philo->nbr_meals);
        pthread_mutex_unlock(&philo->table->mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->table->mutex);
    return (0);
}

void    monitoring(t_main *table)
{
    while (1)
    {
        pthread_mutex_lock(&table->mutex);
        // printf("HELLO\n");
        pthread_mutex_unlock(&table->mutex);
        if (is_death_true(table->philo) == 1)
        {
            print_action("died\n", table->philo);
            break ;
        }
        if (table->loop_eat && nbr_meals_reached(table->philo) == 1)
        {   
            print_action("all philosophers ate", table->philo);
            break ;
        }
        //checker nbr meals
        usleep(400);
    }
}