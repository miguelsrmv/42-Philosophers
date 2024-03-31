/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:12:40 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 22:58:46 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	printing_thread(t_philos *philo)
{
	wait_for_threads(philo->table);
	return ;
}

void	philo_thread(t_philos *philo)
{
	wait_for_threads(philo->table);
	return ;
}
