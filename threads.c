/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:29:05 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/13 18:04:41 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long    get_time(t_characters *philo)
{
   long start;
   long end;

   gettimeofday(&philo->table->end, NULL);
   start = ((philo->table->start.tv_sec * 1000000) + philo->table->start.tv_usec) / 1000;
   end = ((philo->table->end.tv_sec * 1000000) + philo->table->end.tv_usec) / 1000;
   return(end - start);
    
    
}
void    print_action(char *c, t_characters *philo)
{
    long time;
    
    time = get_time(philo);
    pthread_mutex_lock(&philo->table->mutex);
    printf("[%ld] philo %d %s\n",time, philo->id_philo, c); //initialize time
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
    print_action("is eating", philo);
    philo->last_meal = get_time(philo);
    philo->table->time_die = philo->last_meal + philo->table->time_die;
    printf("DEAD : [%ld]\n",philo->table->time_die); //initialize time 
    printf("TMP : [%ld]\n", get_time(philo)); //initialize time
    usleep(philo->table->time_meal * 1000);
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
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
        printf("MAX : %d\n", i);
        if(philo->id_philo % 2 != 0)
            usleep(50);
        philo_eating(philo);
        philo_sleeping(philo);
        philo_thinking(philo);
        i++;
        if (i > philo->table->max_nbr_meals)
            exit (0);//ne pas oublier de free
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
- verifier temps a chaque fois qu'ils mangent philo->end
*/

/*bloquer une sortie decriture avec mutex pour ne pas avoir de data race
utiliser printf*/
