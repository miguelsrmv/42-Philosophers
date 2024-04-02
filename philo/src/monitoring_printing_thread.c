/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_printing_thread.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:41:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/02 20:22:48 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Waits for messages to be created, then prints them
void	monitoring_and_printing_thread(t_table *table)
{
	t_message	*current;
	t_message	current_copy;
	bool		simulation_stop;

	current = (void *) NULL;
	simulation_stop = false;
	wait_for_threads(table);
	wait_for_element(&current, &table->message_head, table);
	wait_for_element(&current, &table->message_head->next, table);
	while (true)
	{
		current_copy = get_t_msg(&(table->message_mutex), current);
		print_philo_action(current_copy);
		update_simstate(table, &table->philos[current_copy.philo_id],
			current_copy.action, &simulation_stop);
		if (simulation_stop)
			break ;
		current = current_copy.next;
		wait_for_element(&current, &table->message_end->next, table);
	}
	return ;
}

// ft_usleeps(PRINT_WAIT_TIME) whenever next element is not (yet) available
void	wait_for_element(t_message **current, t_message **target,
			t_table *table)
{
	ft_usleep(PRINT_WAIT_TIME);
	pthread_mutex_lock(&(table->message_mutex));
	while (!(*current))
	{
		pthread_mutex_unlock(&(table->message_mutex));
		ft_usleep(PRINT_WAIT_TIME);
		pthread_mutex_lock(&(table->message_mutex));
		(*current) = (*target);
	}
	pthread_mutex_unlock(&(table->message_mutex));
}

// Updates simulation_run in case a philosopher dies
// or [times_each_philosopher_must_eat] is reached
void	update_simstate(t_table *table, t_philos *philo,
			t_PhiloAction action, bool *simulation_stop)
{
	if (action == DIED)
		*simulation_stop = true;
	else if (action == IS_EATING)
	{
		philo->eat_count++;
		if (philo->eat_count
			== philo->times_each_philosopher_must_eat)
			table->success_count++;
		if (table->success_count
			== philo->times_each_philosopher_must_eat)
			*simulation_stop = true;
	}
}

// Prints philosopher's action
void	print_philo_action(t_message current)
{
	char	*message;

	if (current.action == TOOK_A_FORK)
		message = FORK_MESSAGE;
	else if (current.action == IS_EATING)
		message = EATING_MESSAGE;
	else if (current.action == IS_SLEEPING)
		message = SLEEPING_MESSAGE;
	else if (current.action == IS_THINKING)
		message = THINKING_MESSAGE;
	else if (current.action == DIED)
		message = DEATH_MESSAGE;
	printf("%ld %i %s\n",
		current.time_stamp,
		current.philo_id,
		message);
}
