/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:29:17 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/04 23:04:44 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philos)
	{
		args->philo_id = (int *)malloc(sizeof(int));
		if (!args->philo_id)
			return (MALLOC_ERROR);
		*(args->philo_id) = i + 1;
		if (pthread_create(&(args->philo[i]), NULL, &routine, args) != 0)
			return (THREAD_ERROR);
		sleep(1);
		i++;
	}
	return (SUCCESS);
}

int	join_threads(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philos)
	{
		if (pthread_join(args->philo[i], NULL) != 0)
			return (THREAD_ERROR);
		i++;
	}
	return (SUCCESS);
}
