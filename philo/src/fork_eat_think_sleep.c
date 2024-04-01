/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_eat_think_sleep.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:13:06 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/01 15:53:21 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Takes first fork
void	take_first_fork_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
	(void)current_time;
	(void)philo;
	return ;
}

// Takes second fork
void	take_second_fork_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
	(void)current_time;
	(void)philo;
	return ;
}

// Eats
void	eat_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
	(void)current_time;
	(void)philo;
	return ;
}

// Thinks
void	think_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
	(void)current_time;
	(void)philo;
	return ;
}

// Sleeps
void	sleep_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
	(void)current_time;
	(void)philo;
	return ;
}
