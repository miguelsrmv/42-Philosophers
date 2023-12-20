/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:17:00 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/20 16:50:10 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_args(t_args *args)
{
	ft_printf("1. Number of Philosophers: %i\n", args->number_of_philos);
	ft_printf("2. Time to die: %i\n", args->time_to_die);
	ft_printf("3. Time_to_eat: %i\n", args->time_to_eat);
	ft_printf("4. Time_to_sleep: %i\n", args->time_to_sleep);
	ft_printf("5. Number of times each philosopher must eat: ");
	ft_printf("%i\n\n\n", args->number_of_times_each_philosopher_must_eat);
}

void	print_message_helper(t_args *args, int thread_id, char *message)
{
	pthread_mutex_lock(&args->print_mutex);
	ft_printf("Thread %i (philo %i): %s", thread_id, thread_id + 1, message);
	ft_printf("\n");
	pthread_mutex_unlock(&args->print_mutex);
}
