/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:41:43 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/08 16:46:06 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*NBR arg :
    - number_of_philosophers 
    - time_to_die 
    - time_to_eat
    - time_to_sleep
*/

int main(int ac, char **av)
{
    t_main  table;
    t_characters *philo;
    
    if (ac != 5 && ac != 6)
        return (0);
    init_data(&table, &philo);
    if(is_args_correct(av, &table, &philo) != 0)
        return (1);
    thread_creation(&table, &philo);
    return (0);
}