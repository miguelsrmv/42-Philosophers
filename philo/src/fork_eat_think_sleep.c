/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_eat_think_sleep.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:13:06 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/01 14:59:26 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_first_fork_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time) || simulation_successful(philo, current_time))
		return ;
	(void)current_time;
	(void)philo;
	return ;
}

void	take_second_fork_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
	(void)current_time;
	(void)philo;
	return ;
}

void	eat_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
	(void)current_time;
	(void)philo;
	return ;
}

void	think_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
	(void)current_time;
	(void)philo;
	return ;
}

void	sleep_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
	(void)current_time;
	(void)philo;
	return ;
}
