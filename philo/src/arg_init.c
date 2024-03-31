/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:46:08 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 18:06:29 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_table(t_table *table, int argc, char **argv)
{
	table->number_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		table->times_each_philosopher_must_eat = -1;
	table->epoch_time = 0;
	table->success_count = 0;
	table->death_flag = false;
	table->message_head = NULL;
	table->message_end = NULL;
	if (malloc_table_data(table) == MALLOC_ERROR)
	{
		clean_mallocs(table);
		return (MALLOC_ERROR);
	}
	init_malloc_data(table);
	return (SUCCESS);
}

int	malloc_table_data(t_table *table)
{
	table->forks = (t_forks *)malloc((1 + table->number_of_philos)
			* sizeof(t_forks));
	table->philos = (t_philos *)malloc((1 + table->number_of_philos)
			* sizeof(t_philos));
	table->message_head = (t_message *)malloc(sizeof(t_message));
	if (!table->forks || !table->philos || !table->message_head)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

void	init_malloc_data(t_table *table)
{
	int			i;
	t_philos	*philo;
	t_forks		*fork;

	i = 0;
	while (i < table->number_of_philos)
	{
		philo = &(table->philos)[i];
		philo->philo_id = i + 1;
		philo->state = MISSING_2_FORK;
		philo->full = false;
		philo->first_fork = &(table->forks[(i + 1) % table->number_of_philos]);
		philo->second_fork = &(table->forks[i]);
		if (philo->philo_id % 2 == 0)
		{
			philo->first_fork = &(table->forks[i]);
			philo->second_fork
				= &(table->forks[(i + 1) % table->number_of_philos]);
		}
		fork = &(table->forks[i]);
		fork->fork_id = i + 1;
		fork->fork_status = AVAILABLE;
		i++;
	}
	table->message_head = NULL;
}

int	init_mutexes(t_table *table)
{
	int			i;
	t_forks		*fork;

	if (pthread_mutex_init(&(table->success_mutex), NULL)
		|| (pthread_mutex_init(&(table->death_mutex), NULL))
		|| (pthread_mutex_init(&(table->message_mutex), NULL)))
	{
		clean_data(table);
		return (MUTEX_ERROR);
	}
	i = 0;
	while (i < table->number_of_philos)
	{
		fork = &(table->forks[i]);
		if (pthread_mutex_init(&(fork->fork_mutex), NULL))
		{
			clean_data(table);
			return (MUTEX_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
