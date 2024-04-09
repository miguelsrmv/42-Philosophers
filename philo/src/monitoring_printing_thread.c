/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_printing_thread.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:41:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/09 19:42:27 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Waits for messages to be created, then prints them
// Upon printing, death_flag and success_count are updated
// If an endpoint was reached, no further messages are printed
void	monitoring_and_printing_thread(t_table *table)
{
	t_message	*current;
	t_message	current_copy;
	bool		simulation_stop;

	current = (void *) NULL;
	simulation_stop = false;
	wait_for_first_element(&current, table);
	while (!simulation_stop)
	{
		current_copy = get_t_msg(&(table->message_mutex), current);
		print_philo_action(current_copy);
		update_simstate(table, &table->philos[current_copy.philo_id],
			current_copy.action, &simulation_stop);
		if (simulation_stop)
			return ;
		current = current_copy.next;
		wait_for_next_element(&current, table);
	}
	return ;
}

// ft_usleeps(PRINT_WAIT_TIME) whenever first list element is not available
void	wait_for_first_element(t_message **current, t_table *table)
{
	t_message	**target;

	pthread_mutex_lock(&(table->message_mutex));
	target = &table->message_head;
	while (!(*current))
	{
		pthread_mutex_unlock(&(table->message_mutex));
		ft_usleep(LIST_WAIT_TIME);
		pthread_mutex_lock(&(table->message_mutex));
		(*current) = (*target);
	}
	pthread_mutex_unlock(&(table->message_mutex));
}

// ft_usleeps(PRINT_WAIT_TIME) whenever next element is not available
/// Not refactored so as to not have so many "ifs".
void	wait_for_next_element(t_message **current, t_table *table)
{
	t_message	**target;

	pthread_mutex_lock(&(table->message_mutex));
	target = &table->message_end->next;
	while (!(*current))
	{
		pthread_mutex_unlock(&(table->message_mutex));
		ft_usleep(LIST_WAIT_TIME);
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
			== table->number_of_philos)
		{
			*simulation_stop = true;
			set_bool(&(table->success_mutex),
				&(table->success_flag), true);
		}
	}
}

// Prints philosopher's action from the node
void	print_philo_action(t_message current)
{
	char	*actions[5];

	actions[0] = FORK_MESSAGE;
	actions[1] = EATING_MESSAGE;
	actions[2] = SLEEPING_MESSAGE;
	actions[3] = THINKING_MESSAGE;
	actions[4] = DEATH_MESSAGE;
	printf("%ld %i %s\n",
		current.time_stamp,
		current.philo_id,
		actions[current.action]);
}
