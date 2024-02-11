/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:46:08 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/30 19:50:24 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_args(t_args *arg, int argc, char **argv)
{
	arg->number_of_philos = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		arg->times_each_philosopher_must_eat = -1;
	arg->philo_id = -1;
	arg->death_flag = 0;
	arg->success_count = 0;
	arg->output = NULL;
	arg->output_head = NULL;
	arg->output_end = NULL;
	arg->next_to_eat = NULL;
	arg->next_to_eat_head = NULL;
	arg->next_to_eat_end = NULL;
	if (init_mem_alloc(arg) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

int	init_mem_alloc(t_args *arg)
{
	arg->success_array = (int *)malloc(arg->number_of_philos
			* sizeof(int));
	arg->philo_state = (enum e_PhiloState *)malloc(arg->number_of_philos
			* sizeof(enum e_PhiloState));
	arg->threads = (pthread_t *)malloc((arg->number_of_philos + 1)
			* sizeof(pthread_t));
	arg->forks = (pthread_mutex_t *)malloc((arg->number_of_philos)
			* sizeof(pthread_mutex_t));
	arg->fork_status = (enum e_ForkStatus *)malloc(arg->number_of_philos
			* sizeof(enum e_ForkStatus));
	arg->fork_status_mutex = (pthread_mutex_t *)malloc(arg->number_of_philos
			* sizeof(pthread_mutex_t));
	arg->fork_holder = (int *)malloc(arg->number_of_philos
			* sizeof(int));
	if (!arg->success_array || !arg->philo_state || !arg->threads
		|| !arg->forks || !arg->fork_status || !arg->fork_status_mutex
		|| !arg->fork_holder)
	{
		clear_mallocs(arg);
		return (MALLOC_ERROR);
	}
	fill_in_args_arrays(arg);
	return (SUCCESS);
}

void	fill_in_args_arrays(t_args *arg)
{
	int	i;

	i = 0;
	while (i < arg->number_of_philos)
	{
		arg->success_array[i] = arg->times_each_philosopher_must_eat;
		arg->fork_status[i] = AVAILABLE;
		arg->fork_holder[i] = -1;
		arg->philo_state[i++] = AVAILABLE_FOR_EATING_2_FORK_LEFT;
	}
}

int	init_mutexes(t_args *arg)
{
	int	return_value;
	int	i;

	return_value = SUCCESS;
	if (pthread_mutex_init(&(arg->success_count_mutex), NULL)
		|| (pthread_mutex_init(&(arg->death_mutex), NULL))
		|| (pthread_mutex_init(&(arg->philo_id_mutex), NULL))
		|| (pthread_mutex_init(&(arg->linked_list_mutex), NULL))
		|| (pthread_mutex_init(&(arg->next_to_eat_mutex), NULL))
		|| (pthread_mutex_init(&(arg->cleanup_mutex), NULL)))
		return_value = MUTEX_ERROR;
	i = 0;
	while (i < arg->number_of_philos)
	{
		if (pthread_mutex_init(&arg->forks[i], NULL))
			return_value = MUTEX_ERROR;
		if (pthread_mutex_init(&arg->fork_status_mutex[i++], NULL))
			return_value = MUTEX_ERROR;
	}
	if (return_value == MUTEX_ERROR)
		clear_args(arg);
	return (return_value);
}
