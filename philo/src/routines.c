/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:12:40 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/09 12:41:12 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Starts routines for philos 1 to N (threads 1 to N)
// Routine 0 will be the monitor/printing thread
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

// Starts Eat-Sleep-Think routine
void	philo_thread(t_philos *philo)
{
	wait_for_threads(philo->table);
	//philo->start_time = get_abs_time();
	philo->time_last_meal = get_current_time(philo);
	while (!stop_simulation(philo->table))
	{
		take_first_fork_routine(philo);
		take_second_fork_routine(philo);
		eat_routine(philo, get_current_time(philo));
		sleep_routine(philo, get_current_time(philo));
		think_routine(philo, get_current_time(philo));
	}
	return ;
}

// Special routine in case there is only 1 philo
void	*one_philo_routine(void	*time_to_die)
{
	size_t	start_time;
	size_t	current_time;
	int		waiting_time;

	waiting_time = *(int *)time_to_die;
	start_time = get_abs_time();
	current_time = get_abs_time() - start_time;
	printf("%ld 0 has taken a fork\n", current_time);
	ft_usleep(waiting_time);
	current_time += waiting_time;
	printf("%ld 0 has died\n", current_time);
	return (NULL);
}
