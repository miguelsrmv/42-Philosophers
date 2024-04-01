/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_eat_think_sleep.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:13:06 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/01 16:16:51 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Takes first fork
void	take_first_fork_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
	pthread_mutex_lock(&(philo->first_fork->fork_mutex));
	add_message(philo, current_time, TOOK_A_FORK);
}

// Takes second fork
void	take_second_fork_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
	pthread_mutex_lock(&(philo->second_fork->fork_mutex));
	add_message(philo, current_time, TOOK_A_FORK);
}

// Eats
void	eat_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
	philo->time_last_meal = current_time;
	add_message(philo, current_time, IS_EATING);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
	pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
}

// Thinks
void	think_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
}

// Sleeps
void	sleep_routine(t_philos *philo, size_t current_time)
{
	if (is_dead(philo, current_time))
		return ;
}
