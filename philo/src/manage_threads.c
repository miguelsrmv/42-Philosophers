/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:07:40 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/02 20:13:40 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Starts multithreaded environment
t_ErrorCode	init_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i <= table->number_of_philos)
	{
		if (pthread_create(&(table->philos[i].thread), NULL,
				&routine, &(table->philos[i])) != 0)
		{
			clean_data(table);
			return (THREAD_ERROR);
		}
		i++;
	}
	sync_threads(table);
	return (SUCCESS);
}

// Joins all threads upon conclusion
t_ErrorCode	end_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i <= table->number_of_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
		{
			clean_data(table);
			return (THREAD_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

// Waits for simulation_run to be true (spinlock @ thread start)
void	wait_for_threads(t_table *table)
{
	while (!get_bool(&table->simulation_mutex, &table->simulation_run))
		;
}

// Waits for all threads to be created, then sets simulation_run to TRUE
void	sync_threads(t_table *table)
{
	ft_usleep(table->number_of_philos * 5);
	set_bool(&(table->simulation_mutex), &(table->simulation_run), true);
}

// Starts special case with just 1 thread
t_ErrorCode	one_philo_simulation(int time_to_die)
{
	pthread_t	lone_philo;

	if (pthread_create(&lone_philo, NULL,
			&one_philo_routine, &time_to_die) != 0)
		return (THREAD_ERROR);
	if (pthread_join(lone_philo, NULL) != 0)
		return (THREAD_ERROR);
	return (SUCCESS);
}
