/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_print_threads.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:03:33 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/01 12:18:28 by mde-sa--         ###   ########.fr       */
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
