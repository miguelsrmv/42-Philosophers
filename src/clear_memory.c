/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:00:23 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/29 19:00:55 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_args(t_args *arg)
{
	clear_mutexes(arg);
	clear_memory(arg);
}

void	clear_memory(t_args *arg)
{
	t_list	*temp;

	if (arg->threads)
		free(arg->threads);
	if (arg->philo_state)
		free(arg->philo_state);
	if (arg->forks)
		free(arg->forks);
	if (arg->success_array)
		free(arg->success_array);
	if (arg->fork_status)
		free(arg->fork_status);
	while (arg->head)
	{
		temp = arg->head;
		arg->head = arg->head->next;
		if (temp->content)
			free(temp->content);
		free(temp);
	}
}

void	clear_mutexes(t_args *arg)
{
	int	i;

	pthread_mutex_destroy(&(arg->print_mutex));
	pthread_mutex_destroy(&(arg->success_count_mutex));
	pthread_mutex_destroy(&arg->death_mutex);
	pthread_mutex_destroy(&arg->philo_id_mutex);
	pthread_mutex_destroy(&arg->linked_list_mutex);
	i = 0;
	while (i < arg->number_of_philos)
	{
		pthread_mutex_destroy(&arg->fork_status_mutex[i]);
		pthread_mutex_destroy(&arg->forks[i++]);
	}
}
