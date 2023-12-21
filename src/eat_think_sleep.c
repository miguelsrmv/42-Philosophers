/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:08:23 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/21 21:52:14 by mde-sa--         ###   ########.fr       */
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
	//ft_usleep(arg->time_to_eat);
	usleep(arg->time_to_eat);
	decrement_array(arg, thread_id);
	update_philo_state(arg, thread_id, &time_last_meal, &epoch_time);
//	print_message_helper(arg, thread_id, "Finished eating!\n");
	pthread_mutex_unlock(&arg->forks[thread_id]);
	pthread_mutex_unlock
		(&arg->forks[(thread_id + 1) % arg->number_of_philos]);
}

void	take_left_fork(t_args *arg, int thread_id,
			size_t time_last_meal, size_t epoch_time)
{
	pthread_mutex_lock(&arg->forks[thread_id]);
/*  	char *right_msg = ft_itoa(thread_id);
	char *message = ft_strjoin("LEFT:		fork #", right_msg);
	print_message_helper(arg, thread_id, message);
	free(right_msg);
	free(message); */
	update_philo_state(arg, thread_id, &time_last_meal, &epoch_time);
}

void	take_right_fork(t_args *arg, int thread_id,
			size_t time_last_meal, size_t epoch_time)
{
	pthread_mutex_lock
		(&arg->forks[((thread_id + 1) % arg->number_of_philos)]);
/*   	char *right_msg = ft_itoa((thread_id + 1) % arg->number_of_philos);
	char *message = ft_strjoin("RIGHT:		fork #", right_msg);
	print_message_helper(arg, thread_id, message);
	free(right_msg);
	free(message); */
	update_philo_state(arg, thread_id, &time_last_meal, &epoch_time);
}

void	sleep_routine(t_args *arg, int thread_id,
	size_t time_last_meal, size_t epoch_time)
{
	size_t	remaining_time;

	update_philo_state(arg, thread_id, &time_last_meal, &epoch_time);
	remaining_time = arg->time_to_die - (get_current_time() - time_last_meal);
	if (arg->time_to_sleep < remaining_time)
		usleep(arg->time_to_sleep);
		//ft_usleep(arg->time_to_sleep);
	else
		usleep(remaining_time);
		//ft_usleep(remaining_time);
}

void	think_routine(t_args *arg, int thread_id,
	size_t time_last_meal, size_t epoch_time)
{
	update_philo_state(arg, thread_id, &time_last_meal, &epoch_time);
}
