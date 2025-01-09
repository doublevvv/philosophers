/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:29:05 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/09 14:44:42 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
creer threads et join them : a faire dans une boucle car nb de thread = nb de philo
	donc tant x < nb philo; x++;
*/

void    *routine_table(void *data)
{
    //loop that runs until any of your philosophers die
    
    t_characters *philo;

    philo = (t_characters *)data;
    pthread_mutex_lock(&philo->table->mutex);
    printf("HELLO\n");
    pthread_mutex_unlock(&philo->table->mutex);
    return (NULL);
}

// void    index_creation(t_main *table, t_characters *philo, int i)
// {
//     int index;

//     index = 1;
//     while (index < table->nbr_philo)
//     {
//         philo[i].thread_id = index;
//         printf("INDEX : %lu\n", philo[i].thread_id);
//         index++;
//         i++;
//     }
// }

void	thread_creation(t_main *table, t_characters *philo)
{
    int i;

    i = 0;
	// philo[i].thread_id = pthread_self(); //❗FUNCTION UNAUTHORIZED; id must be a index starting from 1
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
