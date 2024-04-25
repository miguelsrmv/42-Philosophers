/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:12:40 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/25 08:58:44 by mde-sa--         ###   ########.fr       */
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
	ft_usleep(((philo->philo_id) % 2) * BEGINNING_WAIT_BUFFER_ODD);
	philo->time_last_meal = get_current_time(philo);
	while (!stop_simulation(philo->table))
	{
		if (!take_first_fork_routine(philo))
			break ;
		if (!take_second_fork_routine(philo))
			break ;
		if (!eat_routine(philo, get_current_time(philo)))
			break ;
		if (!sleep_routine(philo, get_current_time(philo)))
			break ;
		if (!think_routine(philo, get_current_time(philo)))
			break ;
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
