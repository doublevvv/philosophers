/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:25:57 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/09 14:48:49 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void fill_struct(char **arg, t_main *table) //retirer philoo
{
    
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

int is_args_correct(char **arg, t_main *table)
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
    fill_struct(arg, table);
    table->philo = malloc(sizeof(t_characters) * (table->nbr_philo));
    pthread_mutex_init(&table->mutex, NULL);
    i = 0;
    while (i < table->nbr_philo)
    {   
        table->philo[i].id_philo = i + 1;
		table->philo[i].table = table;
        i++;
    }
    thread_creation(table, table->philo);
    return (0);
}
