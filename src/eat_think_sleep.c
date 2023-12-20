/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:08:23 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/20 22:53:24 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_routine(t_args *arg, int thread_id,
	int time_last_meal, int start_time)
{
	if (thread_id % 2 == 0)
	{
		take_left_fork(arg, thread_id, time_last_meal, start_time);
		take_right_fork(arg, thread_id, time_last_meal, get_current_time());
	}
	else
	{
		take_right_fork(arg, thread_id, time_last_meal, start_time);
		take_left_fork(arg, thread_id, time_last_meal, get_current_time());
	}
	usleep(arg->time_to_eat);
	update_count(&arg->success_count, &arg->success_count_mutex);
	update_philo_state(arg, thread_id, time_last_meal, get_current_time());
//	print_message_helper(arg, thread_id, "Finished eating!\n");
	pthread_mutex_unlock(&arg->forks_mutex[thread_id]);
	pthread_mutex_unlock
		(&arg->forks_mutex[(thread_id + 1) % arg->number_of_philos]);
}

void	take_left_fork(t_args *arg, int thread_id,
			int time_last_meal, int start_time)
{
	pthread_mutex_lock(&arg->forks_mutex[thread_id]);
/* 	char *right_msg = ft_itoa(thread_id);
	char *message = ft_strjoin("LEFT:		fork #", right_msg);
	print_message_helper(arg, thread_id, message);
	free(right_msg);
	free(message);  */
	update_philo_state(arg, thread_id, time_last_meal, start_time);
}

void	take_right_fork(t_args *arg, int thread_id,
			int time_last_meal, int start_time)
{
	pthread_mutex_lock
		(&arg->forks_mutex[((thread_id + 1) % arg->number_of_philos)]);
/*    	char *right_msg = ft_itoa((thread_id + 1) % arg->number_of_philos);
	char *message = ft_strjoin("RIGHT:		fork #", right_msg);
	print_message_helper(arg, thread_id, message);
	free(right_msg);
	free(message); */
	update_philo_state(arg, thread_id, time_last_meal, start_time);
}

void	sleep_routine(t_args *arg, int thread_id,
	int time_last_meal, int start_time)
{
	update_philo_state(arg, thread_id, time_last_meal, get_current_time());
	usleep(arg->time_to_sleep);
	(void)time_last_meal;
	(void)start_time;
}

void	think_routine(t_args *arg, int thread_id,
	int time_last_meal, int start_time)
{
	update_philo_state(arg, thread_id, time_last_meal, start_time);
	(void)time_last_meal;
}
