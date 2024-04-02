/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_printing_thread.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:41:15 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/02 15:52:40 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Waits for messages to be created, then prints them
void	monitoring_and_printing_thread(t_table *table)
{
	t_message	*current;
	t_message	current_copy;
	bool		simulation_run;

	simulation_run = true;
	wait_for_threads(table);
	while (!(table->message_head) || !(table->message_head->next))
		;
	current = table->message_head;
	while (true)
	{
		current_copy = get_t_msg(&(table->message_mutex), current);
		print_philo_action(current_copy);
		update_simstate(table, &table->philos[current_copy.philo_id],
			current_copy.action, &simulation_run);
		if (!simulation_run)
			break ;
		while (!current || !current->next)
			;
		current = current->next;
	}
	return ;
}

// Prints philosopher's action
void	print_philo_action(t_message current)
{
	if (current.action == TOOK_A_FORK)
		printf("%ld\t%i took a fork\n",
			current.time_stamp, current.philo_id);
	else if (current.action == IS_EATING)
		printf("%ld\t%i is eating\n",
			current.time_stamp, current.philo_id);
	else if (current.action == IS_SLEEPING)
		printf("%ld\t%i is sleeping\n",
			current.time_stamp, current.philo_id);
	else if (current.action == IS_THINKING)
		printf("%ld\t%i is thinking\n",
			current.time_stamp, current.philo_id);
	else
		printf("%ld\t%i died\n",
			current.time_stamp, current.philo_id);
}

void	update_simstate(t_table *table, t_philos *philo,
			t_PhiloAction action, bool *simulation_run)
{
	if (action == DIED)
		*simulation_run = false;
	else if (action == IS_EATING)
	{
		philo->eat_count++;
		if (philo->eat_count
			== philo->times_each_philosopher_must_eat)
			table->success_count++;
		if (table->success_count
			== philo->times_each_philosopher_must_eat)
			*simulation_run = false;
	}
}
