/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:29:05 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/12 13:48:24 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
    creer threads et join them : a faire dans une boucle car nb de thread = nb de philo
	donc tant x < nb philo; x++;

    -EAT
    -SLEEP
    -THINK
    
    ❗must use mutex for printf
*/

void    get_time()
{
    struct timeval start;
    struct timeval end;
    unsigned long e_usec;

    gettimeofday(&start, 0);
    gettimeofday(&end, 0);

    e_usec = ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec);
    //printf("elapsed time: %lu microseconds\n", e_usec);
    
}

void    give_fork(t_main *table)
{
    int i;

    i = 0;
    while (i < table->nbr_philo)
    {
        if (i == table->nbr_philo - 1)
           table->philo[i].l_fork = &table->philo[0].r_fork;
        else
            table->philo[i].l_fork = &table->philo[i + 1].r_fork;
    }
}

void    print_action(char *c, t_characters *philo)
{
    //print temps avec get time 
    pthread_mutex_lock(&philo->table->mutex);
    printf("[%lu] %d", get_time, philo->id_philo); //initialize time
    pthread_mutex_unlock(&philo->table->mutex);
}
void    lock_fork(t_characters *philo)
{
    if (philo->id_philo % 2 ==  0) //donc pair
        pthread_mutex_lock(philo->r_fork);
    else
        pthread_mutex_lock(philo->l_fork);
    if (philo->id_philo % 2 ==  0)
        pthread_mutex_lock(philo->l_fork);
    else
        pthread_mutex_lock(philo->r_fork);
}

void    philo_sleeping(t_characters *philo)
{
    //must use uspleep function (with get_current_time(?))
    print_action("is sleeping", philo);
    usleep(philo->table->time_sleep * 1000);
}

void    philo_thinking(t_characters *philo)
{
    print_action("is thinking", philo);
}

void    philo_eating(t_characters *philo)
{
    lock_fork(philo);
    print_action("is eating\n", philo);
    usleep(philo->table->time_meal * 1000);
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}

void    *routine_table(void *data)
{
    //loop that runs until any of your philosophers die

    /*
        when they think, printf "philo[i] is thinking"
    */
    
    t_characters *philo;

    philo = (t_characters *)data;

    while (philo->dead != 0)
    {
        philo_eating;
        philo_sleeping;
        philo_thinking;
    }
    return (NULL);
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
    i = 0;
    while (i < table->nbr_philo)
        pthread_join(philo[i++].thread_id, NULL);
    pthread_mutex_destroy(&table->mutex);
}


/*
- join (imaginer une fourchette en partant des dents)
	pour terminer le programmer qund un philo meurt ou nbr de meals manges
- initialize mutex and don't forget to destroy it after use
*/

/*bloquer une sortie decriture avec mutex pour ne pas avoir de data race
utiliser printf*/
