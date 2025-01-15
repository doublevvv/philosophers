/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:41:43 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/15 16:35:50 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*NBR arg :
    - number_of_philosophers 
    - time_to_die 
    - time_to_eat
    - time_to_sleep
    - [optionnal] nbr of meals
*/

int main(int ac, char **av)
{
    t_main  table;
    (void)av;
    
    if (ac != 5 && ac != 6)
        return (0);
    init_data(&table);
    gettimeofday(&table.start, NULL);
    is_args_correct(av, &table);
    monitoring(&table);
    free(table.philo);
     // while (i < table->nbr_philo)
    //     pthread_join(philo[i++].thread_id, NULL);
    // pthread_mutex_destroy(&table->mutex);
    return (0);
}
