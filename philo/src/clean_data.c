/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:26:07 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 18:04:52 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_data(t_table *table)
{
	clean_mutexes(table);
	clean_mallocs(table);
	if (table->message_head)
		printf("Don't forget to clean the messages!\n");
}

void	clean_mutexes(t_table *table)
{
	int		i;
	t_forks	*fork;

	pthread_mutex_destroy(&(table->success_mutex));
	pthread_mutex_destroy(&(table->death_mutex));
	pthread_mutex_destroy(&(table->message_mutex));
	i = 0;
	while (i < table->number_of_philos)
	{
		fork = &(table->forks[i]);
		pthread_mutex_destroy(&(fork->fork_mutex));
		i++;
	}
}

void	clean_mallocs(t_table *table)
{
	free(table->forks);
	free(table->philos);
	list_clear(table->message_head);
}

void	list_clear(t_message *message_head)
{
	t_message	*temp;

	while (message_head)
	{
		temp = (message_head)-> next;
		free(message_head);
		message_head = temp;
	}
	message_head = NULL;
}
