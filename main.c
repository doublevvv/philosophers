/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:41:43 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/01/20 16:49:42 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	int		i;
	t_main	table;

	(void)av;
	i = 0;
	if (ac != 5 && ac != 6)
		return (0);
	init_data(&table);
	gettimeofday(&table.start, NULL);
	if (is_args_correct(av, &table) == 1)
		return (0);
	monitoring(&table);
	thread_end(&table);
	free_simulation(&table);
	return (0);
}
