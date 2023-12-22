/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:53:07 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/22 19:04:06 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_args *arg, int thread_id,
	size_t current_time, size_t epoch_time)
{
	char	*message;

	if (arg->death_flag && arg->philo_state[thread_id] != DEAD)
		return ;
	message = get_full_philo_message(arg, thread_id, current_time, epoch_time);
	if (!message)
		 // Que erro por neste caso??? Igual a add_to_buffered_output?
		return ;
/* 	char *message2 = ft_strjoin(ft_itoa(current_time - epoch_time), "\n");
	write(open("list_test", O_WRONLY | O_APPEND), message2, ft_strlen(message2));		// Log check */
	add_to_buffered_output(arg, message);

}

char	*get_full_philo_message(t_args *arg, int thread_id,
	size_t current_time, size_t epoch_time)
{
	char	*left_message;
	char	*right_message;
	char	*result;

	left_message = left_side_of_str(thread_id, current_time, epoch_time);
	if (!left_message)
		return (NULL);
	right_message = right_side_of_str(arg, thread_id);
	if (!right_message)
	{
		free(left_message);
		return (NULL);
	}
	result = concatenate_str_with_space(left_message, right_message);
	free(left_message);
	free(right_message);
	if (!result)
		return (NULL);
	return (result);
}

char	*left_side_of_str(int thread_id,
	size_t current_time, size_t epoch_time)
{
	char	*left_number;
	char	*right_number;
	char	*result;

	left_number = ft_itoa(get_time_diff(epoch_time, current_time));
	if (!left_number)
		return (NULL);
	right_number = ft_itoa(thread_id + 1);
	if (!right_number)
	{
		free(left_number);
		return (NULL);
	}
	result = concatenate_str_with_space(left_number, right_number);
	free(left_number);
	free(right_number);
	if (!result)
		return (NULL);
	return (result);
}

char	*right_side_of_str(t_args *arg, int thread_id)
{
	char	*result;

	result = NULL;
	if (arg->philo_state[thread_id] == AVAILABLE_FOR_EATING_2_FORK_LEFT
		|| arg->philo_state[thread_id] == AVAILABLE_FOR_EATING_1_FORK_LEFT)
		result = ft_strdup("has taken a fork\n");
	else if (arg->philo_state[thread_id] == EATING)
		result = ft_strdup("is eating\n");
	else if (arg->philo_state[thread_id] == SLEEPING)
		result = ft_strdup("is sleeping\n");
	else if (arg->philo_state[thread_id] == THINKING)
		result = ft_strdup("is thinking\n");
	else if (arg->philo_state[thread_id] == DEAD)
		result = ft_strdup("died\n");
	if (!result)
		return (NULL);
	return (result);
}

char	*concatenate_str_with_space(char *left_string, char *right_string)
{
	char	*left_message;
	char	*result;

	left_message = ft_strjoin(left_string, " ");
	//left_message = ft_strjoin(left_string, "\t");
	if (!left_message)
		return (NULL);
	result = ft_strjoin(left_message, right_string);
	if (!result)
	{
		free(left_message);
		return (NULL);
	}
	free(left_message);
	return (result);
}
