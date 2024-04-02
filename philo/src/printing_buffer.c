/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:05:19 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/02 14:24:43 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	add_message(t_philos *philo, t_table *table,
			size_t current_time, t_PhiloAction action)
{
	t_message	*message;

	if (stop_simulation(table))
		return ;
	message = (t_message *)malloc(sizeof(t_message));
	if (!message)
		return ;
	pthread_mutex_lock(&(table->message_mutex));
	message->time_stamp = current_time;
	message->philo_id = philo->philo_id;
	message->action = action;
	message->next = NULL;
	if (!table->message_head)
	{
		table->message_head = message;
		table->message_end = message;
	}
	else
	{
		table->message_end->next = message;
		table->message_end = message;
	}
	pthread_mutex_unlock(&(table->message_mutex));
}
