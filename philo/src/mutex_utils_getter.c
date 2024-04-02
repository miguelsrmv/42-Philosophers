/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils_getter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 22:41:10 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/02 11:57:06 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Gets data from mutex-protected bool
bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	return_value;

	pthread_mutex_lock(mutex);
	return_value = *value;
	pthread_mutex_unlock(mutex);
	return (return_value);
}

// Gets data from mutex-protected int
int	get_int(pthread_mutex_t *mutex, int *value)
{
	int	return_value;

	pthread_mutex_lock(mutex);
	return_value = *value;
	pthread_mutex_unlock(mutex);
	return (return_value);
}

// Gets data from mutex-protected size_t
size_t	get_size_t(pthread_mutex_t *mutex, size_t *value)
{
	size_t	return_value;

	pthread_mutex_lock(mutex);
	return_value = *value;
	pthread_mutex_unlock(mutex);
	return (return_value);
}

// Gets data from mutex-protected t_message
t_message	get_t_msg(pthread_mutex_t *mutex, t_message *message)
{
	t_message	return_message;

	pthread_mutex_lock(mutex);
	return_message = *message;
	pthread_mutex_unlock(mutex);
	return (return_message);
}
