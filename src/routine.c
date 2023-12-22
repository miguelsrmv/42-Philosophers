/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:48:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/22 19:23:48 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	size_t		start_time;
	int			thread_id;

	pthread_mutex_lock(&(((t_args *)arg)->philo_id_mutex));
	(((t_args *)arg)->philo_id)++;
	pthread_mutex_unlock(&(((t_args *)arg)->philo_id_mutex));
	thread_id = (((t_args *)arg)->philo_id);
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

void	printing_thread(t_args *arg)
{
	char	*message;

	while (1)
	{
		while (arg->output == NULL)
			ft_usleep(50);
		message = (char *)arg->output->content;
		if (message != NULL)
		{
			write(STDOUT_FILENO, message, ft_strlen(message));
			arg->head = arg->output;
			arg->output = arg->output->next;
			free(message);
		}
		ft_usleep(10);
		if ((arg->death_flag || arg->success_count == arg->number_of_philos)
			&& !arg->head->next)
			break ;
		free(arg->head);
	}
}

void	simulation(t_args *arg, int thread_id,
			size_t start_time, size_t epoch_time)
{
	while (1)
	{
		if (!(arg->death_flag))
		{
			eat_routine(arg, thread_id, start_time, epoch_time);
			start_time = get_current_time();
			update_success(arg, thread_id);
			if (arg->success_count == arg->number_of_philos)
				return ;
		}
		if (!(arg->death_flag))
			sleep_routine(arg, thread_id, start_time, epoch_time);
		if (!(arg->death_flag))
			think_routine(arg, thread_id, start_time, epoch_time);
		else
			break ;
	}
	return ;
}
