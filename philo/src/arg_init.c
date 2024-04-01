/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:46:08 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/01 15:55:21 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Initializes table struct
t_ErrorCode	init_table(t_table *table, int argc, char **argv)
{
	table->number_of_philos = ft_atoi(argv[1]);
	table->success_count = 0;
	table->death_flag = false;
	table->simulation_run = false;
	table->message_head = NULL;
	table->message_end = NULL;
	if (malloc_table_data(table) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	init_philo_data(table, argc, argv);
	init_fork_data(table);
	return (SUCCESS);
}

// Allocates data for fork and philo array of structs
t_ErrorCode	malloc_table_data(t_table *table)
{
	table->forks = (t_forks *)malloc((table->number_of_philos)
			* sizeof(t_forks));
	if (!table->forks)
		return (MALLOC_ERROR);
	table->philos = (t_philos *)malloc((1 + table->number_of_philos)
			* sizeof(t_philos));
	if (!table->philos)
	{
		free(table->forks);
		return (MALLOC_ERROR);
	}
	return (SUCCESS);
}

// Initializes philo data for each philo
void	init_philo_data(t_table *table, int argc, char **argv)
{
	int			i;
	t_philos	*philo;

	i = 0;
	while (i <= table->number_of_philos)
	{
		philo = &(table->philos)[i];
		philo->philo_id = i;
		philo->state = MISSING_2_FORK;
		philo->full = false;
		philo->time_to_die = (size_t)ft_atoi(argv[2]);
		philo->time_to_eat = (size_t)ft_atoi(argv[3]);
		philo->time_to_sleep = (size_t)ft_atoi(argv[4]);
		if (argc == 6)
			philo->times_each_philosopher_must_eat = (size_t)ft_atoi(argv[5]);
		else
			philo->times_each_philosopher_must_eat = -1;
		assign_forks(philo, table, i);
		philo->table = table;
		i++;
	}
}

void	assign_forks(t_philos *philo, t_table *table, int i)
{
	if (philo->philo_id % 2 != 0)
	{
		philo->first_fork
			= &(table->forks[(i + 1) % table->number_of_philos]);
		philo->second_fork = &(table->forks[i]);
	}
	else
	{
		philo->first_fork = &(table->forks[i]);
		philo->second_fork
			= &(table->forks[(i + 1) % table->number_of_philos]);
	}
}

// Initializes fork data for each fork
void	init_fork_data(t_table *table)
{
	int			i;
	t_forks		*fork;

	i = 1;
	while (i <= table->number_of_philos)
	{
		fork = &(table->forks[i - 1]);
		fork->fork_id = i;
		fork->fork_status = AVAILABLE;
		i++;
	}
}
