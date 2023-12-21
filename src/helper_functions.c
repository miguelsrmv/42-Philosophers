/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:17:00 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/21 19:19:18 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <string.h>

void	print_args(t_args *arg)
{
	ft_printf("1. Number of Philosophers: %i\n", arg->number_of_philos);
	ft_printf("2. Time to die: %i\n", arg->time_to_die);
	ft_printf("3. Time_to_eat: %i\n", arg->time_to_eat);
	ft_printf("4. Time_to_sleep: %i\n", arg->time_to_sleep);
	ft_printf("5. Number of times each philosopher must eat: ");
	ft_printf("%i\n\n\n", arg->times_each_philosopher_must_eat);
}

void	print_message_helper(t_args *arg, int thread_id, char *message)
{
	pthread_mutex_lock(&arg->print_mutex);
	ft_printf("Thread %i (philo %i): %s", thread_id, thread_id + 1, message);
	ft_printf("\n");
	pthread_mutex_unlock(&arg->print_mutex);
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

char	*size_t_to_str(size_t value)
{
	char	buffer[21];
	int		i;
	char	*str;

	buffer[20] = '\0';
	i = 19;
	if (value == 0)
	{
		buffer[19] = '0';
		i = 18;
	}
	while (value > 0)
	{
		i--;
		buffer[i] = '0' + (value % 10);
		value /= 10;
	}
	str = (char *)malloc(21 - i);
	if (str != NULL)
		strcpy(str, &buffer[i]);

	return (str);
}

