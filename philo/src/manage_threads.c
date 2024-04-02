/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:07:40 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/02 15:17:09 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Starts multithreaded environment
t_ErrorCode	init_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i <= table->number_of_philos)
	{
		if (pthread_create(&(table->philos[i].thread), NULL,
				&routine, &(table->philos[i])) != 0)
		{
			clean_data(table);
			return (THREAD_ERROR);
		}
		i++;
	}
	sync_threads(table);
	return (SUCCESS);
}

// Joins all threads upon conclusion
t_ErrorCode	end_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i <= table->number_of_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
		{
			clean_data(table);
			return (THREAD_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
