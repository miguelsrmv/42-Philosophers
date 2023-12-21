/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:48:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/21 20:14:03 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	size_t		start_time;
	int			thread_id;

	pthread_mutex_lock(&(((t_args *)arg)->philo_id_mutex));
	(((t_args *)arg)->philo_id)++;
	pthread_mutex_unlock(&(((t_args *)arg)->philo_id_mutex));
	thread_id = (((t_args *)arg)->philo_id);
	start_time = get_current_time();
	if (!start_time)
		return (NULL);
	if (((t_args *)arg)->times_each_philosopher_must_eat >= 0)
		simulation_stop_at_success_or_death((t_args *)arg,
			thread_id, start_time, start_time);
	else
		simulation_stop_at_death((t_args *)arg, thread_id, start_time,
			start_time);
	return (NULL);
}

// Rever caso de sucesso, são TODOS os filósofos que têem que comer X vezes!
void	simulation_stop_at_success_or_death(t_args *arg, int thread_id,
			size_t start_time, size_t epoch_time)
{
	while (1)
	{
		if (!(arg->death_flag) && arg->success_count
			< arg->times_each_philosopher_must_eat)
		{
			eat_routine(arg, thread_id, start_time, epoch_time);
			start_time = get_current_time();
		}
		if (!(arg->death_flag) && arg->success_count
			< arg->times_each_philosopher_must_eat)
			sleep_routine(arg, thread_id, start_time, epoch_time);
		if (!(arg->death_flag) && arg->success_count
			< arg->times_each_philosopher_must_eat)
			think_routine(arg, thread_id, start_time, epoch_time);
		else
			break ;
	}
	return ;
}

void	simulation_stop_at_death(t_args *arg, int thread_id,
			size_t start_time, size_t epoch_time)
{
	while (1)
	{
		if (!(arg->death_flag))
		{
			eat_routine(arg, thread_id, start_time, epoch_time);
			start_time = get_current_time();
		}
		if (!(arg->death_flag))
			sleep_routine(arg, thread_id, start_time, epoch_time);
		if (!(arg->death_flag))
			think_routine(arg, thread_id, start_time, epoch_time);
		else
			break ;
	}
	return ;
}