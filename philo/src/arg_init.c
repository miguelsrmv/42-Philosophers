/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:46:08 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/02 19:58:39 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Initializes table struct
t_ErrorCode	init_table(t_table *table, int argc, char **argv)
{
	table->number_of_philos = ft_atoi(argv[1]);
	table->success_count = 0;
	table->death_flag = false;
	table->success_flag = false;
	table->simulation_run = false;
	table->message_head = NULL;
	table->message_end = NULL;
	table->forks = (t_forks *)malloc((table->number_of_philos)
			* sizeof(t_forks));
	if (!table->forks)
		return (MALLOC_ERROR);
	table->philos = (t_philos *)malloc((table->number_of_philos + 1)
			* sizeof(t_philos));
	if (!table->philos)
	{
		free(table->forks);
		return (MALLOC_ERROR);
	}
	init_philo_data(table, argc, argv);
	init_fork_data(table);
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
		philo->table = table;
		if (i)
		{
			philo->eat_count = 0;
			setup_philo_times(philo, argc, argv);
			assign_forks(philo, table, i);
		}
		i++;
	}
}

// Sets up times from argv
// Defines time_to_think depending on argv parameters
void	setup_philo_times(t_philos *philo, int argc, char **argv)
{
	philo->time_to_die = (size_t)ft_atoi(argv[TIME_TO_DIE]);
	philo->time_to_eat = (size_t)ft_atoi(argv[TIME_TO_EAT]);
	philo->time_to_sleep = (size_t)ft_atoi(argv[TIME_TO_SLEEP]);
	if ((philo->table->number_of_philos % 2)
		&& philo->time_to_eat <= philo->time_to_sleep)
		philo->time_to_think = philo->time_to_eat * 2 - philo->time_to_sleep;
	else
		philo->time_to_think = 0;
	if (argc == 6)
		philo->times_each_philosopher_must_eat
			= ft_atoi(argv[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT]);
	else
		philo->times_each_philosopher_must_eat = -1;
}

// Assigns forks for each philo, depending if odd or even
void	assign_forks(t_philos *philo, t_table *table, int i)
{
	if (philo->philo_id % 2 != 0)
	{
		philo->first_fork
			= &(table->forks[(i) % table->number_of_philos]);
		philo->second_fork = &(table->forks[i - 1]);
	}
	else
	{
		philo->first_fork = &(table->forks[i - 1]);
		philo->second_fork
			= &(table->forks[(i) % table->number_of_philos]);
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
		i++;
	}
}
