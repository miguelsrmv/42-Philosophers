/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:08:23 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/22 19:05:58 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_routine(t_args *arg, int thread_id,
	size_t time_last_meal, size_t epoch_time)
{
	if (thread_id % 2 == 0)
	{
		take_left_fork(arg, thread_id, time_last_meal, epoch_time);
		take_right_fork(arg, thread_id, time_last_meal, epoch_time);
	}
	else
	{
		take_right_fork(arg, thread_id, time_last_meal, epoch_time);
		take_left_fork(arg, thread_id, time_last_meal, epoch_time);
	}
	if (arg->number_of_philos > 1)
	{
		ft_usleep(arg->time_to_eat);
		update_philo_state(arg, thread_id, get_current_time(), epoch_time);
		pthread_mutex_unlock
			(&arg->forks[(thread_id + 1) % arg->number_of_philos]);
	}
	pthread_mutex_unlock(&arg->forks[thread_id]);
}

void	take_left_fork(t_args *arg, int thread_id,
			size_t time_last_meal, size_t epoch_time)
{
	pthread_mutex_lock(&arg->forks[thread_id]);
	update_philo_state(arg, thread_id, time_last_meal, epoch_time);
}

void	take_right_fork(t_args *arg, int thread_id,
			size_t time_last_meal, size_t epoch_time)
{
	if (arg->number_of_philos == 1)
		ft_usleep(arg->time_to_die);
	else
		pthread_mutex_lock
			(&arg->forks[((thread_id + 1) % arg->number_of_philos)]);
	update_philo_state(arg, thread_id, time_last_meal, epoch_time);
}

void	sleep_routine(t_args *arg, int thread_id,
	size_t time_last_meal, size_t epoch_time)
{
	size_t	remaining_time;

	update_philo_state(arg, thread_id, time_last_meal, epoch_time);
	remaining_time = arg->time_to_die - (get_current_time() - time_last_meal);
	if (arg->time_to_sleep < remaining_time)
		ft_usleep(arg->time_to_sleep);
	else
		ft_usleep(remaining_time);
}

void	think_routine(t_args *arg, int thread_id,
	size_t time_last_meal, size_t epoch_time)
{
	update_philo_state(arg, thread_id, time_last_meal, epoch_time);
}
