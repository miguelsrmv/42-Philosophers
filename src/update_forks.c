/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:07:39 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/29 19:11:27 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

enum e_ForkStatus	check_fork_availability(t_args *arg, int fork_position)
{
	enum e_ForkStatus	fork_state;

	pthread_mutex_lock(arg->fork_status_mutex);
	fork_state = arg->fork_status[fork_position];
	pthread_mutex_unlock(arg->fork_status_mutex);
	return (fork_state);
}

void	update_fork_availability(t_args **arg, int fork_position)
{
	pthread_mutex_lock((*arg)->fork_status_mutex);
	if ((*arg)->fork_status[fork_position] == AVAILABLE)
		(*arg)->fork_status[fork_position] = TAKEN;
	else
		((*arg)->fork_status[fork_position] = AVAILABLE);
	pthread_mutex_unlock((*arg)->fork_status_mutex);
}
