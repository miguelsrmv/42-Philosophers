/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:05:19 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/02 16:59:56 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Adds message to Linked List buffer
/// Stops simulation in case other threads have given such a sign
/// Also stops simulation (and signs other threads) if MALLOC_ERROR
void	add_message(t_philos *philo, t_table *table,
			size_t current_time, t_PhiloAction action)
{
	t_message	*message;

	message = NULL;
	pthread_mutex_lock(&(table->message_mutex));
	if (stop_simulation(table))
	{
		pthread_mutex_unlock(&(table->message_mutex));
		return ;
	}
	if (!create_next_node(&message, current_time, philo->philo_id, action))
	{
		set_bool(&(table->simulation_mutex), &(table->simulation_run), false);
		pthread_mutex_unlock(&(table->message_mutex));
		return ;
	}
	add_to_list(message, &(table->message_head), &(table->message_end));
	pthread_mutex_unlock(&(table->message_mutex));
}

// Creates new node for linked list
bool	create_next_node(t_message **message, size_t current_time,
	int philo_id, t_PhiloAction action)
{
	(*message) = (t_message *)malloc(sizeof(t_message));
	if (!(*message))
	{
		printf(MALLOC_MESSAGE);
		return (false);
	}
	(*message)->time_stamp = current_time;
	(*message)->philo_id = philo_id;
	(*message)->action = action;
	(*message)->next = NULL;
	return (true);
}

// Adds node to linked list
void	add_to_list(t_message *node,
			t_message **list_head, t_message **list_end)
{
	if (!(*list_head))
	{
		(*list_head) = node;
		(*list_end) = node;
	}
	else
	{
		(*list_end)->next = node;
		(*list_end) = node;
	}
}
