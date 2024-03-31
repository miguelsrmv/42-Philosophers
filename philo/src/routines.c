/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:12:40 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 23:09:39 by mde-sa--         ###   ########.fr       */
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
	ft_usleep(philo->philo_id * 50);
	printf("All threads done!\n");
	return ;
}

// Starts Eat-Think-Sleep routine
void	philo_thread(t_philos *philo)
{
	wait_for_threads(philo->table);
	ft_usleep(philo->philo_id * 50);
	printf("I'm thread number %i.\n", philo->philo_id);
	return ;
}
