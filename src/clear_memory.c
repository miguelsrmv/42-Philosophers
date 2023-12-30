/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:00:23 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/30 19:49:02 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_args(t_args *arg)
{
	clear_mutexes(arg);
	clear_mallocs(arg);
	clear_linkedlists(arg);
}

void	clear_mutexes(t_args *arg)
{
	int	i;

	pthread_mutex_destroy(&(arg->success_count_mutex));
	pthread_mutex_destroy(&arg->death_mutex);
	pthread_mutex_destroy(&arg->philo_id_mutex);
	pthread_mutex_destroy(&arg->linked_list_mutex);
	pthread_mutex_destroy(&arg->next_to_eat_mutex);
	pthread_mutex_destroy(&arg->cleanup_mutex);
	i = 0;
	while (i < arg->number_of_philos)
	{
		pthread_mutex_destroy(&arg->fork_status_mutex[i]);
		pthread_mutex_destroy(&arg->forks[i++]);
	}
}

void	clear_mallocs(t_args *arg)
{
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
	if (arg->fork_status_mutex)
		free(arg->fork_status_mutex);
}

void	clear_linkedlists(t_args *arg)
{
	t_list	*temp;

	while (arg->output_head)
	{
		temp = arg->output_head;
		arg->output_head = arg->output_head->next;
		if (temp->content)
			free(temp->content);
		free(temp);
	}
	while (arg->next_to_eat_head)
	{
		temp = arg->next_to_eat_head;
		arg->next_to_eat_head = arg->next_to_eat_head->next;
		free(temp);
	}
}
