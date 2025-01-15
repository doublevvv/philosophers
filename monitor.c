/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:51:47 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/15 16:41:03 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int    is_death_true(t_characters *philo)
{
    size_t time;
    
    time = get_time(philo) - philo->last_meal;
    pthread_mutex_lock(&philo->table->mutex);
    if (time >= philo->table->time_die)
    {
        philo->dead = 1;
        pthread_mutex_unlock(&philo->table->mutex);
        return (1);
    }
    pthread_mutex_unlock(&philo->table->mutex);
    return (0);
    // printf("DEAD : %d\n", philo->dead);
    // printf("TIME : %ld | LASTMEAL : %ld | TIMEDIE : %ld\n", time, philo->last_meal, philo->table->time_die);
}

void    monitoring(t_main *table)
{
    while (1)
    {
        if (is_death_true(table->philo) == 1)
        {   
            print_action("hello\n", table->philo);
            // pthread_mutex_unlock(&table->mutex);  
            return ;
        }
        // pthread_mutex_unlock(&table->mutex);  
        //checker nbr meals
        usleep(400);
    }
}