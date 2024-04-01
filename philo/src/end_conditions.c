/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_conditions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:03:33 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/01 15:56:21 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	stop_simulation(t_table *table)
{
	bool	simulation_run_flag;
	bool	death_flag;
	bool	success_flag;

	simulation_run_flag
		= get_bool(&(table->simulation_mutex), &table->simulation_run);
	if (!simulation_run_flag)
		return (true);
	death_flag
		= get_bool(&(table->death_mutex), &table->death_flag);
	if (death_flag)
		return (true);
	success_flag
		= get_bool(&(table->success_mutex), &table->success_flag);
	if (success_flag)
		return (true);
	return (false);
}

bool	is_dead(t_philos *philo, size_t current_time)
{
	if ((current_time - philo->time_since_last_meal)
		> philo->time_to_die)
	{
		set_bool(&(philo->table->death_mutex),
			&(philo->table->death_flag), true);
		//add_death_message(philo, current_time, time_to_die);
		return (true);
	}
	return (false);
}
