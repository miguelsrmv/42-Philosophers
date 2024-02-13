/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:15:02 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/02/13 17:08:18 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_success(t_args *arg, int thread_id)
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

void	update_philo_state(t_args *arg, int thread_id, size_t time_last_meal,
	size_t epoch_time)
{
	(void)time_last_meal;
	pthread_mutex_lock(&arg->death_mutex);
	if (create_print_message(arg, thread_id, get_current_time(), epoch_time)
		!= SUCCESS)
	{
		arg->death_flag++;
		pthread_mutex_unlock(&arg->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&arg->death_mutex);
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
}

enum e_PhiloState	check_death(t_args *arg, int thread_id,
	size_t time_last_meal, size_t epoch_time)
{
	size_t					current_time;
	enum e_PhiloState		return_value;

	return_value = ALIVE;
	current_time = get_current_time();
	pthread_mutex_lock(&arg->death_mutex);
	if (arg->death_flag)
		return_value = DEAD;
	else if (get_time_diff(time_last_meal, current_time) >= arg->time_to_die)
	{
		arg->death_flag++;
		arg->philo_state[thread_id] = DEAD;
		create_print_message(arg, thread_id, get_current_time(), epoch_time);
		return_value = DEAD;
	}
	pthread_mutex_unlock(&arg->death_mutex);
	return (return_value);
	(void)epoch_time;
}
