/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:15:02 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/20 22:09:19 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_count(int *count, pthread_mutex_t *count_mutex)
{
	pthread_mutex_lock(count_mutex);
	(*count)++;
	pthread_mutex_unlock(count_mutex);
}

int	update_philo_state(t_args *arg, int thread_id, int time_last_meal,
	int current_time)
{
	if (check_death(arg, thread_id, time_last_meal, current_time))
		return (0);
	else if (arg->philo_state[thread_id] == START_STATE)
		arg->philo_state[thread_id] = AVAILABLE_FOR_EATING_2_FORK_LEFT;
	else if (arg->philo_state[thread_id] == AVAILABLE_FOR_EATING_2_FORK_LEFT)
		arg->philo_state[thread_id] = AVAILABLE_FOR_EATING_1_FORK_LEFT;
	else if (arg->philo_state[thread_id] == AVAILABLE_FOR_EATING_1_FORK_LEFT)
		arg->philo_state[thread_id] = EATING;
	else if (arg->philo_state[thread_id] == EATING)
		arg->philo_state[thread_id] = AVAILABLE_FOR_SLEEPING;
	else if (arg->philo_state[thread_id] == AVAILABLE_FOR_SLEEPING)
		arg->philo_state[thread_id] = SLEEPING;
	else if (arg->philo_state[thread_id] == SLEEPING)
		arg->philo_state[thread_id] = AVAILABLE_FOR_THINKING;
	else if (arg->philo_state[thread_id] == AVAILABLE_FOR_THINKING)
		arg->philo_state[thread_id] = THINKING;
	else if (arg->philo_state[thread_id] == THINKING)
		arg->philo_state[thread_id] = AVAILABLE_FOR_EATING_2_FORK_LEFT;
	print_message(arg, thread_id, current_time);
	return (1);
}

int	check_death(t_args *arg, int thread_id,
	int time_last_meal, int current_time)
{
	if (arg->number_of_times_each_philosopher_must_eat < 0
		&& arg->death_count > 0)
		return (1);
	else if (get_time_diff(time_last_meal, current_time) > arg->time_to_die)
	{
		arg->philo_state[thread_id] = DEAD;
		print_message(arg, thread_id, current_time);
		update_count(&arg->death_count, &arg->death_count_mutex);
		return (1);
	}
	return (0);
}
