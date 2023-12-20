/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:08:23 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/20 16:53:18 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_routine(t_args *arg, int thread_id,
	int time_last_action, int start_time)
{
	// Se já tiver passado muito tempo, mata o filósofo
	if (check_death(arg, thread_id, time_last_action, start_time))
		return ;
	// Tira um garfo, depois tira outro (ordem depende do número do filósofo)
	if (thread_id % 2 == 0)
	{
		take_left_fork(arg, thread_id);
		take_right_fork(arg, thread_id);
	}
	else
	{
		take_right_fork(arg, thread_id);
		take_left_fork(arg, thread_id);
	}
	// Faz update para está a comer
	update_philo_state(arg, thread_id, start_time);
	usleep((arg->time_to_eat) * 10000);
	update_count(&arg->success_count, &arg->success_count_mutex);
	pthread_mutex_unlock(&arg->forks_mutex[thread_id]);
	pthread_mutex_unlock
		(&arg->forks_mutex[(thread_id + 1) % arg->number_of_philos]);
	print_message_helper(arg, thread_id, "Both forks down!");
}

void	take_left_fork(t_args *arg, int thread_id)
{
	pthread_mutex_lock(&arg->forks_mutex[thread_id]);
 	char *right_msg = ft_itoa(thread_id);
	char *message = ft_strjoin("LEFT:		fork #", right_msg);
	print_message_helper(arg, thread_id, message);
	free(right_msg);
	free(message);
	arg->forks[thread_id] = TAKEN;
	update_philo_state(arg, thread_id, get_current_time());
}

void	take_right_fork(t_args *arg, int thread_id)
{
	pthread_mutex_lock
		(&arg->forks_mutex[((thread_id + 1) % arg->number_of_philos)]);
 	char *right_msg = ft_itoa((thread_id + 1) % arg->number_of_philos);
	char *message = ft_strjoin("RIGHT:		fork #", right_msg);
	print_message_helper(arg, thread_id, message);
	free(right_msg);
	free(message);
	update_philo_state(arg, thread_id, get_current_time());
}

void	sleep_routine(t_args *arg, int thread_id,
	int time_last_action, int start_time)
{
	if (check_death(arg, thread_id, time_last_action, start_time))
		return ;
	update_philo_state(arg, thread_id, start_time);
	usleep((arg->time_to_sleep) * 10000);
}

void	think_routine(t_args *arg, int thread_id,
	int time_last_action, int start_time)
{
	if (check_death(arg, thread_id, time_last_action, start_time))
		return ;
	update_philo_state(arg, thread_id, start_time);
}
