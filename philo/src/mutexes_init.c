/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:49:47 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/02 11:27:30 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Initiates mutexes
t_ErrorCode	init_mutexes(t_table *table)
{
	int			i;
	t_forks		*fork;

	if (pthread_mutex_init(&(table->success_mutex), NULL)
		|| (pthread_mutex_init(&(table->success_count_mutex), NULL))
		|| (pthread_mutex_init(&(table->death_mutex), NULL))
		|| (pthread_mutex_init(&(table->message_mutex), NULL))
		|| (pthread_mutex_init(&(table->simulation_mutex), NULL))
		|| (pthread_mutex_init(&(table->number_mutex), NULL)))
	{
		clean_data(table);
		return (MUTEX_ERROR);
	}
	i = 0;
	while (i < table->number_of_philos)
	{
		fork = &(table->forks[i]);
		if (pthread_mutex_init(&(fork->fork_mutex), NULL))
		{
			clean_data(table);
			return (MUTEX_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
