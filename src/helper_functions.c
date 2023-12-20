/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:17:00 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/20 22:55:08 by mde-sa--         ###   ########.fr       */
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

void	print_state(t_args *arg, int thread_id)
{
	char	*message;
	char	*message_right;
	int		state;

	state = arg->philo_state[thread_id];
	if (state == 0)
		message_right = "START STATE";
	else if (state == 1)
		message_right = "AVAILABLE FOR EATING (2 FORKS LEFT)";
	else if (state == 2)
		message_right = "AVAILABLE FOR EATING (1 FORKS LEFT)";
	else if (state == 3)
		message_right = "EATING";
	else if (state == 4)
		message_right = "SLEEPING";
	else if (state == 5)
		message_right = "THINKING";
	else if (state == 6)
		message_right = "DEAD";
	message = ft_strjoin("State: ", message_right);
	print_message_helper(arg, thread_id, message);
	free(message);
}
