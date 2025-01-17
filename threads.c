/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:29:05 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/17 15:19:13 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    unlock_fork(t_characters *philo)
{
    if (philo->id_philo % 2 ==  0)
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

int    check_death(t_characters *philo)
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

int    check_nbr_meals(t_characters *philo)
{
    if (philo->table->loop_eat && philo->nbr_meals >= philo->table->max_nbr_meals)
        return (1);
    return (0);
    
}

size_t    get_time(t_characters *philo)
{
   size_t start;
   size_t end;
   
   gettimeofday(&philo->table->end, NULL);
   start = ((philo->table->start.tv_sec * 1000000) + philo->table->start.tv_usec) / 1000;
   end = ((philo->table->end.tv_sec * 1000000) + philo->table->end.tv_usec) / 1000;
   return(end - start);
}

int   print_action(char *c, t_characters *philo)
{
    long time;
    
    pthread_mutex_lock(&philo->table->mutex);
    time = get_time(philo);
    printf("[%ld] philo %d %s\n",time, philo->id_philo, c);
    pthread_mutex_unlock(&philo->table->mutex);
    return (0);
}
void    lock_fork(t_characters *philo)
{
    if (philo->id_philo % 2 ==  0)
    {
        pthread_mutex_lock(philo->r_fork);
        print_action("has taken a fork", philo);
        pthread_mutex_lock(philo->l_fork);
        print_action("has taken a fork", philo);
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        print_action("has taken a fork", philo);
        pthread_mutex_lock(philo->r_fork);
        print_action("has taken a fork", philo);
    }
}


int    philo_sleeping(t_characters *philo)
{
    long time;

    pthread_mutex_lock(&philo->table->mutex);
    time = philo->table->time_meal * 1000;
    pthread_mutex_unlock(&philo->table->mutex);
    if (check_death(philo) == 1)
        return (1);
    if (check_nbr_meals(philo) == 1)
        return (1);
    print_action("is sleeping", philo);
    usleep(time);
    return (0);
}

int    philo_thinking(t_characters *philo)
{
    if (check_death(philo) == 1)
        return (1);
    if (check_nbr_meals(philo) == 1)
        return (1);
    print_action("is thinking", philo);
    return (0);
}

int   philo_eating(t_characters *philo)
{
    long time;

    lock_fork(philo);
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
    usleep(time);
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
    return (0);
}

void    *routine_table(void *data)
{   
    t_characters *philo;
    int i;

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
            break;
        }
        if(philo->id_philo % 2 != 0)
            usleep(500);
        if (philo_eating(philo) == 1)
            break;
        if (philo_sleeping(philo) == 1)
            break;
        if (philo_thinking(philo) == 1)
            break;
    }
    return (NULL);
}


void    thread_end(t_main *table)
{
    int i;

    i = 0;
    while (i < table->nbr_philo)
    {
        pthread_join(table->philo[i++].thread_id, NULL);
    }
    pthread_mutex_destroy(&table->mutex);
}

void	thread_creation(t_main *table, t_characters *philo)
{
    int i;

    i = 0;
    while (i < table->nbr_philo) 
    {
        pthread_create(&philo[i].thread_id, NULL, &routine_table, (void *)&philo[i]);
        i++;
    }
}

