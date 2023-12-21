/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:15:02 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/21 22:06:27 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	decrement_array(t_args *arg, int thread_id)
{
	arg->success_array[thread_id]--;
	if (arg->success_array[thread_id] == 0)
		update_count(&arg->success_count, &arg->success_count_mutex);
}

void	update_count(int *count, pthread_mutex_t *count_mutex)
{
	pthread_mutex_lock(count_mutex);
	(*count)++;
	pthread_mutex_unlock(count_mutex);
}

int	update_philo_state(t_args *arg, int thread_id, size_t *time_last_meal,
	size_t *epoch_time)
{
	pthread_mutex_lock(&arg->print_mutex);
	if (check_death(arg, thread_id, *time_last_meal, *epoch_time)
		|| arg->success_count == arg->times_each_philosopher_must_eat)
		return (0);
	print_message(arg, thread_id, get_current_time(), *epoch_time);
	if (arg->philo_state[thread_id] == AVAILABLE_FOR_EATING_2_FORK_LEFT)
		arg->philo_state[thread_id] = AVAILABLE_FOR_EATING_1_FORK_LEFT;
	else if (arg->philo_state[thread_id] == AVAILABLE_FOR_EATING_1_FORK_LEFT)
		arg->philo_state[thread_id] = EATING;
	else if (arg->philo_state[thread_id] == EATING)
		arg->philo_state[thread_id] = SLEEPING;
	else if (arg->philo_state[thread_id] == SLEEPING)
		arg->philo_state[thread_id] = THINKING;
	else if (arg->philo_state[thread_id] == THINKING)
		arg->philo_state[thread_id] = AVAILABLE_FOR_EATING_2_FORK_LEFT;
	return (1);
}

int	check_death(t_args *arg, int thread_id,
	size_t time_last_meal, size_t epoch_time)
{
	size_t	current_time;

	current_time = get_current_time();
	if (arg->death_flag)
	{
		pthread_mutex_unlock(&arg->print_mutex);
		return (1);
	}
	else if (get_time_diff(time_last_meal, current_time) > arg->time_to_die)
	{
		pthread_mutex_lock(&arg->death_mutex);
		if (arg->death_flag)
			return (1);
		arg->death_flag++;
		arg->philo_state[thread_id] = DEAD;
		print_message(arg, thread_id, current_time, epoch_time);
		return (1);
	}
	return (0);
}
