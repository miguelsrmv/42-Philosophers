/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:48:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/23 19:13:50 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	size_t		start_time;
	int			thread_id;

	pthread_mutex_lock(&(((t_args *)arg)->philo_id_mutex));
	(((t_args *)arg)->philo_id)++;
	thread_id = (((t_args *)arg)->philo_id);
	pthread_mutex_unlock(&(((t_args *)arg)->philo_id_mutex));
	start_time = get_current_time();
	if (!start_time)
		return (NULL);
	if (thread_id == ((t_args *)arg)->number_of_philos)
		printing_thread((t_args *)arg);
	else
		simulation((t_args *)arg,
			thread_id, start_time, ((t_args *)arg)->epoch_time);
	return (NULL);
}

void	wait_for_print_buffer(t_args *arg, t_list **print)
{
	ft_usleep(500);
	while (1)
	{
		pthread_mutex_lock(&arg->linked_list_mutex);
		if (arg->output == NULL || arg->output->next == NULL)
		{
			pthread_mutex_unlock(&arg->linked_list_mutex);
			ft_usleep(500);
		}
		else
		{
			*print = arg->output;
			pthread_mutex_unlock(&arg->linked_list_mutex);
			break ;
		}
	}
}

void	printing_thread(t_args *arg)
{
	t_list	*print;

	wait_for_print_buffer(arg, &print);
	while (print)
	{
		pthread_mutex_lock(&arg->linked_list_mutex);
		write(STDOUT_FILENO, print->content, ft_strlen(print->content));
		pthread_mutex_unlock(&arg->linked_list_mutex);
		if (check_end_of_simulation(arg) == STOP_SIMULATION
			&& !print->next)
			break ;
		ft_usleep(100);
		pthread_mutex_lock(&arg->linked_list_mutex);
		print = print->next;
		pthread_mutex_unlock(&arg->linked_list_mutex);
	}
}

void	simulation(t_args *arg, int thread_id,
			size_t start_time, size_t epoch_time)
{
	while (1)
	{
		if (check_end_of_simulation(arg) == CONTINUE)
		{
			eat_routine(arg, thread_id, start_time, epoch_time);
			start_time = get_current_time();
			update_success(arg, thread_id);
		}
		if (check_end_of_simulation(arg) == CONTINUE)
			sleep_routine(arg, thread_id, start_time, epoch_time);
		if (check_end_of_simulation(arg) == CONTINUE)
			think_routine(arg, thread_id, start_time, epoch_time);
		else
			break ;
	}
	return ;
}

enum e_SimState	check_end_of_simulation(t_args *arg)
{
	int	simulation_state;

	simulation_state = CONTINUE;
	pthread_mutex_lock(&arg->death_mutex);
	if (arg->death_flag)
		simulation_state = STOP_SIMULATION;
	pthread_mutex_unlock(&arg->death_mutex);
	pthread_mutex_lock(&arg->success_count_mutex);
	if (arg->success_count == arg->number_of_philos)
		simulation_state = STOP_SIMULATION;
	pthread_mutex_unlock(&arg->success_count_mutex);
	return (simulation_state);
}
