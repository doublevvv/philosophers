/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:41:43 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/16 14:26:33 by vlaggoun         ###   ########.fr       */
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
    int i;
    t_main  table;
    (void)av;
    
    i = 0;
    if (ac != 5 && ac != 6)
        return (0);
    init_data(&table);
    gettimeofday(&table.start, NULL);
    is_args_correct(av, &table);
    monitoring(&table);
    thread_end(&table);
    free(table.philo);
    return (0);
}
