/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_conditions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:03:33 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/03 00:06:57 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Checks for any flag that should stop the simulation
/// Simulation_run allows for fewer checks after success_flag is up
bool	stop_simulation(t_table *table)
{
	bool	death_flag;
	bool	success_flag;
	bool	simulation_run;

	simulation_run
		= get_bool(&(table->simulation_mutex), &table->simulation_run);
	if (!simulation_run)
		return (true);
	death_flag
		= get_bool(&(table->death_mutex), &table->death_flag);
	if (death_flag)
	{
		set_bool(&(table->simulation_mutex), &table->simulation_run, false);
		return (true);
	}
	success_flag
		= get_bool(&(table->success_mutex), &table->success_flag);
	if (success_flag)
	{
		set_bool(&(table->simulation_mutex), &table->simulation_run, false);
		return (true);
	}
	return (false);
}

// Returns death_flag
bool	someone_died(t_table *table)
{
	bool	death_flag;

	death_flag = get_bool(&(table->death_mutex), &table->death_flag);
	return (death_flag);
}

// Sleeps for appropriate time, adds death message and sets death_flag to true
void	set_death(t_philos *philo, size_t wait_time)
{
	if (wait_time)
		ft_usleep(wait_time);
	add_message(philo, philo->table, get_current_time(philo), DIED);
	set_bool(&(philo->table->death_mutex),
		&(philo->table->death_flag), true);
}
