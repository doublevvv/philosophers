/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:41:43 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/09 14:45:44 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*NBR arg :
    - number_of_philosophers 
    - time_to_die 
    - time_to_eat
    - time_to_sleep
    - [optionnal] nb r of meals
*/

int main(int ac, char **av)
{
    t_main  table;
    
    if (ac != 5 && ac != 6)
        return (0);
    init_data(&table);
    if(is_args_correct(av, &table) != 0)
        return (1);
    free(table.philo);
    return (0);
}
