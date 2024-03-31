/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:07:40 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 18:14:41 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_threads(t_table *table)
{
	int	i;

	table->epoch_time = get_current_time();
	i = 0;
	while (i <= table->number_of_philos)
	{
		if (pthread_create(&(table->philos[i++].thread), NULL, &routine, table) != 0)
		{
			clean_data(table);
			return (THREAD_ERROR);
		}
	}
	return (SUCCESS);
}
