/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:29:05 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/08 16:46:43 by vlaggoun         ###   ########.fr       */
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
    
    t_main *table;

    table = (t_main *)data;
    // pthread_mutex_lock(&table->mutex);
    printf("HELLO\n");
    // pthread_mutex_unlock(&table->mutex);
    return (NULL);
}

void	thread_creation(t_main *table, t_characters *philo)
{
    int i;

    i = 0;
    pthread_mutex_init(&table->mutex, NULL);
	philo->thread_id = pthread_self();
    while (i < table->nbr_philo)
    {
        pthread_mutex_lock(&table->mutex);
        pthread_create(&philo->thread_id, NULL, &routine_table, (void *)&philo[i]);
        // pthread_join(philo->id_philo, NULL);
        printf("ID = %ld\n", philo->thread_id);
        pthread_mutex_unlock(&table->mutex);
        // pthread_join(philo->id_philo, NULL);
        i++;

    }
}


/*
- join (imaginer une fourchette en partant des dents)
	pour terminer le programmer qund un philo meurt ou nbr de meals manges
- initialize mutex and don't forget to destroy it after use
*/

/*bloquer une sortie decriture avec mutex pour ne pas avoir de data race
utiliser printf*/