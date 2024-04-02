/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_eat_think_sleep.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:13:06 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/02 15:29:20 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Takes first fork
/// If someone has died in the meantime, drop the fork
/// If too much time has passed before grabbing the fork, dies
void	take_first_fork_routine(t_philos *philo)
{
	pthread_mutex_lock(&(philo->first_fork->fork_mutex));
	if (someone_died(philo->table))
	{
		pthread_mutex_unlock(&(philo->first_fork->fork_mutex));
		return ;
	}
	if (waited_too_long(philo, get_current_time(philo)))
	{
		set_death(philo, get_current_time(philo));
		pthread_mutex_unlock(&(philo->first_fork->fork_mutex));
		return ;
	}
	add_message(philo, philo->table, get_current_time(philo), TOOK_A_FORK);
}

// Takes second fork
/// If someone has died in the meantime, drop the fork
/// If too much time has passed before grabbing the fork, dies
void	take_second_fork_routine(t_philos *philo)
{
	pthread_mutex_lock(&(philo->second_fork->fork_mutex));
	if (someone_died(philo->table))
	{
		pthread_mutex_unlock(&(philo->first_fork->fork_mutex));
		pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
		return ;
	}
	if (waited_too_long(philo, get_current_time(philo)))
	{
		set_death(philo, get_current_time(philo));
		pthread_mutex_unlock(&(philo->first_fork->fork_mutex));
		pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
		return ;
	}
	add_message(philo, philo->table, get_current_time(philo), TOOK_A_FORK);
}

// Eats
/// Eats for [time_to_eat], unless [time_to_die] < [time_to_eat]
//// "If a philosopher didn’t start eating [time_to_die] milliseconds 
//// since the beginning of their last meal or of the simulation, they die"
void	eat_routine(t_philos *philo, size_t current_time)
{
	philo->time_last_meal = current_time;
	add_message(philo, philo->table, current_time, IS_EATING);
	if (philo->time_to_eat < philo->time_to_die)
		ft_usleep(philo->time_to_eat);
	else
		set_death(philo, current_time);
	pthread_mutex_unlock(&(philo->first_fork->fork_mutex));
	pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
}

// Sleeps
/// Sleeps for [time_to_sleep],
/// unless [time_to_die] is lower than remaining time
void	sleep_routine(t_philos *philo, size_t current_time)
{
	add_message(philo, philo->table, current_time, IS_SLEEPING);
	if (current_time + philo->time_to_sleep
		< philo->time_last_meal + philo->time_to_die)
		ft_usleep(philo->time_to_sleep);
	else
		set_death(philo, current_time);
	return ;
}

// Thinks
/// Thinks for [time_to_think],
/// unless [time_to_die] is lower than remaining time
void	think_routine(t_philos *philo, size_t current_time)
{
	add_message(philo, philo->table, current_time, IS_THINKING);
	if (philo->time_to_think)
	{
		if (current_time + philo->time_to_think
			< philo->time_last_meal + philo->time_to_die)
			ft_usleep(philo->time_to_think);
		else
			set_death(philo, current_time);
	}
	return ;
}
