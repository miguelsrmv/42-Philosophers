/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_conditions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:03:33 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/01 14:53:26 by mde-sa--         ###   ########.fr       */
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
	size_t	time_to_die;

	time_to_die
		= (size_t)get_int(&(philo->table->time_mutex),
			&(philo->table->time_to_die));
	if ((current_time - philo->time_since_last_meal) > time_to_die)
	{
		set_bool(&(philo->table->death_mutex), &(philo->table->death_flag), true);
		return (true);
	}
	return (false);
	
}