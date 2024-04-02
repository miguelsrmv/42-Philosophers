/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:12:40 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/02 15:53:29 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Starts routines for philos 1 to N (threads 1 to N)
// Routine 0 will be the printing thread
void	*routine(void *current_philo)
{
	t_philos	*philo;

	philo = (t_philos *)current_philo;
	if (philo->philo_id == 0)
		monitoring_and_printing_thread(philo->table);
	else
		philo_thread(philo);
	return (NULL);
}

// Starts Eat-Think-Sleep routine
void	philo_thread(t_philos *philo)
{
	philo->start_time = get_abs_time();
	wait_for_threads(philo->table);
	philo->time_last_meal = get_current_time(philo);
	while (!stop_simulation(philo->table))
	{
		take_first_fork_routine(philo);
		take_second_fork_routine(philo);
		eat_routine(philo, get_current_time(philo));
		think_routine(philo, get_current_time(philo));
		sleep_routine(philo, get_current_time(philo));
	}
	return ;
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
