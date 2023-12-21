/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:00:23 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/21 20:26:57 by mde-sa--         ###   ########.fr       */
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
	if (arg->threads)
		free(arg->threads);
	if (arg->philo_state)
		free(arg->philo_state);
	if (arg->forks)
		free(arg->forks);
	if (arg->success_array)
		free(arg->success_array);
}

void	clear_mutexes(t_args *arg)
{
	int	i;

	pthread_mutex_destroy(&(arg->print_mutex));
	pthread_mutex_destroy(&(arg->success_count_mutex));
	pthread_mutex_destroy(&arg->death_mutex);
	pthread_mutex_destroy(&arg->philo_id_mutex);
	i = 0;
	while (i < arg->number_of_philos)
		pthread_mutex_destroy(&arg->forks[i++]);



}
