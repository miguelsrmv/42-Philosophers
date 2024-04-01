/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:12:40 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/01 12:27:53 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Starts routines for philos 1 to N (threads 0 to N - 1)
// Routine #"number of philos" will be the printing thread
void	*routine(void *current_philo)
{
	t_philos	*philo;

	philo = (t_philos *)current_philo;
	if (philo->philo_id == philo->table->number_of_philos)
		printing_thread(philo);
	else
		philo_thread(philo);
	return (NULL);
}

// Waits for messages to be created, then prints them
void	printing_thread(t_philos *philo)
{
	wait_for_threads(philo->table);
	return ;
}

// Starts Eat-Think-Sleep routine
void	philo_thread(t_philos *philo)
{
	wait_for_threads(philo->table);
	philo->time_since_last_meal = get_current_time();
	while (!stop_simulation(philo->table))
	{
		if (!stop_simulation(philo->table))
			take_first_fork_routine(philo, get_current_time());
		if (!stop_simulation(philo->table))
			take_second_fork_routine(philo, get_current_time());
		if (!stop_simulation(philo->table))
			eat_routine(philo, get_current_time());
		if (!stop_simulation(philo->table))
			think_routine(philo, get_current_time());
		if (!stop_simulation(philo->table))
			sleep_routine(philo, get_current_time());
	}
	return ;
}
