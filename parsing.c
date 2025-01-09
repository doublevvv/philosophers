/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:25:57 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/09 09:06:42 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void fill_struct(char **arg, t_main *table, t_characters *philoo) //retirer philoo
{
	(void)philoo;
    
    table->nbr_philo = ft_atol(arg, arg[1]);
    table->time_die = ft_atol(arg, arg[2]);
    table->time_meal = ft_atol(arg, arg[3]);
    table->time_sleep = ft_atol(arg, arg[4]);
    // printf("NB = %d\n", table->nbr_philo);
    // printf("die = %zu\n", table->time_die);
    // printf("eat = %zu\n", table->time_meal);
    // printf("sleep = %zu\n", table->time_sleep);
    // printf("id = %d\nnbrmeals = %d\nlastmeal = %d\n", philoo->id_philo, philoo->nbr_meals, philoo->last_meal);
}

int is_args_correct(char **arg, t_main *table, t_characters **philo)
{
    int i;
    long n;

    i = 1;
    while (arg[i])
    {
        if (ft_is_numeric(arg[i]) != 1){
            printf("FALSE\n");
           return (1);
        }
        n = ft_atol(arg, arg[i]);
        if (n < -2147483648 || n > 2147483647 || n < 1)
        {
            printf("HRE\n");
            return (1);
        }
        i++;
    }
    fill_struct(arg, table, *philo);
    *philo = malloc(sizeof(t_characters) * (table->nbr_philo));
    thread_creation(table, *philo);
    return (0);
}
