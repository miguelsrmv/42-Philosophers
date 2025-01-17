/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:05:19 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/10 08:49:09 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Turns on mutex before creating/appending node to list
void	add_message(t_philos *philo, t_table *table, t_PhiloAction action)
{
	ssize_t	time;

	pthread_mutex_lock(&(table->message_mutex));
	time = get_current_time(philo);
	add_node_to_list(philo, table, time, action);
	pthread_mutex_unlock(&(table->message_mutex));
}

// Creates node and appends it to list
/// Returns if malloc error
void	add_node_to_list(t_philos *philo, t_table *table, ssize_t time,
	t_PhiloAction action)
{
	t_message	*message;

	message = (t_message *)malloc(sizeof(t_message));
	if (!message)
	{
		printf(MALLOC_MESSAGE);
		return ;
	}
	message->time_stamp = time;
	message->philo_id = philo->philo_id;
	message->action = action;
	message->next = NULL;
	if (!(table->message_head))
	{
		(table->message_head) = message;
		(table->message_end) = message;
	}
	else
	{
		(table->message_end)->next = message;
		(table->message_end) = message;
	}
}
