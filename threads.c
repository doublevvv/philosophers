/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:29:05 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/15 17:02:54 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    unlock_fork(t_characters *philo)
{
    if (philo->id_philo % 2 ==  0)
    {
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        // print_action("has taken a", philo);
    }
    else
    {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
    }
}

int    check_death(t_characters *philo)
{
    if (philo->dead == 1)
        return (1);
    return (0);
}
size_t    get_time(t_characters *philo)
{
   size_t start;
   size_t end;
   
   pthread_mutex_lock(&philo->table->mutex);
   gettimeofday(&philo->table->end, NULL);
   start = ((philo->table->start.tv_sec * 1000000) + philo->table->start.tv_usec) / 1000;
   end = ((philo->table->end.tv_sec * 1000000) + philo->table->end.tv_usec) / 1000;
   pthread_mutex_unlock(&philo->table->mutex);
   return(end - start);
}
void    print_action(char *c, t_characters *philo)
{
    long time;
    
    time = get_time(philo);
    pthread_mutex_lock(&philo->table->mutex);
    if(check_death(philo))
    {
        pthread_mutex_unlock(&philo->table->mutex);
        return ;
    }
    printf("[%ld] philo %d %s\n",time, philo->id_philo, c); //initialize time
    pthread_mutex_unlock(&philo->table->mutex);
}
void    lock_fork(t_characters *philo)
{
    //verifier mort a chaque prise de fourchette
    //❗ pb de lock lors de l'affichage
    if (philo->id_philo % 2 ==  0)
    {
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(philo->l_fork);
        // print_action("has taken a", philo);
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        pthread_mutex_lock(philo->r_fork);
    }
    // else
    // if (philo->id_philo % 2 ==  0)
}

int    philo_sleeping(t_characters *philo)
{
    if (check_death(philo) == 1)
    {
        unlock_fork(philo);
        return (1);
    }
    print_action("is sleeping", philo);
    usleep(philo->table->time_sleep * 1000);
    return (0);
}

int    philo_thinking(t_characters *philo)
{
     if (check_death(philo) == 1)
    {
        unlock_fork(philo);
        return (1);
    }
    print_action("is thinking", philo);
    return (0);
}

int   philo_eating(t_characters *philo)
{
    lock_fork(philo);
    if (check_death(philo) == 1)
    {
        unlock_fork(philo);
        return (1);
    }
    // pthread_mutex_lock(&philo->table->mutex);
    print_action("is eating", philo);
    philo->last_meal = get_time(philo);
    // pthread_mutex_unlock(&philo->table->mutex);
    usleep(philo->table->time_meal * 1000);
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
    // if(philo->table->max_nbr_meals > 0)
    //     ;//routine de nombre de loop
    // // else
    // //     {
            
    // //     }
    while (1)
    {
        //printf("MAX : %d\n", i);
        if(philo->id_philo % 2 != 0)
            usleep(50);
        if (philo_eating(philo) == 1)
            break;
        if (philo_sleeping(philo) == 1)
            break;
        if (philo_thinking(philo) == 1)
            break;
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
}


/*
- join (imaginer une fourchette en partant des dents)
	pour terminer le programmer qund un philo meurt ou nbr de meals manges
- initialize mutex and don't forget to destroy it after use
- verifier temps a chaque fois qu'ils mangent philo->end
❗ always lock and unlock to read or modify variables in main structure❗
*/

/*bloquer une sortie decriture avec mutex pour ne pas avoir de data race
utiliser printf*/
