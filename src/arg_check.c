/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:33:22 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/20 21:57:09 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		ft_printf(ARG_MESSAGE);
		return (ARG_ERROR);
	}
	i = 1;
	while (argv[i] && *argv[i] != 0)
	{
		if (!ft_isdigit(*argv[i++]))
		{
			ft_printf(ARG_MESSAGE);
			return (ARG_ERROR);
		}
	}
	return (SUCCESS);
}

int	init_args(t_args *args, int argc, char **argv)
{
	args->number_of_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]) * 10000;
	args->time_to_eat = ft_atoi(argv[3]) * 10000;
	args->time_to_sleep = ft_atoi(argv[4]) * 10000;
	if (argc == 6)
		args->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		args->number_of_times_each_philosopher_must_eat = -1;
	args->threads = (pthread_t *)malloc(args->number_of_philos
			* sizeof(pthread_t));
	args->philo_state = (enum e_PhiloState *)malloc(args->number_of_philos
			* sizeof(enum e_PhiloState));
	args->forks = (enum e_ForkState *)malloc(args->number_of_philos
			* sizeof(enum e_ForkState));
	args->forks_mutex = (pthread_mutex_t *)malloc((args->number_of_philos)
			* sizeof(pthread_mutex_t));
	if (!args->threads || !args->philo_state
		|| !args->forks || !args->forks_mutex)
		return (MALLOC_ERROR);
	args->philo_id = -1;
	args->death_count = 0;
	args->success_count = 0;
	init_mutexes(args);
	return (SUCCESS);
}

void	init_mutexes(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philos)
	{
		args->philo_state[i] = START_STATE;
		pthread_mutex_init(&args->forks_mutex[i++], NULL);
	}
	pthread_mutex_init(&(args->philo_id_mutex), NULL);
	pthread_mutex_init(&(args->death_count_mutex), NULL);
	pthread_mutex_init(&(args->success_count_mutex), NULL);
	pthread_mutex_init(&(args->print_mutex), NULL);
}

void	clear_args(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philos)
		pthread_mutex_destroy(&args->forks_mutex[i++]);
	pthread_mutex_destroy(&args->philo_id_mutex);
	pthread_mutex_destroy(&(args->death_count_mutex));
	pthread_mutex_destroy(&(args->success_count_mutex));
	pthread_mutex_destroy(&(args->print_mutex));
	free(args->threads);
	free(args->philo_state);
	free(args->forks);
	free(args->forks_mutex);
}
