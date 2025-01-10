/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:19:51 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/10 15:08:05 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>

typedef struct s_characters
{
    int id_philo;
    int nbr_meals;
    int last_meal;
    int    dead;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    pthread_t   thread_id;
	struct s_main	*table;
}   t_characters;

typedef struct s_main
{
    int nbr_philo;
    int max_nbr_meals;
    size_t  time_meal;
    size_t  time_sleep;
    size_t  time_die;
    pthread_mutex_t   mutex;
    t_characters    *philo;

}   t_main; 


long	ft_atol(char **argv, char *str);
void	ft_free_double_array(char **array);
int     is_args_correct(char **arg, t_main *table);
int     ft_is_numeric(char *str);
void	thread_creation(t_main *table, t_characters *philo);
void	init_data(t_main *table);
void    *routine_table(void *data);
void    index_creation(t_main *table, t_characters *philo, int i);

# endif
