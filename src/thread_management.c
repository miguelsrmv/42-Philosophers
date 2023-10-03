/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:29:17 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/03 11:55:22 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_global(&args, philo, &print_mutex)
{
	
}

int	create_threads(t_args *args, pthread_t *philo)
{
	int i;
	
	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_create(&philo[i], NULL, &routine, &i) != 0)
			return (THREAD_ERROR);
		i++;
	}
	return (SUCCESS);
}

int	join_threads(t_args *args, pthread_t *philo)
{
	int i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_join(philo[i], NULL) != 0)
			return (THREAD_ERROR);
		i++;
	}
	return (SUCCESS);
}