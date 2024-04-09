/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_eat_think_sleep.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:13:06 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/09 21:11:59 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Takes first fork
/// If someone has died in the meantime, returns
/// If too much time has passed before grabbing the fork, dies
bool	take_first_fork_routine(t_philos *philo)
{
	if (someone_died(philo->table))
		return (false);
	pthread_mutex_lock(&(philo->first_fork->fork_mutex));
	if (get_current_time(philo) > philo->time_last_meal + philo->time_to_die)
	{
		set_death(philo, 0);
		pthread_mutex_unlock(&(philo->first_fork->fork_mutex));
		return (false);
	}
	add_message(philo, philo->table, TOOK_A_FORK);
	return (true);
}

// Takes second fork
/// If someone has died in the meantime, drops the fork and returns
/// If too much time has passed before grabbing the fork, dies
bool	take_second_fork_routine(t_philos *philo)
{
	if (someone_died(philo->table))
	{
		pthread_mutex_unlock(&(philo->first_fork->fork_mutex));
		return (false);
	}
	pthread_mutex_lock(&(philo->second_fork->fork_mutex));
	if (get_current_time(philo) > philo->time_last_meal + philo->time_to_die)
	{
		set_death(philo, 0);
		pthread_mutex_unlock(&(philo->first_fork->fork_mutex));
		pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
		return (false);
	}
	add_message(philo, philo->table, TOOK_A_FORK);
	return (true);
}

// Eats
/// Eats for [time_to_eat], unless [time_to_die] < [time_to_eat]
//// "If a philosopher didn’t start eating [time_to_die] milliseconds 
//// since the beginning of their last meal or of the simulation, they die"
/// If someone died in the meantime, drops the forks and returns
bool	eat_routine(t_philos *philo, size_t current_time)
{
	if (someone_died(philo->table))
	{
		pthread_mutex_unlock(&(philo->first_fork->fork_mutex));
		pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
		return (false);
	}
	philo->time_last_meal = current_time;
	add_message(philo, philo->table, IS_EATING);
	if (philo->time_to_eat < philo->time_to_die)
		ft_usleep(philo->time_to_eat);
	else
	{
		set_death(philo,
			(philo->time_to_die) - (current_time - philo->time_last_meal));
		pthread_mutex_unlock(&(philo->first_fork->fork_mutex));
		pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
		return (false);
	}
	pthread_mutex_unlock(&(philo->first_fork->fork_mutex));
	pthread_mutex_unlock(&(philo->second_fork->fork_mutex));
	return (true);
}

// Sleeps
/// Sleeps for [time_to_sleep],
/// unless [time_to_die] is lower than remaining time
bool	sleep_routine(t_philos *philo, size_t current_time)
{
	if (someone_died(philo->table))
		return (false);
	add_message(philo, philo->table, IS_SLEEPING);
	if (current_time + philo->time_to_sleep
		< philo->time_last_meal + philo->time_to_die)
		ft_usleep(philo->time_to_sleep);
	else
	{
		set_death(philo,
			(philo->time_to_die) - (current_time - philo->time_last_meal));
		return (false);
	}
	return (true);
}

// Thinks
/// Thinks for [time_to_think],
/// unless [time_to_die] is lower than remaining time
bool	think_routine(t_philos *philo, size_t current_time)
{
	if (someone_died(philo->table))
		return (false);
	add_message(philo, philo->table, IS_THINKING);
	if (current_time + philo->time_to_think
		< philo->time_last_meal + philo->time_to_die)
	{
		ft_usleep(philo->time_to_think);
	}
	else
	{
		set_death(philo,
			(philo->time_to_die) - (current_time - philo->time_last_meal));
		return (false);
	}
	return (true);
}
