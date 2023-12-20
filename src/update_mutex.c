/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:15:02 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/20 16:57:21 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_count(int *count, pthread_mutex_t *count_mutex)
{
	pthread_mutex_lock(count_mutex);
	(*count)++;
	pthread_mutex_unlock(count_mutex);
}

void	update_philo_state(t_args *arg, int thread_id, int current_time)
{
	if (arg->philo_state[thread_id] == START_STATE)
		arg->philo_state[thread_id] = AVAILABLE_FOR_EATING_2_FORK_LEFT;
	else if (arg->philo_state[thread_id] == AVAILABLE_FOR_EATING_2_FORK_LEFT)
		arg->philo_state[thread_id] = AVAILABLE_FOR_EATING_1_FORK_LEFT;
	else if (arg->philo_state[thread_id] == AVAILABLE_FOR_EATING_1_FORK_LEFT)
		arg->philo_state[thread_id] = EATING;
	else if (arg->philo_state[thread_id] == EATING)
		arg->philo_state[thread_id] = AVAILABLE_FOR_THINKING;
	else if (arg->philo_state[thread_id] == AVAILABLE_FOR_THINKING)
		arg->philo_state[thread_id] = THINKING;
	else if (arg->philo_state[thread_id] == THINKING)
		arg->philo_state[thread_id] = AVAILABLE_FOR_SLEEPING;
	else if (arg->philo_state[thread_id] == AVAILABLE_FOR_SLEEPING)
		arg->philo_state[thread_id] = SLEEPING;
	else if (arg->philo_state[thread_id] == SLEEPING)
		arg->philo_state[thread_id] = AVAILABLE_FOR_EATING_2_FORK_LEFT;
	print_message(arg, thread_id, current_time);
}

int	check_death(t_args *arg, int thread_id,
	int time_last_action, int start_time)
{
	if (get_time_diff(time_last_action, start_time) > arg->time_to_die)
	{
		arg->philo_state[thread_id] = DEAD;
		update_count(&arg->death_count, &arg->death_count_mutex);
		return (1);
	}
	return (0);
}
