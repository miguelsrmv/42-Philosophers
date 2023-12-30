/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:07:39 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/30 19:51:10 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup_forks(t_args *arg, int thread_id)
{
	int	i;

	i = 0;
	pthread_mutex_lock(arg->fork_status_mutex);
	while (i < arg->number_of_philos)
	{
		if (arg->fork_holder[i] == thread_id)
			pthread_mutex_unlock(&arg->forks[i]);
		i++;
	}
	pthread_mutex_unlock(arg->fork_status_mutex);
}

void	take_left_fork(t_args *arg, int thread_id,
			size_t time_last_meal, size_t epoch_time)
{
	while (1)
	{
		if (check_death(arg, thread_id, time_last_meal, epoch_time) == DEAD)
			return ;
		if (check_fork(arg, thread_id) == AVAILABLE)
		{
			pthread_mutex_lock(&arg->forks[thread_id]);
			break ;
		}
	}
	update_philo_state(arg, thread_id, time_last_meal, epoch_time);
	update_fork(&arg, thread_id, thread_id);
}

void	take_right_fork(t_args *arg, int thread_id,
			size_t time_last_meal, size_t epoch_time)
{
	while (1)
	{
		if (check_death(arg, thread_id, time_last_meal, epoch_time) == DEAD)
			return ;
		if (check_fork(arg, ((thread_id + 1)
					% arg->number_of_philos)) == AVAILABLE)
		{
			pthread_mutex_lock (&arg->forks[((thread_id + 1)
					% arg->number_of_philos)]);
			break ;
		}
	}
	update_philo_state(arg, thread_id, time_last_meal, epoch_time);
	update_fork(&arg, (thread_id + 1) % arg->number_of_philos, thread_id);
}

enum e_ForkStatus	check_fork(t_args *arg, int fork_position)
{
	enum e_ForkStatus	fork_state;

	pthread_mutex_lock(arg->fork_status_mutex);
	fork_state = arg->fork_status[fork_position];
	pthread_mutex_unlock(arg->fork_status_mutex);
	return (fork_state);
}

void	update_fork(t_args **arg, int fork_position, int thread_id)
{
	pthread_mutex_lock((*arg)->fork_status_mutex);
	if ((*arg)->fork_status[fork_position] == AVAILABLE)
	{
		(*arg)->fork_status[fork_position] = TAKEN;
		(*arg)->fork_holder[fork_position] = thread_id;
	}
	else
	{
		(*arg)->fork_status[fork_position] = AVAILABLE;
		(*arg)->fork_holder[fork_position] = -1;
	}
	pthread_mutex_unlock((*arg)->fork_status_mutex);
}
